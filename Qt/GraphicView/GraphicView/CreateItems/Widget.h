#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QTimer>
#include <QFuture>

class Widget : public QGraphicsView
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
private:
    QGraphicsScene* mScence;
    QGraphicsItem* mItem;
    QTimer mTimer;
    QFuture<void> mFuture;
    volatile bool mIsRender;
protected:
    virtual void resizeEvent(QResizeEvent* ev);
};
#endif // WIDGET_H
