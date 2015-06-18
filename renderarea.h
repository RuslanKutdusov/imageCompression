#pragma once
#include <QMainWindow>

#include "ycbcr.h"

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

        //
        QImage m_renderarea;
        QImage m_imageContainer;
        YCbCr_ubyte m_ycbcr;

   protected:
       void paintEvent(QPaintEvent *event);
};
