#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QTimer>

#include "git2.h"
#include "renderer.h"
#include "gitcommitobj.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void parseGitRepo();
    bool isNewCommit(git_oid *oid);

public slots:
    void refresh_ui();

private slots:
    void on_pb_browse_clicked();

private:
    Ui::MainWindow *ui;

    git_repository *repo = Q_NULLPTR;
    git_revwalk *walker = Q_NULLPTR;

    Renderer *renderer;
    QTimer timer_renderer;

    QList <GitCommitObj *> list_gitCommitObj;

};

#endif // MAINWINDOW_H
