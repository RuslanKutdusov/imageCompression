#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <stdint.h>

#include "jpeg.h"
#include "renderarea.h"

namespace Ui {
class MainWindow;
}


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

    void on_pushButton_clicked();

    void on_dwtCompressBtn_clicked();

protected:
    //void paintEvent(QPaintEvent *event);

private:
    Ui::MainWindow *ui;
    RenderArea* imageWidget1;
    RenderArea* imageWidget2;
    float m_psnr;

    void resetPSNR();
};

#endif // MAINWINDOW_H
