/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *image1Open;
    QPushButton *Image2Open;
    QPushButton *image1Save;
    QPushButton *Image2Save;
    QPushButton *image1Black;
    QPushButton *image1White;
    QPushButton *image1GrayWA;
    QPushButton *image1GrayCCIR;
    QPushButton *image2Black;
    QPushButton *image2GrayWA;
    QPushButton *image2GrayCCIR;
    QPushButton *image2White;
    QPushButton *Y1;
    QPushButton *Cb1;
    QPushButton *Cr1;
    QPushButton *Cb2;
    QPushButton *Y2;
    QPushButton *Cr2;
    QPushButton *RGB1;
    QPushButton *RGB2;
    QPushButton *transform;
    QPushButton *transform2;
    QTabWidget *tabWidget;
    QWidget *tab;
    QPushButton *dctCr;
    QPushButton *dsCr;
    QPushButton *dsCb;
    QPushButton *dctY;
    QPushButton *dctCb;
    QGroupBox *groupBox;
    QRadioButton *dsNone;
    QRadioButton *ds2h1v;
    QRadioButton *ds1h2v;
    QRadioButton *ds2h2v;
    QGroupBox *groupBox_2;
    QRadioButton *quantMax;
    QRadioButton *quantAlfaGamma;
    QRadioButton *quantStd;
    QLabel *label;
    QLabel *label_2;
    QSpinBox *Ny;
    QSpinBox *Nc;
    QLabel *label_3;
    QLabel *label_4;
    QSpinBox *gamma;
    QSpinBox *alfa;
    QLabel *label_5;
    QLabel *label_6;
    QSpinBox *alfaC;
    QSpinBox *gammaC;
    QPushButton *pushButton;
    QLabel *uncompressed;
    QLabel *compressed;
    QRadioButton *quantStdHalf;
    QWidget *tab_2;
    QPushButton *calcPSNR;
    QLabel *PSNRLabel;
    QWidget *tab_3;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QRadioButton *radioButton_3;
    QRadioButton *radioButton_4;
    QSlider *horizontalSlider;
    QLabel *label_7;
    QPushButton *dwtCompressBtn;
    QMenuBar *menuBar;
    QButtonGroup *buttonGroup;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1040, 820);
        MainWindow->setMinimumSize(QSize(1040, 676));
        MainWindow->setMaximumSize(QSize(1040, 820));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        image1Open = new QPushButton(centralWidget);
        image1Open->setObjectName(QStringLiteral("image1Open"));
        image1Open->setGeometry(QRect(0, 515, 61, 27));
        Image2Open = new QPushButton(centralWidget);
        Image2Open->setObjectName(QStringLiteral("Image2Open"));
        Image2Open->setGeometry(QRect(520, 515, 61, 27));
        image1Save = new QPushButton(centralWidget);
        image1Save->setObjectName(QStringLiteral("image1Save"));
        image1Save->setGeometry(QRect(60, 515, 61, 27));
        Image2Save = new QPushButton(centralWidget);
        Image2Save->setObjectName(QStringLiteral("Image2Save"));
        Image2Save->setGeometry(QRect(580, 515, 61, 27));
        image1Black = new QPushButton(centralWidget);
        image1Black->setObjectName(QStringLiteral("image1Black"));
        image1Black->setGeometry(QRect(120, 515, 61, 27));
        image1White = new QPushButton(centralWidget);
        image1White->setObjectName(QStringLiteral("image1White"));
        image1White->setGeometry(QRect(180, 515, 61, 27));
        image1GrayWA = new QPushButton(centralWidget);
        image1GrayWA->setObjectName(QStringLiteral("image1GrayWA"));
        image1GrayWA->setGeometry(QRect(240, 515, 151, 27));
        image1GrayCCIR = new QPushButton(centralWidget);
        image1GrayCCIR->setObjectName(QStringLiteral("image1GrayCCIR"));
        image1GrayCCIR->setGeometry(QRect(0, 540, 151, 27));
        image2Black = new QPushButton(centralWidget);
        image2Black->setObjectName(QStringLiteral("image2Black"));
        image2Black->setGeometry(QRect(640, 515, 61, 27));
        image2GrayWA = new QPushButton(centralWidget);
        image2GrayWA->setObjectName(QStringLiteral("image2GrayWA"));
        image2GrayWA->setGeometry(QRect(760, 515, 151, 27));
        image2GrayCCIR = new QPushButton(centralWidget);
        image2GrayCCIR->setObjectName(QStringLiteral("image2GrayCCIR"));
        image2GrayCCIR->setGeometry(QRect(520, 540, 151, 27));
        image2White = new QPushButton(centralWidget);
        image2White->setObjectName(QStringLiteral("image2White"));
        image2White->setGeometry(QRect(700, 515, 61, 27));
        Y1 = new QPushButton(centralWidget);
        Y1->setObjectName(QStringLiteral("Y1"));
        Y1->setGeometry(QRect(150, 540, 31, 27));
        Cb1 = new QPushButton(centralWidget);
        Cb1->setObjectName(QStringLiteral("Cb1"));
        Cb1->setGeometry(QRect(180, 540, 31, 27));
        Cr1 = new QPushButton(centralWidget);
        Cr1->setObjectName(QStringLiteral("Cr1"));
        Cr1->setGeometry(QRect(210, 540, 31, 27));
        Cb2 = new QPushButton(centralWidget);
        Cb2->setObjectName(QStringLiteral("Cb2"));
        Cb2->setGeometry(QRect(700, 540, 31, 27));
        Y2 = new QPushButton(centralWidget);
        Y2->setObjectName(QStringLiteral("Y2"));
        Y2->setGeometry(QRect(670, 540, 31, 27));
        Cr2 = new QPushButton(centralWidget);
        Cr2->setObjectName(QStringLiteral("Cr2"));
        Cr2->setGeometry(QRect(730, 540, 31, 27));
        RGB1 = new QPushButton(centralWidget);
        RGB1->setObjectName(QStringLiteral("RGB1"));
        RGB1->setGeometry(QRect(240, 540, 41, 27));
        RGB2 = new QPushButton(centralWidget);
        RGB2->setObjectName(QStringLiteral("RGB2"));
        RGB2->setGeometry(QRect(760, 540, 41, 27));
        transform = new QPushButton(centralWidget);
        transform->setObjectName(QStringLiteral("transform"));
        transform->setGeometry(QRect(280, 540, 141, 27));
        transform2 = new QPushButton(centralWidget);
        transform2->setObjectName(QStringLiteral("transform2"));
        transform2->setGeometry(QRect(800, 540, 141, 27));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(2, 570, 671, 211));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        dctCr = new QPushButton(tab);
        dctCr->setObjectName(QStringLiteral("dctCr"));
        dctCr->setGeometry(QRect(140, 120, 99, 27));
        dsCr = new QPushButton(tab);
        dsCr->setObjectName(QStringLiteral("dsCr"));
        dsCr->setGeometry(QRect(10, 150, 131, 27));
        dsCb = new QPushButton(tab);
        dsCb->setObjectName(QStringLiteral("dsCb"));
        dsCb->setGeometry(QRect(10, 120, 131, 27));
        dctY = new QPushButton(tab);
        dctY->setObjectName(QStringLiteral("dctY"));
        dctY->setGeometry(QRect(240, 120, 99, 27));
        dctCb = new QPushButton(tab);
        dctCb->setObjectName(QStringLiteral("dctCb"));
        dctCb->setGeometry(QRect(140, 150, 99, 27));
        groupBox = new QGroupBox(tab);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 0, 121, 101));
        groupBox->setFlat(true);
        groupBox->setCheckable(false);
        dsNone = new QRadioButton(groupBox);
        dsNone->setObjectName(QStringLiteral("dsNone"));
        dsNone->setGeometry(QRect(10, 20, 117, 22));
        dsNone->setChecked(true);
        ds2h1v = new QRadioButton(groupBox);
        ds2h1v->setObjectName(QStringLiteral("ds2h1v"));
        ds2h1v->setGeometry(QRect(10, 40, 117, 22));
        ds1h2v = new QRadioButton(groupBox);
        ds1h2v->setObjectName(QStringLiteral("ds1h2v"));
        ds1h2v->setGeometry(QRect(10, 80, 117, 22));
        ds2h2v = new QRadioButton(groupBox);
        ds2h2v->setObjectName(QStringLiteral("ds2h2v"));
        ds2h2v->setGeometry(QRect(10, 60, 117, 22));
        groupBox_2 = new QGroupBox(tab);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(150, 0, 421, 101));
        quantMax = new QRadioButton(groupBox_2);
        buttonGroup = new QButtonGroup(MainWindow);
        buttonGroup->setObjectName(QStringLiteral("buttonGroup"));
        buttonGroup->addButton(quantMax);
        quantMax->setObjectName(QStringLiteral("quantMax"));
        quantMax->setGeometry(QRect(10, 20, 21, 22));
        quantAlfaGamma = new QRadioButton(groupBox_2);
        buttonGroup->addButton(quantAlfaGamma);
        quantAlfaGamma->setObjectName(QStringLiteral("quantAlfaGamma"));
        quantAlfaGamma->setGeometry(QRect(10, 46, 21, 22));
        quantStd = new QRadioButton(groupBox_2);
        buttonGroup->addButton(quantStd);
        quantStd->setObjectName(QStringLiteral("quantStd"));
        quantStd->setGeometry(QRect(10, 72, 141, 22));
        quantStd->setChecked(true);
        label = new QLabel(groupBox_2);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(33, 22, 21, 17));
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(115, 22, 21, 17));
        Ny = new QSpinBox(groupBox_2);
        Ny->setObjectName(QStringLiteral("Ny"));
        Ny->setGeometry(QRect(60, 18, 48, 24));
        Ny->setValue(1);
        Nc = new QSpinBox(groupBox_2);
        Nc->setObjectName(QStringLiteral("Nc"));
        Nc->setGeometry(QRect(140, 18, 48, 24));
        Nc->setValue(1);
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(115, 48, 21, 17));
        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(33, 48, 21, 17));
        gamma = new QSpinBox(groupBox_2);
        gamma->setObjectName(QStringLiteral("gamma"));
        gamma->setGeometry(QRect(140, 46, 48, 24));
        gamma->setValue(2);
        alfa = new QSpinBox(groupBox_2);
        alfa->setObjectName(QStringLiteral("alfa"));
        alfa->setGeometry(QRect(60, 46, 48, 24));
        alfa->setValue(1);
        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(193, 48, 21, 17));
        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(275, 48, 21, 17));
        alfaC = new QSpinBox(groupBox_2);
        alfaC->setObjectName(QStringLiteral("alfaC"));
        alfaC->setGeometry(QRect(220, 46, 48, 24));
        alfaC->setValue(1);
        gammaC = new QSpinBox(groupBox_2);
        gammaC->setObjectName(QStringLiteral("gammaC"));
        gammaC->setGeometry(QRect(300, 46, 48, 24));
        gammaC->setValue(4);
        pushButton = new QPushButton(tab);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(350, 120, 99, 27));
        uncompressed = new QLabel(tab);
        uncompressed->setObjectName(QStringLiteral("uncompressed"));
        uncompressed->setGeometry(QRect(460, 120, 181, 17));
        compressed = new QLabel(tab);
        compressed->setObjectName(QStringLiteral("compressed"));
        compressed->setGeometry(QRect(460, 140, 191, 17));
        quantStdHalf = new QRadioButton(tab);
        buttonGroup->addButton(quantStdHalf);
        quantStdHalf->setObjectName(QStringLiteral("quantStdHalf"));
        quantStdHalf->setGeometry(QRect(160, 98, 141, 22));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        calcPSNR = new QPushButton(tab_2);
        calcPSNR->setObjectName(QStringLiteral("calcPSNR"));
        calcPSNR->setGeometry(QRect(10, 10, 99, 27));
        PSNRLabel = new QLabel(tab_2);
        PSNRLabel->setObjectName(QStringLiteral("PSNRLabel"));
        PSNRLabel->setGeometry(QRect(10, 40, 151, 17));
        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        radioButton = new QRadioButton(tab_3);
        radioButton->setObjectName(QStringLiteral("radioButton"));
        radioButton->setGeometry(QRect(20, 10, 61, 22));
        radioButton_2 = new QRadioButton(tab_3);
        radioButton_2->setObjectName(QStringLiteral("radioButton_2"));
        radioButton_2->setGeometry(QRect(20, 30, 51, 22));
        radioButton_3 = new QRadioButton(tab_3);
        radioButton_3->setObjectName(QStringLiteral("radioButton_3"));
        radioButton_3->setGeometry(QRect(20, 50, 51, 22));
        radioButton_4 = new QRadioButton(tab_3);
        radioButton_4->setObjectName(QStringLiteral("radioButton_4"));
        radioButton_4->setGeometry(QRect(20, 70, 51, 22));
        horizontalSlider = new QSlider(tab_3);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(100, 30, 160, 29));
        horizontalSlider->setMaximum(255);
        horizontalSlider->setOrientation(Qt::Horizontal);
        horizontalSlider->setTickPosition(QSlider::TicksBelow);
        label_7 = new QLabel(tab_3);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(100, 10, 91, 17));
        dwtCompressBtn = new QPushButton(tab_3);
        dwtCompressBtn->setObjectName(QStringLiteral("dwtCompressBtn"));
        dwtCompressBtn->setGeometry(QRect(90, 80, 99, 27));
        tabWidget->addTab(tab_3, QString());
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1040, 25));
        MainWindow->setMenuBar(menuBar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        image1Open->setText(QApplication::translate("MainWindow", "Open", 0));
        Image2Open->setText(QApplication::translate("MainWindow", "Open", 0));
        image1Save->setText(QApplication::translate("MainWindow", "Save", 0));
        Image2Save->setText(QApplication::translate("MainWindow", "Save", 0));
        image1Black->setText(QApplication::translate("MainWindow", "Black", 0));
        image1White->setText(QApplication::translate("MainWindow", "White", 0));
        image1GrayWA->setText(QApplication::translate("MainWindow", "Gray weight avarege", 0));
        image1GrayCCIR->setText(QApplication::translate("MainWindow", "Gray CCIR 601-1", 0));
        image2Black->setText(QApplication::translate("MainWindow", "Black", 0));
        image2GrayWA->setText(QApplication::translate("MainWindow", "Gray weight avarege", 0));
        image2GrayCCIR->setText(QApplication::translate("MainWindow", "Gray CCIR 601-1", 0));
        image2White->setText(QApplication::translate("MainWindow", "White", 0));
        Y1->setText(QApplication::translate("MainWindow", "Y", 0));
        Cb1->setText(QApplication::translate("MainWindow", "Cb", 0));
        Cr1->setText(QApplication::translate("MainWindow", "Cr", 0));
        Cb2->setText(QApplication::translate("MainWindow", "Cb", 0));
        Y2->setText(QApplication::translate("MainWindow", "Y", 0));
        Cr2->setText(QApplication::translate("MainWindow", "Cr", 0));
        RGB1->setText(QApplication::translate("MainWindow", "RGB", 0));
        RGB2->setText(QApplication::translate("MainWindow", "RGB", 0));
        transform->setText(QApplication::translate("MainWindow", "RGB->YCbCr->RGB", 0));
        transform2->setText(QApplication::translate("MainWindow", "RGB->YCbCr->RGB", 0));
        dctCr->setText(QApplication::translate("MainWindow", "DCT Cr", 0));
        dsCr->setText(QApplication::translate("MainWindow", "Downsampled Cr", 0));
        dsCb->setText(QApplication::translate("MainWindow", "Downsampled Cb", 0));
        dctY->setText(QApplication::translate("MainWindow", "DCT Y", 0));
        dctCb->setText(QApplication::translate("MainWindow", "DCT Cb", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "Downsampling:", 0));
        dsNone->setText(QApplication::translate("MainWindow", "None", 0));
        ds2h1v->setText(QApplication::translate("MainWindow", "2h1v", 0));
        ds1h2v->setText(QApplication::translate("MainWindow", "1h2v", 0));
        ds2h2v->setText(QApplication::translate("MainWindow", "2h2v", 0));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Quantization:", 0));
        quantMax->setText(QApplication::translate("MainWindow", "RadioButton", 0));
        quantAlfaGamma->setText(QApplication::translate("MainWindow", "RadioButton", 0));
        quantStd->setText(QApplication::translate("MainWindow", "Std. matrix", 0));
        label->setText(QApplication::translate("MainWindow", "Ny:", 0));
        label_2->setText(QApplication::translate("MainWindow", "Nc:", 0));
        label_3->setText(QApplication::translate("MainWindow", "Yg:", 0));
        label_4->setText(QApplication::translate("MainWindow", "Ya:", 0));
        label_5->setText(QApplication::translate("MainWindow", "Ca:", 0));
        label_6->setText(QApplication::translate("MainWindow", "Cg:", 0));
        pushButton->setText(QApplication::translate("MainWindow", "Compress", 0));
        uncompressed->setText(QApplication::translate("MainWindow", "Uncompressed: --", 0));
        compressed->setText(QApplication::translate("MainWindow", "Compressed: --", 0));
        quantStdHalf->setText(QApplication::translate("MainWindow", "Std. matrix div by 2", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "JPEG", 0));
        calcPSNR->setText(QApplication::translate("MainWindow", "calcPSNR", 0));
        PSNRLabel->setText(QApplication::translate("MainWindow", "PSNR: --", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "PSNR", 0));
        radioButton->setText(QApplication::translate("MainWindow", "D2", 0));
        radioButton_2->setText(QApplication::translate("MainWindow", "D4", 0));
        radioButton_3->setText(QApplication::translate("MainWindow", "D6", 0));
        radioButton_4->setText(QApplication::translate("MainWindow", "D8", 0));
        label_7->setText(QApplication::translate("MainWindow", "Threshold:", 0));
        dwtCompressBtn->setText(QApplication::translate("MainWindow", "Compress", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("MainWindow", "Wavelet", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
