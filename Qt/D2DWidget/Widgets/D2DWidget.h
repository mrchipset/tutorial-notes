#ifndef D2D_WIDGET_H
#define D2D_WIDGET_H

#include <Windows.h>
#include <d2d1_3.h>

#include <QWidget>
#include <QPaintEvent>

class D2DWidget : public QWidget
{
    Q_OBJECT
public:
    explicit D2DWidget(QWidget* parent = nullptr);
    ~D2DWidget();
    virtual QPaintEngine* paintEngine() const override;
private:
    ID2D1Factory*           m_pD2DFactory   = NULL; // Direct2D factory
    ID2D1HwndRenderTarget*  m_pRenderTarget = NULL; // Render target
    ID2D1SolidColorBrush*   m_pBlackBrush   = NULL; // A black brush, reflect the line color

    void cleanUp();
    void createD2DResource(HWND hWnd);
protected:
    virtual void paintEvent(QPaintEvent* ev) override;
    virtual void draw();

};
#endif