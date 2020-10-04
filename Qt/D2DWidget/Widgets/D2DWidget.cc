#include "D2DWidget.h"

#include <QPainter>

#define SAFE_RELEASE(P) if(P){P->Release() ; P = nullptr ;}

D2DWidget::D2DWidget(QWidget* parent) : QWidget(parent),
    m_pRenderTarget(nullptr),
    m_pD2DFactory(nullptr),
    m_pBlackBrush(nullptr)
{
    setAttribute(Qt::WA_NativeWindow);
    setAttribute(Qt::WA_PaintOnScreen);
    setAttribute(Qt::WA_NoSystemBackground);
}

D2DWidget::~D2DWidget()
{
    cleanUp();
}

QPaintEngine* D2DWidget::paintEngine() const
{
    return nullptr;
}

void D2DWidget::cleanUp()
{
    SAFE_RELEASE(m_pRenderTarget) ;
    SAFE_RELEASE(m_pBlackBrush) ;
    SAFE_RELEASE(m_pD2DFactory) ;
}

void D2DWidget::createD2DResource(HWND hWnd)
{
    if (!m_pRenderTarget) {
        HRESULT hr ;

        hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pD2DFactory) ;
        if (FAILED(hr)) {
            MessageBox(hWnd, "Create D2D factory failed!", "Error", 0) ;
            return ;
        }

        // Obtain the size of the drawing area
        RECT rc ;
        GetClientRect(hWnd, &rc) ;

        // Create a Direct2D render target
        hr = m_pD2DFactory->CreateHwndRenderTarget(
                 D2D1::RenderTargetProperties(),
                 D2D1::HwndRenderTargetProperties(
                     hWnd,
                     D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top)
                 ),
                 &m_pRenderTarget
             ) ;
        if (FAILED(hr)) {
            MessageBox(hWnd, "Create render target failed!", "Error", 0) ;
            return ;
        }

        // Create a brush
        hr = m_pRenderTarget->CreateSolidColorBrush(
                 D2D1::ColorF(D2D1::ColorF::Black),
                 &m_pBlackBrush
             ) ;
        if (FAILED(hr)) {
            MessageBox(hWnd, "Create brush failed!", "Error", 0) ;
            return ;
        }
    }
}

void D2DWidget::paintEvent(QPaintEvent* ev)
{
    QPainter painter(this);
    painter.beginNativePainting();
    draw();
    painter.endNativePainting();
}

void D2DWidget::draw()
{
    HWND hwnd;
    hwnd = (HWND)this->winId();

    createD2DResource(hwnd) ;

    m_pRenderTarget->BeginDraw() ;

    // Clear background color to White
    m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));

    // Draw Rectangle
    m_pRenderTarget->DrawRectangle(
        D2D1::RectF(100.f, 100.f, 500.f, 500.f),
        m_pBlackBrush
    );

    HRESULT hr = m_pRenderTarget->EndDraw() ;
    if (FAILED(hr)) {
        MessageBox(NULL, "Draw failed!", "Error", 0) ;
        return ;
    }
}