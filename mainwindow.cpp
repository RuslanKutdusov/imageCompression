#include <algorithm>
#include <zlib.h>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QPainter"
#include "QFileDialog"
#include "QMessageBox"
#include <math.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    imageWidget1 = new RenderArea( ui->centralWidget );
    imageWidget1->setObjectName(QStringLiteral("image1"));
    imageWidget1->setGeometry(QRect(0, 0, 512, 512 ));

    imageWidget2 = new RenderArea( ui->centralWidget );
    imageWidget2->setObjectName(QStringLiteral("image2"));
    imageWidget2->setGeometry(QRect(520, 0, 512, 512 ));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_image1Open_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open Image"), "~", tr("Image Files (*.png *.jpg *.bmp)"));
    imageWidget1->OpenImage( filename );
    resetPSNR();
}

void MainWindow::on_image1Save_clicked()
{

}

void MainWindow::on_Image2Open_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open Image"), "~", tr("Image Files (*.png *.jpg *.bmp)"));
    imageWidget2->OpenImage( filename );
    resetPSNR();
}

void MainWindow::on_Image2Save_clicked()
{

}

void MainWindow::on_image1Black_clicked()
{
    imageWidget1->FillBlack();
}

void MainWindow::on_image1White_clicked()
{
    imageWidget1->FillWhite();
}

void MainWindow::on_image1GrayWA_clicked()
{
    imageWidget1->ToGrayWeightAverage();
}

void MainWindow::on_image1GrayCCIR_clicked()
{
    imageWidget1->ToGrayCCIR601();
}

void MainWindow::on_image2Black_clicked()
{
    imageWidget2->FillBlack();
}

void MainWindow::on_image2White_clicked()
{
    imageWidget2->FillWhite();
}

void MainWindow::on_image2GrayWA_clicked()
{
    imageWidget2->ToGrayWeightAverage();
}

void MainWindow::on_image2GrayCCIR_clicked()
{
    imageWidget2->ToGrayCCIR601();
}

void MainWindow::on_Y1_clicked()
{
    imageWidget1->ShowY();
}

void MainWindow::on_Cb1_clicked()
{
    imageWidget1->ShowCb();
}

void MainWindow::on_Cr1_clicked()
{
    imageWidget1->ShowCr();
}

void MainWindow::on_Y2_clicked()
{
    imageWidget2->ShowY();
}

void MainWindow::on_Cb2_clicked()
{
    imageWidget2->ShowCb();
}

void MainWindow::on_Cr2_clicked()
{
    imageWidget2->ShowCr();
}

void MainWindow::on_RGB1_clicked()
{
    imageWidget1->ShowRGB();
}

void MainWindow::on_RGB2_clicked()
{
    imageWidget2->ShowRGB();
}

void MainWindow::on_transform_clicked()
{
    imageWidget1->YCbCr2RGB();
}

void MainWindow::on_transform2_clicked()
{
    imageWidget2->YCbCr2RGB();
}

void MainWindow::on_calcPSNR_clicked()
{
    if( imageWidget1->m_renderarea.width() != imageWidget2->m_renderarea.width() ||
        imageWidget1->m_renderarea.height() != imageWidget2->m_renderarea.height() ||
        imageWidget1->m_renderarea.width() != imageWidget2->m_renderarea.height() )
    {
        QMessageBox msgBox;
        char buf[ 1024 ];
        sprintf( buf, "Images has different sizes %ux%u and %ux%u", imageWidget1->m_renderarea.width(), imageWidget1->m_renderarea.height(),
                                                                    imageWidget2->m_renderarea.width(), imageWidget2->m_renderarea.height() );
        msgBox.setText( buf );
        msgBox.exec();
        return;
    }

    int N = imageWidget1->m_renderarea.width();
    for( int x = 0; x < N; x++ )
        for( int y = 0; y < N; y++ )
        {
            QRgb rgb1 = imageWidget1->m_renderarea.pixel( x, y );
            QRgb rgb2 = imageWidget2->m_renderarea.pixel( x, y );
            float dr = qRed( rgb1 ) - qRed( rgb2 );
            float dg = qGreen( rgb1 ) - qGreen( rgb2 );
            float db = qBlue( rgb1 ) - qBlue( rgb2 );
            float diff = dr * dr + dg * dg + db * db;
            m_psnr = 10.0f * log10( 3.0f * 255.0f * 255.0f * ( float )N * ( float )N  / diff );
        }
    char buf[ 1024 ];
    sprintf( buf, "PSNR: %f", m_psnr );
    ui->PSNRLabel->setText( buf );
}

void MainWindow::on_dsCb_clicked()
{
    imageWidget1->ShowDsCb();
}

void MainWindow::on_dsCr_clicked()
{
    imageWidget1->ShowDsCr();
}

void MainWindow::on_dctY_clicked()
{
    imageWidget1->showDctY();
}

void MainWindow::on_dctCb_clicked()
{
    imageWidget1->showDctCb();
}

void MainWindow::on_dctCr_clicked()
{
    imageWidget1->showDctCr();
}

void MainWindow::on_pushButton_clicked()
{
    DOWNSAMPLING ds = DOWNSAMPLING_NONE;
    QUANTIZATION q = QUANTIZATION_MAX;
    if( ui->dsNone->isChecked() )
        ds = DOWNSAMPLING_NONE;
    else if( ui->ds2h1v->isChecked() )
        ds = DOWNSAMPLING_2h1v;
    else if( ui->ds2h2v->isChecked() )
        ds = DOWNSAMPLING_2h2v;
    else if( ui->ds1h2v->isChecked() )
        ds = DOWNSAMPLING_1h2v;
    else
    {
        QMessageBox msgBox;
        char buf[ 1024 ];
        sprintf( buf, "You need to select downsample method" );
        msgBox.setText( buf );
        msgBox.exec();
        return;
    }

    uint32_t qParam1;
    uint32_t qParam2;
    if( ui->quantMax->isChecked() )
    {
        q = QUANTIZATION_MAX;
        qParam1 = ui->Ny->text().toUInt();
        qParam2 = ui->Nc->text().toUInt();
    }
    else if( ui->quantAlfaGamma->isChecked() )
    {
        q = QUANTIZATION_ALFA_GAMMMA;
        qParam1 = ui->alfa->text().toUInt();
        qParam2 = ui->gamma->text().toUInt();
    }
    else if( ui->quantStd->isChecked() )
    {
        q = QUANTIZATION_STD_MATRIX;
    }
    else
    {
        QMessageBox msgBox;
        char buf[ 1024 ];
        sprintf( buf, "You need to select quantization" );
        msgBox.setText( buf );
        msgBox.exec();
        return;
    }

    uint32_t uc, c;
    imageWidget1->Compress( ds, q, qParam1, qParam2, uc, c );
    char buf[ 1024 ];
    sprintf( buf, "Uncompressed: %u", uc / 1024 );
    ui->uncompressed->setText( buf );
    sprintf( buf, "Compressed: %u", c / 1024 );
    ui->compressed->setText( buf );
}

void MainWindow::resetPSNR()
{
    m_psnr = 0.0f;
    ui->PSNRLabel->setText( "PSNR: -- " );
}


////////////////////////////////////////////////////////////////////////////

const float g_stdQuantizationMatrixY[ 8 ][ 8 ] = {
    { 16.0f,   11.0f,   10.0f,   16.0f,   24.0f,   40.0f,   51.0f,   61.0f  },
    { 12.0f,   12.0f,   14.0f,   19.0f,   26.0f,   58.0f,   60.0f,   55.0f  },
    { 14.0f,   13.0f,   16.0f,   24.0f,   40.0f,   57.0f,   69.0f,   56.0f  },
    { 14.0f,   17.0f,   22.0f,   29.0f,   51.0f,   87.0f,   80.0f,   62.0f  },
    { 18.0f,   22.0f,   37.0f,   56.0f,   68.0f,  109.0f,  103.0f,   77.0f  },
    { 24.0f,   35.0f,   55.0f,   64.0f,   81.0f,  104.0f,  113.0f,   92.0f  },
    { 49.0f,   64.0f,   78.0f,   87.0f,  103.0f,  121.0f,  120.0f,  101.0f  },
    { 72.0f,   92.0f,   95.0f,   98.0f,  112.0f,  100.0f,  103.0f,   99.0f  }
};

const float g_stdQuantizationMatrixCbCr[ 8 ][ 8 ] = {
    { 17.0f,   18.0f,   24.0f,   47.0f,   99.0f,   99.0f,   99.0f,   99.0f },
    { 18.0f,   21.0f,   26.0f,   66.0f,   99.0f,   99.0f,   99.0f,   99.0f },
    { 24.0f,   26.0f,   56.0f,   99.0f,   99.0f,   99.0f,   99.0f,   99.0f },
    { 47.0f,   66.0f,   99.0f,   99.0f,   99.0f,   99.0f,   99.0f,   99.0f },
    { 99.0f,   99.0f,   99.0f,   99.0f,   99.0f,   99.0f,   99.0f,   99.0f },
    { 99.0f,   99.0f,   99.0f,   99.0f,   99.0f,   99.0f,   99.0f,   99.0f },
    { 99.0f,   99.0f,   99.0f,   99.0f,   99.0f,   99.0f,   99.0f,   99.0f },
    { 99.0f,   99.0f,   99.0f,   99.0f,   99.0f,   99.0f,   99.0f,   99.0f }
};

const uint32_t g_zigzagMap[] = {
       0,   1,  8, 16,  9,  2,  3, 10,
       17, 24, 32, 25, 18, 11,  4,  5,
       12, 19, 26, 33, 40, 48, 41, 34,
       27, 20, 13,  6,  7, 14, 21, 28,
       35, 42, 49, 56, 57, 50, 43, 36,
       29, 22, 15, 23, 30, 37, 44, 51,
       58, 59, 52, 45, 38, 31, 39, 46,
       53, 60, 61, 54, 47, 55, 62, 63
};

RenderArea::RenderArea(QWidget *parent)
    : QWidget( parent )
    , dsCbCrWidth( 0 )
    , dsCbCrHeight( 0 )
{
    Y  = new uint8_t*[ 512 ];
    Cb = new uint8_t*[ 512 ];
    Cr = new uint8_t*[ 512 ];
    dsCb = new uint8_t*[ 512 ];
    dsCr = new uint8_t*[ 512 ];
    dctY  = new float*[ 512 ];
    dctCb = new float*[ 512 ];
    dctCr = new float*[ 512 ];

    for( uint32_t i = 0; i < 512; i++ )
    {
        Y[ i ]  = new uint8_t[ 512 ];
        Cb[ i ] = new uint8_t[ 512 ];
        Cr[ i ] = new uint8_t[ 512 ];
        dsCb[ i ] = new uint8_t[ 512 ];
        dsCr[ i ] = new uint8_t[ 512 ];
        dctY[ i ]  = new float[ 512 ];
        dctCb[ i ] = new float[ 512 ];
        dctCr[ i ] = new float[ 512 ];
    }

    FillWhite();

    const float PI = M_PI;

    for( uint8_t j = 0; j < 8; j++ )
    {
        M[ 0 ][ j ] = 1.0f / sqrt( 8.0f );
        for( uint8_t i = 1; i < 8; i++ )
            M[ i ][ j ] = 0.5f * cosf( ( 2.0f * ( float )j + 1.0f ) * ( float )i * PI / 16.0f );
    }
}

RenderArea::~RenderArea()
{
    for( uint32_t i = 0; i < 512; i++ )
    {
        delete[] Y[ i ];
        delete[] Cb[ i ];
        delete[] Cr[ i ];
        delete[] dsCb[ i ];
        delete[] dsCr[ i ];
        delete[] dctY[ i ];
        delete[] dctCb[ i ];
        delete[] dctCr[ i ];
    }
    delete[] Y;
    delete[] Cb;
    delete[] Cr;
    delete[] dsCb;
    delete[] dsCr;
    delete[] dctY;
    delete[] dctCb;
    delete[] dctCr;
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
    CalcYCbCr();
    Render();
}

void RenderArea::FillWhite()
{
    m_imageContainer = QImage( 512, 512, QImage::Format_RGB888 );
    m_imageContainer.fill( QColor( 255, 255, 255 ) );
    CalcYCbCr();
    Render();
}

void RenderArea::FillBlack()
{
    m_imageContainer = QImage( 512, 512, QImage::Format_RGB888 );
    m_imageContainer.fill(0);
    CalcYCbCr();
    Render();
}

void RenderArea::YCbCr2RGB()
{
    for( int x = 0; x < m_imageContainer.width(); x++ )
        for( int y = 0; y < m_imageContainer.height(); y++ )
        {
            uint8_t R = ( float )Y[ x ][ y ] + 1.402f   * ( ( float )Cr[ x ][ y ] - 128.0f );
            uint8_t G = ( float )Y[ x ][ y ] - 0.34414f * ( ( float )Cb[ x ][ y ] - 128.0f ) - 0.71414f * ( ( float )Cr[ x ][ y ] - 128.0f );
            uint8_t B = ( float )Y[ x ][ y ] + 1.772f   * ( ( float )Cb[ x ][ y ] - 128.0f );
            m_imageContainer.setPixel( x, y, qRgb( R, G, B ) );
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
            Y[ x ][ y ] = 0.299f * ( float )qRed( p ) + 0.587f * ( float )qGreen( p ) + 0.114f * ( float )qBlue( p );
            Cb[ x ][ y ] = 0.564334f * ( float )( qBlue( p ) - Y[ x ][ y ] ) + 128.0f;
            Cr[ x ][ y ] = 0.713267f * ( float )( qRed( p ) - Y[ x ][ y ] ) + 128.0f;
        }

    dsCbCrWidth = 0;
    dsCbCrHeight = 0;
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
            m_renderarea.setPixel( x, y, qRgb( Y[ x ][ y ], Y[ x ][ y ], Y[ x ][ y ] ) );
        }
    repaint();
}

void RenderArea::ShowCb()
{
    for( int x = 0; x < m_renderarea.width(); x++ )
        for( int y = 0; y < m_renderarea.height(); y++ )
        {
            m_renderarea.setPixel( x, y, qRgb( Cb[ x ][ y ], Cb[ x ][ y ], Cb[ x ][ y ] ) );
        }
    repaint();
}

void RenderArea::ShowCr()
{
    for( int x = 0; x < m_renderarea.width(); x++ )
        for( int y = 0; y < m_renderarea.height(); y++ )
        {
            m_renderarea.setPixel( x, y, qRgb( Cr[ x ][ y ], Cr[ x ][ y ], Cr[ x ][ y ] ) );
        }
    repaint();
}

void RenderArea::ShowRGB()
{
    Render();
}

void RenderArea::Downsampling( DOWNSAMPLING downsampling )
{
    uint32_t xStep = 1;
    uint32_t yStep = 1;
    if( downsampling == DOWNSAMPLING_NONE )
    {
        dsCbCrWidth = m_imageContainer.width();
        dsCbCrHeight = m_imageContainer.height();
    }
    else if( downsampling == DOWNSAMPLING_2h2v )
    {
        dsCbCrWidth = m_imageContainer.width() / 2;
        dsCbCrHeight = m_imageContainer.height() / 2;
        xStep = 2;
        yStep = 2;
    }
    else if( downsampling == DOWNSAMPLING_2h1v )
    {
        dsCbCrWidth = m_imageContainer.width() / 2;
        dsCbCrHeight = m_imageContainer.height();
        xStep = 2;
        yStep = 1;
    }
    else if( downsampling == DOWNSAMPLING_1h2v )
    {
        dsCbCrWidth = m_imageContainer.width();
        dsCbCrHeight = m_imageContainer.height() / 2;
        xStep = 1;
        yStep = 2;
    }

    //
    for( uint32_t x = 0; x < dsCbCrWidth; x++ )
        for( uint32_t y = 0; y < dsCbCrHeight; y++ )
        {
            dsCb[ x ][ y ] = Cb[ x * xStep ][ y * yStep ];
            dsCr[ x ][ y ] = Cr[ x * xStep ][ y * yStep ];
        }
}

void RenderArea::DCT( uint8_t** inData, float** outDct, uint32_t width, uint32_t height )
{
    for( uint32_t bx = 0; bx < width / 8; bx++ )
        for( uint32_t by = 0; by < height / 8; by++ )
        {
            float temp[ 8 ][ 8 ];
            for( uint32_t i = 0; i < 8; i++ )
                for( uint32_t j = 0; j < 8; j++ )
                {
                    float sum = 0.0f;
                    for( uint8_t r = 0; r < 8; r++ )
                        sum += M[ i ][ r ] * inData[ bx * 8 + j ][ by * 8 + r ];
                    temp[ i ][ j ] = sum;
                }
            for( uint32_t i = 0; i < 8; i++ )
                for( uint32_t j = 0; j < 8; j++ )
                {
                    float sum = 0.0f;
                    for( uint8_t r = 0; r < 8; r++ )
                        sum += temp[ i ][ r ] * M[ j ][ r ];
                    outDct[ bx * 8 + j ][ by * 8 + i ] = sum;
                }
        }
}

void RenderArea::IDCT( uint8_t** outData, float** inDct, uint32_t width, uint32_t height )
{
    for( uint32_t bx = 0; bx < width / 8; bx++ )
        for( uint32_t by = 0; by < height / 8; by++ )
        {
            float temp[ 8 ][ 8 ];
            for( uint32_t i = 0; i < 8; i++ )
                for( uint32_t j = 0; j < 8; j++ )
                {
                    float sum = 0.0f;
                    for( uint8_t r = 0; r < 8; r++ )
                        sum += M[ r ][ i ] * inDct[ bx * 8 + j ][ by * 8 + r ];
                    temp[ i ][ j ] = sum;
                }
            for( uint32_t i = 0; i < 8; i++ )
                for( uint32_t j = 0; j < 8; j++ )
                {
                    float sum = 0.0f;
                    for( uint8_t r = 0; r < 8; r++ )
                        sum += temp[ i ][ r ] * M[ r ][ j ];
                    outData[ bx * 8 + j ][ by * 8 + i ] = sum;
                }
        }
}

void RenderArea::QuantizationMax( float** data, int32_t** outData, uint32_t width, uint32_t height, uint32_t n )
{
    struct ToSort
    {
        float val;
        uint32_t i;
        uint32_t j;
    };

    for( uint32_t bx = 0; bx < width / 8; bx++ )
        for( uint32_t by = 0; by < height / 8; by++ )
        {
            ToSort toSort[ 64 ];
            uint32_t c = 0;
            for( uint32_t i = 0; i < 8; i++ )
                for( uint32_t j = 0; j < 8; j++ )
                {
                    toSort[ c ].val = data[ bx * 8 + i ][ by * 8 + j ];
                    toSort[ c ].i = i;
                    toSort[ c ].j = j;
                    outData[ bx * 8 + i ][ by * 8 + j ] = 0;
                    c++;
                }
            std::sort( &toSort[ 0 ], &toSort[ 63 ], []( const ToSort& a, const ToSort& b)
                {
                    return a.val > b.val;
                });
            for( uint32_t i = 0; i < n; i++ )
            {
                outData[ bx * 8 + toSort[ i ].i ][ by * 8 + toSort[ i ].j ] = toSort[ i ].val;
            }
        }
}

void RenderArea::QuantizationAlfaGamma( float** data, int32_t** outData, uint32_t width, uint32_t height, uint32_t alfa, uint32_t gamma )
{
    float q[ 8 ][ 8 ];
    for( uint32_t i = 0; i < 8; i++ )
        for( uint32_t j = 0; j < 8; j++ )
            q[ i ][ j ] = alfa * ( 1 + gamma * ( i + j + 2 ) );
    QuantizationMatrix( data, outData, width, height, q );
}

void RenderArea::QuantizationMatrix( float** data, int32_t** outData, uint32_t width, uint32_t height, const float matrix[ 8 ][ 8 ] )
{
    for( uint32_t bx = 0; bx < width / 8; bx++ )
        for( uint32_t by = 0; by < height / 8; by++ )
        {
            for( uint32_t i = 0; i < 8; i++ )
                for( uint32_t j = 0; j < 8; j++ )
                    outData[ bx * 8 + i ][ by * 8 + j ] = data[ bx * 8 + i ][ by * 8 + j ] / matrix[ i ][ j ];
        }
}

void RenderArea::ZigZag( int32_t** inData, int32_t width, int32_t height, int32_t* outData )
{
    int32_t totalCounter = 0;
    for( int32_t bx = 0; bx < width / 8; bx++ )
        for( int32_t by = 0; by < height / 8; by++ )
        {
           for( int32_t c = 0; c < 64; c++ )
           {
               uint32_t index = g_zigzagMap[ c ];
               uint32_t i = index / 8;
               uint32_t j = index % 8;
               outData[ totalCounter++ ] = inData[ bx * 8 + i ][ by * 8 + j ];
           }
        }
}

void RenderArea::Deflate( const void* data, uint32_t dataLengh, void* out, uint32_t& outLength )
{
    z_stream defstream;
    defstream.zalloc = Z_NULL;
    defstream.zfree = Z_NULL;
    defstream.opaque = Z_NULL;
    defstream.avail_in = (uInt)dataLengh; // size of input
    defstream.next_in = (Bytef *)data; // input char array
    defstream.avail_out = (uInt)dataLengh; // size of output
    defstream.next_out = (Bytef *)out; // output char array

    deflateInit(&defstream, Z_DEFAULT_COMPRESSION);
    deflate(&defstream, Z_FINISH);
    deflateEnd(&defstream);

    outLength = ( char* )defstream.next_out - ( char* )out;
}

void RenderArea::Compress(DOWNSAMPLING downsampling, QUANTIZATION quantization, uint32_t qParam1, uint32_t qParam2 , uint32_t& uncompressed, uint32_t& compressed)
{
    Downsampling( downsampling );
    DCT( Y, dctY, m_imageContainer.width(), m_imageContainer.height() );
    DCT( dsCb, dctCb, dsCbCrWidth, dsCbCrHeight );
    DCT( dsCr, dctCr, dsCbCrWidth, dsCbCrHeight );

    int32_t** quantizedY  = new int32_t*[ 512 ];
    int32_t** quantizedCr = new int32_t*[ 512 ];
    int32_t** quantizedCb = new int32_t*[ 512 ];
    for( uint32_t i = 0; i < 512; i++ )
    {
        quantizedY [ i ] = new int32_t[ 512 ];
        quantizedCr[ i ] = new int32_t[ 512 ];
        quantizedCb[ i ] = new int32_t[ 512 ];
    }
    if( quantization == QUANTIZATION_MAX )
    {
        QuantizationMax( dctY, quantizedY, m_imageContainer.width(), m_imageContainer.height(), qParam1 );
        QuantizationMax( dctCb, quantizedCr, dsCbCrWidth, dsCbCrHeight, qParam2 );
        QuantizationMax( dctCr, quantizedCb, dsCbCrWidth, dsCbCrHeight, qParam2 );
    }
    else if( quantization == QUANTIZATION_ALFA_GAMMMA )
    {
        QuantizationAlfaGamma( dctY, quantizedY, m_imageContainer.width(), m_imageContainer.height(), qParam1, qParam2 );
        QuantizationAlfaGamma( dctCb, quantizedCr, dsCbCrWidth, dsCbCrHeight, qParam1, qParam2 );
        QuantizationAlfaGamma( dctCr, quantizedCb, dsCbCrWidth, dsCbCrHeight, qParam1, qParam2 );
    }
    else if( quantization == QUANTIZATION_STD_MATRIX )
    {
        QuantizationMatrix( dctY, quantizedY, m_imageContainer.width(), m_imageContainer.height(), g_stdQuantizationMatrixY );
        QuantizationMatrix( dctCb, quantizedCr, dsCbCrWidth, dsCbCrHeight, g_stdQuantizationMatrixCbCr );
        QuantizationMatrix( dctCr, quantizedCb, dsCbCrWidth, dsCbCrHeight, g_stdQuantizationMatrixCbCr );
    }

    int32_t YLine[ 512 * 512 ];
    int32_t CbLine[ 512 * 512 ];
    int32_t CrLine[ 512 * 512 ];
    uint32_t YLineLength = m_imageContainer.width() * m_imageContainer.height() * 3;
    uint32_t CbLineLength = dsCbCrWidth * dsCbCrHeight * 3;
    uint32_t CrLineLength = dsCbCrWidth * dsCbCrHeight * 3;
    ZigZag( quantizedY, m_imageContainer.width(), m_imageContainer.height(), YLine );
    ZigZag( quantizedCb, dsCbCrWidth, dsCbCrHeight, CbLine );
    ZigZag( quantizedCr, dsCbCrWidth, dsCbCrHeight, CrLine );

    float YCompressedline[ 512 * 512 ];
    float CbCompressedLine[ 512 * 512 ];
    float CrCompressedLine[ 512 * 512 ];
    uint32_t YCompressedLength;
    uint32_t CbCompressedLength;
    uint32_t CrCompressedLength;
    Deflate( YLine, YLineLength, YCompressedline, YCompressedLength );
    Deflate( CbLine, CbLineLength, CbCompressedLine, CbCompressedLength );
    Deflate( CrLine, CrLineLength, CrCompressedLine, CrCompressedLength );
    uncompressed = YLineLength + CbLineLength + CrLineLength;
    compressed = YCompressedLength + CbCompressedLength + CrCompressedLength;

    // decompress
    if( quantization == QUANTIZATION_MAX )
    {
        DequantizationMax( quantizedY, dctY, m_imageContainer.width(), m_imageContainer.height(), qParam1 );
        DequantizationMax( quantizedCr,dctCb, dsCbCrWidth, dsCbCrHeight, qParam2 );
        DequantizationMax( quantizedCb,dctCr, dsCbCrWidth, dsCbCrHeight, qParam2 );
    }
    else if( quantization == QUANTIZATION_ALFA_GAMMMA )
    {
        DequantizationAlfaGamma( quantizedY,  dctY,  m_imageContainer.width(), m_imageContainer.height(), qParam1, qParam2 );
        DequantizationAlfaGamma( quantizedCr, dctCb, dsCbCrWidth, dsCbCrHeight, qParam1, qParam2 );
        DequantizationAlfaGamma( quantizedCb, dctCr, dsCbCrWidth, dsCbCrHeight, qParam1, qParam2 );
    }
    else if( quantization == QUANTIZATION_STD_MATRIX )
    {
        DequantizationMatrix( quantizedY,  dctY,  m_imageContainer.width(), m_imageContainer.height(), g_stdQuantizationMatrixY );
        DequantizationMatrix( quantizedCr, dctCb, dsCbCrWidth, dsCbCrHeight, g_stdQuantizationMatrixCbCr );
        DequantizationMatrix( quantizedCb, dctCr, dsCbCrWidth, dsCbCrHeight, g_stdQuantizationMatrixCbCr );
    }

    IDCT( Y, dctY, m_imageContainer.width(), m_imageContainer.height() );
    IDCT( dsCb, dctCb, dsCbCrWidth, dsCbCrHeight );
    IDCT( dsCr, dctCr, dsCbCrWidth, dsCbCrHeight );
    Upsampling( downsampling );
    YCbCr2RGB();

    for( uint32_t i = 0; i < 512; i++ )
    {
        delete[] quantizedY[ i ];
        delete[] quantizedCr[ i ];
        delete[] quantizedCb[ i ];
    }
    delete[] quantizedY;
    delete[] quantizedCr;
    delete[] quantizedCb;
}

void RenderArea::Upsampling( DOWNSAMPLING downsampling )
{
    uint32_t xStep = 1;
    uint32_t yStep = 1;
    if( downsampling == DOWNSAMPLING_NONE )
    {
    }
    else if( downsampling == DOWNSAMPLING_2h2v )
    {
        xStep = 2;
        yStep = 2;
    }
    else if( downsampling == DOWNSAMPLING_2h1v )
    {
        xStep = 2;
        yStep = 1;
    }
    else if( downsampling == DOWNSAMPLING_1h2v )
    {
        xStep = 1;
        yStep = 2;
    }

    //
    for( int32_t x = 0; x < m_imageContainer.width(); x++ )
        for( int32_t y = 0; y < m_imageContainer.height(); y++ )
        {
            Cb[ x ][ y ] = dsCb[ x / xStep ][ y / yStep ];
            Cr[ x ][ y ] = dsCr[ x / xStep ][ y / yStep ];
        }
}

void RenderArea::DequantizationMax( int32_t** inData, float** outData, uint32_t width, uint32_t height, uint32_t n )
{
    for( uint32_t i = 0; i < width; i++ )
        for( uint32_t j = 0; j < height; j++ )
            outData[ i ][ j ] = inData[ i ][ j ];
}

void RenderArea::DequantizationAlfaGamma( int32_t** inData, float** outData, uint32_t width, uint32_t height, uint32_t alfa, uint32_t gamma )
{
    float q[ 8 ][ 8 ];
    for( uint32_t i = 0; i < 8; i++ )
        for( uint32_t j = 0; j < 8; j++ )
            q[ i ][ j ] = alfa * ( 1 + gamma * ( i + j + 2 ) );
    DequantizationMatrix( inData, outData, width, height, q );
}

void RenderArea::DequantizationMatrix( int32_t** inData, float** outData, uint32_t width, uint32_t height, const float matrix[ 8 ][ 8 ] )
{
    for( uint32_t bx = 0; bx < width / 8; bx++ )
        for( uint32_t by = 0; by < height / 8; by++ )
        {
            for( uint32_t i = 0; i < 8; i++ )
                for( uint32_t j = 0; j < 8; j++ )
                    outData[ bx * 8 + i ][ by * 8 + j ] = inData[ bx * 8 + i ][ by * 8 + j ] * matrix[ i ][ j ];
        }
}

void RenderArea::ShowDsCb()
{
    for( int x = 0; x < m_renderarea.width(); x++ )
        for( int y = 0; y < m_renderarea.height(); y++ )
        {
            uint8_t val = 255;
            if( x < ( int )dsCbCrWidth && y < ( int )dsCbCrHeight )
                val = dsCb[ x ][ y ];
            m_renderarea.setPixel( x, y, qRgb( val, val, val ) );
        }
    repaint();
}

void RenderArea::ShowDsCr()
{
    for( int x = 0; x < m_renderarea.width(); x++ )
        for( int y = 0; y < m_renderarea.height(); y++ )
        {
            uint8_t val = 255;
            if( x < ( int )dsCbCrWidth && y < ( int )dsCbCrHeight )
                val = dsCr[ x ][ y ];
            m_renderarea.setPixel( x, y, qRgb( val, val, val ) );
        }
    repaint();
}

void RenderArea::showDctY()
{
    for( int x = 0; x < m_renderarea.width(); x++ )
        for( int y = 0; y < m_renderarea.height(); y++ )
        {
            uint8_t val = dctY[ x ][ y ];
            m_renderarea.setPixel( x, y, qRgb( val, val, val ) );
        }
    repaint();
}

void RenderArea::showDctCb()
{
    for( int x = 0; x < m_renderarea.width(); x++ )
        for( int y = 0; y < m_renderarea.height(); y++ )
        {
            uint8_t val = 255;
            if( x < ( int )dsCbCrWidth && y < ( int )dsCbCrHeight )
                val = dctCb[ x ][ y ];
            m_renderarea.setPixel( x, y, qRgb( val, val, val ) );
        }
    repaint();
}

void RenderArea::showDctCr()
{
    for( int x = 0; x < m_renderarea.width(); x++ )
        for( int y = 0; y < m_renderarea.height(); y++ )
        {
            uint8_t val = 255;
            if( x < ( int )dsCbCrWidth && y < ( int )dsCbCrHeight )
                val = dctCr[ x ][ y ];
            m_renderarea.setPixel( x, y, qRgb( val, val, val ) );
        }
    repaint();
}

void RenderArea::paintEvent(QPaintEvent *event)
{
    QPainter painter( this );
    painter.drawImage( 0, 0, m_renderarea );
}
