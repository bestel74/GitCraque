#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <string.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

#if (LIBGIT2_VER_MAJOR == 0)
    #if (LIBGIT2_VER_MINOR < 22)
        git_threads_init();
    #else
        git_libgit2_init();
    #endif
#endif

    renderer = new Renderer(ui->graphicsView);

    timer_renderer.setInterval(1000);
    connect(&timer_renderer, &QTimer::timeout, this, &MainWindow::refresh_ui);

}

MainWindow::~MainWindow()
{
    delete ui;
}


bool MainWindow::isNewCommit(git_oid *oid) {
    foreach(GitCommitObj *obj, list_gitCommitObj) {
        if(memcmp(&obj->commit_id, oid, sizeof(obj->commit_id)) == 0) {
            return false;
        }
    }

    return true;
}


void MainWindow::parseGitRepo() {
    git_revwalk_sorting(walker, GIT_SORT_NONE);
    git_revwalk_push_head(walker);

    git_oid oid;
    // Retrieve info about ALL COMMIT, MOUHAHAHAHA
    while(!git_revwalk_next(&oid, walker)) {
        git_commit * commit = Q_NULLPTR;
        git_commit_lookup(&commit, repo, &oid);

        if(isNewCommit(&oid)) {
            GitCommitObj *tmp = new GitCommitObj;

            // Set commit id
            tmp->commit_id = oid;

            // Set all parent id
            unsigned int parCount = git_commit_parentcount(commit);
            for(unsigned int i=0 ; i < parCount ; i++) {
                git_oid par_oid = *git_commit_parent_id(commit, i);
                tmp->commit_list_parentID.append(par_oid);
            }

            // Set commit author
            git_signature sign = *git_commit_author(commit);
            tmp->commit_signature = sign;

            // Set commit message
            const char *msg = git_commit_message(commit);
            tmp->commit_message.fromLocal8Bit(msg, strlen(msg));

            list_gitCommitObj.append(tmp);
        }
    }
}


void MainWindow::refresh_ui()
{
    // Parse and prepare objects
    parseGitRepo();

    // Render Objects
    renderer->render(list_gitCommitObj);
}


void MainWindow::on_pb_browse_clicked()
{
    QString folder = QFileDialog::getExistingDirectory(this, tr("Open Git folder"), QString());
    if(folder.isEmpty() == false) {
        int ret = git_repository_open(&repo, folder.toUtf8().data());
        if(!ret) {
            git_revwalk_new(&walker, repo);
            ui->le_gitFilePath->setText(folder);

            // Flush all previous objects
            foreach(GitCommitObj *obj, list_gitCommitObj) {
                delete obj;
            }
            list_gitCommitObj.clear();

            timer_renderer.start();
        }
        else {
            QMessageBox::critical(this, tr("Error"), tr("Not a valid 'git' folder?"));
        }
    }
}
