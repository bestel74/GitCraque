#ifndef RENDERER_H
#define RENDERER_H

#include <QObject>
#include <QGraphicsView>
#include <QGraphicsSimpleTextItem>
#include <QFontDatabase>

#include "gitcommitobj.h"

class Renderer
{
public:
    Renderer(QGraphicsView *gv);

    void render(QList <GitCommitObj *> list_gitCommitObj);

private:
    QGraphicsView *graphView;
    QGraphicsScene scene;
};

#endif // RENDERER_H
