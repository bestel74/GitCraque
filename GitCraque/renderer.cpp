#include "renderer.h"


Renderer::Renderer(QGraphicsView *gv) :
    graphView(gv)
{
    graphView->setScene(&scene);
}



void Renderer::render(QList <GitCommitObj *> list_gitCommitObj) {
    scene.clear();

    int x=0, y=0;

    foreach(GitCommitObj *obj, list_gitCommitObj) {
        scene.addRect(x+0, y+0, 10, 10);
        const QFont fixedFont = QFontDatabase::systemFont(QFontDatabase::FixedFont);

        QGraphicsSimpleTextItem *textItem = scene.addSimpleText(GitCommitObj::convertIdString(obj->commit_id), fixedFont);
        textItem->setPos(15, y);

        y+=15;
    }
}

