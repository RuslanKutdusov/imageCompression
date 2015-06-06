#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <stdint.h>

namespace Ui {
class MainWindow;
}

enum DOWNSAMPLING
{
    DOWNSAMPLING_NONE = 0,
    DOWNSAMPLING_2h1v,
    DOWNSAMPLING_2h2v,
    DOWNSAMPLING_1h2v
};

enum QUANTIZATION
{
    QUANTIZATION_MAX = 0,
    QUANTIZATION_ALFA_GAMMMA,
    QUANTIZATION_STD_MATRIX
};

class RenderArea : public QWidget
{
    Q_OBJECT

   public:
        RenderArea( QWidget* parent );
        ~RenderArea();
        void Render();
        void OpenImage( const QString& filename );
        void FillWhite();
        void FillBlack();
        void YCbCr2RGB();
        void CalcYCbCr();
        void ShowY();
        void ShowCb();
        void ShowCr();
        void ShowRGB();
        void ToGrayWeightAverage();
        void ToGrayCCIR601();

        // jpeg compress
        void Downsampling( DOWNSAMPLING downsampling );
        void DCT( uint8_t** inData, float** outDct, uint32_t width, uint32_t height );
        void IDCT( uint8_t** outData, float** inDct, uint32_t width, uint32_t height );
        void QuantizationMax( float** inData, int32_t** outData, uint32_t width, uint32_t height, uint32_t n );
        void QuantizationAlfaGamma( float** inData, int32_t** outData, uint32_t width, uint32_t height, uint32_t alfa, uint32_t gamma );
        void QuantizationMatrix(float** inData, int32_t** outData, uint32_t width, uint32_t height, const float matrix[ 8 ][ 8 ] );
        void ZigZag( int32_t** inData, int32_t width, int32_t height, int32_t* outData );
        void Deflate( const void* data, uint32_t dataLengh, void* out, uint32_t& outLength );
        void Compress(DOWNSAMPLING downsampling, QUANTIZATION quantization, uint32_t qParam1, uint32_t qParam2, uint32_t &uncompressed, uint32_t &compressed );

        // jpeg decompress
        void Upsampling( DOWNSAMPLING downsampling );
        void DequantizationMax( int32_t** inData, float** outData, uint32_t width, uint32_t height, uint32_t n );
        void DequantizationAlfaGamma( int32_t** inData, float** outData, uint32_t width, uint32_t height, uint32_t alfa, uint32_t gamma );
        void DequantizationMatrix( int32_t** inData, float** outData, uint32_t width, uint32_t height, const float matrix[ 8 ][ 8 ] );

        //
        void ShowDsCb();
        void ShowDsCr();
        void showDctY();
        void showDctCb();
        void showDctCr();

        //
        QImage m_renderarea;
        QImage m_imageContainer;
        uint8_t** Y ;
        uint8_t** Cb;
        uint8_t** Cr;

        uint32_t dsCbCrWidth;
        uint32_t dsCbCrHeight;
        uint8_t** dsCb;
        uint8_t** dsCr;

        float** dctY;
        float** dctCb;
        float** dctCr;

        float M[ 8 ][ 8 ];

   protected:
       void paintEvent(QPaintEvent *event);
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_image1Open_clicked();

    void on_image1Save_clicked();

    void on_Image2Open_clicked();

    void on_Image2Save_clicked();

    void on_calcPSNR_clicked();

    void on_image1Black_clicked();

    void on_image1White_clicked();

    void on_image1GrayWA_clicked();

    void on_image1GrayCCIR_clicked();

    void on_image2Black_clicked();

    void on_image2White_clicked();

    void on_image2GrayWA_clicked();

    void on_image2GrayCCIR_clicked();

    void on_Y1_clicked();

    void on_Cb1_clicked();

    void on_Cr1_clicked();

    void on_Y2_clicked();

    void on_Cb2_clicked();

    void on_Cr2_clicked();

    void on_RGB1_clicked();

    void on_RGB2_clicked();

    void on_transform_clicked();

    void on_transform2_clicked();

    void on_dsCb_clicked();

    void on_dsCr_clicked();

    void on_dctY_clicked();

    void on_dctCb_clicked();

    void on_dctCr_clicked();

    void on_pushButton_clicked();

protected:
    //void paintEvent(QPaintEvent *event);

private:
    Ui::MainWindow *ui;
    RenderArea* imageWidget1;
    RenderArea* imageWidget2;
    float m_psnr;
    DOWNSAMPLING m_downsampling;
    QUANTIZATION m_quantization;
    uint32_t        m_ny;
    uint32_t        m_nc;
    uint32_t        m_alfa;
    uint32_t        m_gamma;

    void resetPSNR();
};

#endif // MAINWINDOW_H
