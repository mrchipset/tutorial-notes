#include "Widget.h"
#include <QDebug>
#include <QResizeEvent>
#include <QtConcurrent>

Widget::Widget(QWidget *parent)
    : QGraphicsView(parent),
      mScence(new QGraphicsScene(this)),
      mIsRender(true)
{

    mScence->setItemIndexMethod(QGraphicsScene::NoIndex);   // if you what to use threading rendering, the index algorithm should be disabled.
    mScence->setSceneRect(0, 0, 640, 480);
    setScene(mScence);
    QGraphicsView::setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    setCacheMode(QGraphicsView::CacheBackground);
    setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    setDragMode(QGraphicsView::ScrollHandDrag);
    qDebug() << "UI:" << QThread::currentThreadId();

    QtConcurrent::run([&](){
        qDebug() << "Concurrent:" << QThread::currentThreadId();
        mScence->addRect(320 - 40, 240 - 40, 40, 40);
    });

    mItem = mScence->addLine(0, 0, 320, 240);
    mFuture = QtConcurrent::run([&](){
        qDebug() << "Thread:" << QThread::currentThreadId();
        while(mIsRender)
        {
            auto pos = mItem->pos();
            pos.setX(pos.x() + 3);
            if (pos.x() > mScence->width())
            {
                mScence->removeItem(mItem);
                mItem = mScence->addLine(0, 0, 320, 240);
                pos.setX(0);
            }
            mItem->setPos(pos);
            update();
            QThread::msleep(1000/60);
        }
    });
}

Widget::~Widget()
{
    mIsRender = false;
    mFuture.waitForFinished();
}

void Widget::resizeEvent(QResizeEvent *ev)
{
    QGraphicsView::fitInView(mScence->sceneRect());
    QGraphicsView::resizeEvent(ev);
//    qDebug() << mScence->sceneRect();
//    qDebug() << mItem->x() << mItem->y() << mItem->boundingRect();
//    setSceneRect(0, 0, frameSize().width(), frameSize().height());
}

