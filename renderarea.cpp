#include "renderarea.h"
#include "QPainter"

#include "utils.h"

RenderArea::RenderArea(QWidget *parent)
    : QWidget( parent )
{
    FillWhite();
}

RenderArea::~RenderArea()
{

}

void RenderArea::Render()
{
    m_renderarea = m_imageContainer;
    repaint();
}

void RenderArea::OpenImage(const QString &filename)
{
    QImage tempImage;
    tempImage.load( filename );
    m_imageContainer = tempImage.convertToFormat( QImage::Format_RGB888 );
    m_ycbcr.Init( m_imageContainer.width(), m_imageContainer.height() );
    CalcYCbCr();
    Render();
}

void RenderArea::FillWhite()
{
    m_imageContainer = QImage( 512, 512, QImage::Format_RGB888 );
    m_imageContainer.fill( QColor( 255, 255, 255 ) );
    m_ycbcr.Init( m_imageContainer.width(), m_imageContainer.height() );
    CalcYCbCr();
    Render();
}

void RenderArea::FillBlack()
{
    m_imageContainer = QImage( 512, 512, QImage::Format_RGB888 );
    m_imageContainer.fill(0);
    m_ycbcr.Init( m_imageContainer.width(), m_imageContainer.height() );
    CalcYCbCr();
    Render();
}

void RenderArea::YCbCr2RGB()
{
    for( int i = 0; i < m_imageContainer.width(); i++ )
        for( int j = 0; j < m_imageContainer.height(); j++ )
        {
            float y =  m_ycbcr.Y [ i ][ j ];
            float cb = m_ycbcr.Cb[ i ][ j ];
            float cr = m_ycbcr.Cr[ i ][ j ];
            uint8_t R = clamp( y + 1.402f   * ( cr - 128.0f ), 0.0f, 255.0f );
            uint8_t G = clamp( y - 0.34414f * ( cb - 128.0f ) - 0.71414f * ( cr - 128.0f ), 0.0f, 255.0f );
            uint8_t B = clamp( y + 1.772f   * ( cb - 128.0f ), 0.0f, 255.0f );
            m_imageContainer.setPixel( i, j, qRgb( R, G, B ) );
        }
    CalcYCbCr();
    Render();
}

void RenderArea::CalcYCbCr()
{
    for( int x = 0; x < m_imageContainer.width(); x++ )
        for( int y = 0; y < m_imageContainer.height(); y++ )
        {
            QRgb p = m_imageContainer.pixel( x, y );
            m_ycbcr.Y[ x ][ y ] =  0.299f * ( float )qRed( p ) + 0.587f * ( float )qGreen( p ) + 0.114f * ( float )qBlue( p );
            m_ycbcr.Cb[ x ][ y ] = 0.564334f * ( float )( qBlue( p ) - m_ycbcr.Y[ x ][ y ] ) + 128.0f;
            m_ycbcr.Cr[ x ][ y ] = 0.713267f * ( float )( qRed( p ) - m_ycbcr.Y[ x ][ y ] ) + 128.0f;
        }
}

void RenderArea::ToGrayWeightAverage()
{
    for( int x = 0; x < m_imageContainer.width(); x++ )
        for( int y = 0; y < m_imageContainer.height(); y++ )
        {
            QRgb p = m_imageContainer.pixel( x, y );
            int gray = ( qRed( p ) + qGreen( p ) + qBlue( p ) ) / 3;
            m_imageContainer.setPixel( x, y, qRgb( gray, gray, gray ) );
        }
    CalcYCbCr();
    Render();
}

void RenderArea::ToGrayCCIR601()
{
    for( int x = 0; x < m_imageContainer.width(); x++ )
        for( int y = 0; y < m_imageContainer.height(); y++ )
        {
            QRgb p = m_imageContainer.pixel( x, y );
            int gray = 0.299f * ( float )qRed( p ) + 0.587f * ( float )qGreen( p ) + 0.114f * ( float )qBlue( p );
            m_imageContainer.setPixel( x, y, qRgb( gray, gray, gray ) );
        }
    CalcYCbCr();
    Render();
}

void RenderArea::ShowY()
{
    for( int x = 0; x < m_renderarea.width(); x++ )
        for( int y = 0; y < m_renderarea.height(); y++ )
        {
            m_renderarea.setPixel( x, y, qRgb( m_ycbcr.Y[ x ][ y ], m_ycbcr.Y[ x ][ y ], m_ycbcr.Y[ x ][ y ] ) );
        }
    repaint();
}

void RenderArea::ShowCb()
{
    for( int x = 0; x < m_renderarea.width(); x++ )
        for( int y = 0; y < m_renderarea.height(); y++ )
        {
            m_renderarea.setPixel( x, y, qRgb( m_ycbcr.Cb[ x ][ y ], m_ycbcr.Cb[ x ][ y ], m_ycbcr.Cb[ x ][ y ] ) );
        }
    repaint();
}

void RenderArea::ShowCr()
{
    for( int x = 0; x < m_renderarea.width(); x++ )
        for( int y = 0; y < m_renderarea.height(); y++ )
        {
            m_renderarea.setPixel( x, y, qRgb( m_ycbcr.Cr[ x ][ y ], m_ycbcr.Cr[ x ][ y ], m_ycbcr.Cr[ x ][ y ] ) );
        }
    repaint();
}

void RenderArea::ShowRGB()
{
    Render();
}

void RenderArea::paintEvent(QPaintEvent *event)
{
    QPainter painter( this );
    painter.drawImage( 0, 0, m_renderarea );
}

