#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

#if (LIBGIT2_VER_MAJOR == 0)
    #if (LIBGIT2_VER_MINOR < 22)
        git_threads_init();
    #else
        git_libgit_init();
    #endif
#endif

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_browse_clicked()
{
    QString folder = QFileDialog::getExistingDirectory(this, tr("Open Git folder"), QString());
    if(folder.isEmpty() == false) {
        ui->le_gitFilePath->setText(folder);
    }
}

void MainWindow::on_pb_go_clicked()
{

}
