#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include "QMessageBox"
#include <math.h>

#include "jpeg.h"
#include "wavelet.h"

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
    float sum = 0.0f;
    for( int x = 0; x < N; x++ )
        for( int y = 0; y < N; y++ )
        {
            QRgb rgb1 = imageWidget1->m_renderarea.pixel( x, y );
            QRgb rgb2 = imageWidget2->m_renderarea.pixel( x, y );
            float dr = qRed( rgb1 ) - qRed( rgb2 );
            float dg = qGreen( rgb1 ) - qGreen( rgb2 );
            float db = qBlue( rgb1 ) - qBlue( rgb2 );
            float diff = dr * dr + dg * dg + db * db;
            sum += diff;
        }
    m_psnr = 10.0f * log10( 3.0f * 255.0f * 255.0f * ( float )N * ( float )N  / sum );
    char buf[ 1024 ];
    sprintf( buf, "PSNR: %f", m_psnr );
    ui->PSNRLabel->setText( buf );
}

void MainWindow::on_pushButton_clicked()
{
    jpeg::DOWNSAMPLING ds = jpeg::DOWNSAMPLING_NONE;
    jpeg::QUANTIZATION q = jpeg::QUANTIZATION_MAX;
    if( ui->dsNone->isChecked() )
        ds = jpeg::DOWNSAMPLING_NONE;
    else if( ui->ds2h1v->isChecked() )
        ds = jpeg::DOWNSAMPLING_2h1v;
    else if( ui->ds2h2v->isChecked() )
        ds = jpeg::DOWNSAMPLING_2h2v;
    else if( ui->ds1h2v->isChecked() )
        ds = jpeg::DOWNSAMPLING_1h2v;
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
    uint32_t qParam3;
    uint32_t qParam4;
    if( ui->quantMax->isChecked() )
    {
        q = jpeg::QUANTIZATION_MAX;
        qParam1 = ui->Ny->text().toUInt();
        qParam2 = ui->Nc->text().toUInt();
    }
    else if( ui->quantAlfaGamma->isChecked() )
    {
        q = jpeg::QUANTIZATION_ALFA_GAMMMA;
        qParam1 = ui->alfa->text().toUInt();
        qParam2 = ui->gamma->text().toUInt();
        qParam3 = ui->alfaC->text().toUInt();
        qParam4 = ui->gammaC->text().toUInt();
    }
    else if( ui->quantStd->isChecked() )
    {
        q = jpeg::QUANTIZATION_STD_MATRIX;
    }
    else if( ui->quantStdHalf->isChecked() )
    {
        q = jpeg::QUANTIZATION_STD_MATRIX_HALF;
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

    uint32_t compressedLength;
    uint8_t* compressed = jpeg::Compress( imageWidget1->m_ycbcr, ds, q, qParam1, qParam2, qParam3, qParam4, compressedLength );
    jpeg::Decompress( compressed, compressedLength, imageWidget2->m_ycbcr );
    delete[] compressed;
    imageWidget2->YCbCr2RGB();
    imageWidget2->Render();

    char buf[ 1024 ];
    sprintf( buf, "Uncompressed: %u", imageWidget1->m_ycbcr.Ywidth * imageWidget1->m_ycbcr.Yheight * 3 / 1024 );
    ui->uncompressed->setText( buf );
    sprintf( buf, "Compressed: %u", compressedLength / 1024 );
    ui->compressed->setText( buf );
}

void MainWindow::on_dwtCompressBtn_clicked()
{
    uint32_t compLength;
    wavelet::WAVELET wv = wavelet::WAVELET_D2;
    if( ui->wvD2->isChecked() )
        wv = wavelet::WAVELET_D2;
    else if( ui->wvD4->isChecked() )
        wv = wavelet::WAVELET_D4;
    else if( ui->wvD6->isChecked() )
        wv = wavelet::WAVELET_D6;
    else if( ui->wvD8->isChecked() )
        wv = wavelet::WAVELET_D8;

    uint8_t* compressed = wavelet::Compress( imageWidget1->m_ycbcr, wv, ui->horizontalSlider->value(), compLength );
    wavelet::Decompress( compressed, imageWidget2->m_ycbcr );
    delete[] compressed;
    imageWidget2->YCbCr2RGB();
    imageWidget2->Render();

    char buf[ 1024 ];
    sprintf( buf, "Uncompressed: %u", ( imageWidget1->m_ycbcr.Ywidth * imageWidget1->m_ycbcr.Yheight * 3 ) / 1024 );
    ui->wvUncompressed->setText( buf );
    sprintf( buf, "Compressed: %u", compLength / 1024 );
    ui->wvCompressed->setText( buf );
}

void MainWindow::resetPSNR()
{
    m_psnr = 0.0f;
    ui->PSNRLabel->setText( "PSNR: -- " );
}
