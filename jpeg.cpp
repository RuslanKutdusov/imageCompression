#include "jpeg.h"

#include <algorithm>
#include <zlib.h>

#include "utils.h"

namespace jpeg
{
    //
    typedef int16_t quant_t;
    typedef YCbCr< quant_t > YCbCr_quant;

    //
    struct CompressedHeader
    {
        uLongf          yCompLength;
        uLongf          cbCompLength;
        uLongf          crCompLength;
        DOWNSAMPLING    downsampling;
        QUANTIZATION    quantization;
        uint32_t        param1;
        uint32_t        param2;
        uint32_t        param3;
        uint32_t        param4;
        uint32_t        Ywidth;
        uint32_t        Yheight;
        uint32_t        CbCrwidth;
        uint32_t        CbCrheight;
    };

    //
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

    const float g_stdQuantizationMatrixYHalf[ 8 ][ 8 ] = {
        { 16.0f * 0.5f,   11.0f * 0.5f,   10.0f * 0.5f,   16.0f * 0.5f,   24.0f * 0.5f,   40.0f * 0.5f,   51.0f * 0.5f,   61.0f * 0.5f  },
        { 12.0f * 0.5f,   12.0f * 0.5f,   14.0f * 0.5f,   19.0f * 0.5f,   26.0f * 0.5f,   58.0f * 0.5f,   60.0f * 0.5f,   55.0f * 0.5f  },
        { 14.0f * 0.5f,   13.0f * 0.5f,   16.0f * 0.5f,   24.0f * 0.5f,   40.0f * 0.5f,   57.0f * 0.5f,   69.0f * 0.5f,   56.0f * 0.5f  },
        { 14.0f * 0.5f,   17.0f * 0.5f,   22.0f * 0.5f,   29.0f * 0.5f,   51.0f * 0.5f,   87.0f * 0.5f,   80.0f * 0.5f,   62.0f * 0.5f  },
        { 18.0f * 0.5f,   22.0f * 0.5f,   37.0f * 0.5f,   56.0f * 0.5f,   68.0f * 0.5f,  109.0f * 0.5f,  103.0f * 0.5f,   77.0f * 0.5f  },
        { 24.0f * 0.5f,   35.0f * 0.5f,   55.0f * 0.5f,   64.0f * 0.5f,   81.0f * 0.5f,  104.0f * 0.5f,  113.0f * 0.5f,   92.0f * 0.5f  },
        { 49.0f * 0.5f,   64.0f * 0.5f,   78.0f * 0.5f,   87.0f * 0.5f,  103.0f * 0.5f,  121.0f * 0.5f,  120.0f * 0.5f,  101.0f * 0.5f  },
        { 72.0f * 0.5f,   92.0f * 0.5f,   95.0f * 0.5f,   98.0f * 0.5f,  112.0f * 0.5f,  100.0f * 0.5f,  103.0f * 0.5f,   99.0f * 0.5f  }
    };

    const float g_stdQuantizationMatrixCbCrHalf[ 8 ][ 8 ] = {
        { 17.0f * 0.5f,   18.0f * 0.5f,   24.0f * 0.5f,   47.0f * 0.5f,   99.0f * 0.5f,   99.0f * 0.5f,   99.0f * 0.5f,   99.0f * 0.5f },
        { 18.0f * 0.5f,   21.0f * 0.5f,   26.0f * 0.5f,   66.0f * 0.5f,   99.0f * 0.5f,   99.0f * 0.5f,   99.0f * 0.5f,   99.0f * 0.5f },
        { 24.0f * 0.5f,   26.0f * 0.5f,   56.0f * 0.5f,   99.0f * 0.5f,   99.0f * 0.5f,   99.0f * 0.5f,   99.0f * 0.5f,   99.0f * 0.5f },
        { 47.0f * 0.5f,   66.0f * 0.5f,   99.0f * 0.5f,   99.0f * 0.5f,   99.0f * 0.5f,   99.0f * 0.5f,   99.0f * 0.5f,   99.0f * 0.5f },
        { 99.0f * 0.5f,   99.0f * 0.5f,   99.0f * 0.5f,   99.0f * 0.5f,   99.0f * 0.5f,   99.0f * 0.5f,   99.0f * 0.5f,   99.0f * 0.5f },
        { 99.0f * 0.5f,   99.0f * 0.5f,   99.0f * 0.5f,   99.0f * 0.5f,   99.0f * 0.5f,   99.0f * 0.5f,   99.0f * 0.5f,   99.0f * 0.5f },
        { 99.0f * 0.5f,   99.0f * 0.5f,   99.0f * 0.5f,   99.0f * 0.5f,   99.0f * 0.5f,   99.0f * 0.5f,   99.0f * 0.5f,   99.0f * 0.5f },
        { 99.0f * 0.5f,   99.0f * 0.5f,   99.0f * 0.5f,   99.0f * 0.5f,   99.0f * 0.5f,   99.0f * 0.5f,   99.0f * 0.5f,   99.0f * 0.5f }
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

    float DCT_MATRIX[ 8 ][ 8 ];
    bool g_inited = false;


    //
    void Init()
    {
        if( g_inited )
            return;
        g_inited = true;

        const float PI = M_PI;

        for( uint8_t j = 0; j < 8; j++ )
        {
            DCT_MATRIX[ 0 ][ j ] = 1.0f / sqrt( 8.0f );
            for( uint8_t i = 1; i < 8; i++ )
                DCT_MATRIX[ i ][ j ] = 0.5f * cosf( ( 2.0f * ( float )j + 1.0f ) * ( float )i * PI / 16.0f );
        }
    }


    //
    void DownsamplingAndInitOutput( DOWNSAMPLING downsampling, const YCbCr_ubyte& input, YCbCr_ubyte& downsampledOutput )
    {
        uint32_t xStep = 1;
        uint32_t yStep = 1;
        uint32_t dsCbCrwidth = 0;
        uint32_t dsCbCrheight = 0;
        if( downsampling == DOWNSAMPLING_NONE )
        {
            dsCbCrwidth = input.Ywidth;
            dsCbCrheight = input.Yheight;
        }
        else if( downsampling == DOWNSAMPLING_2h2v )
        {
            dsCbCrwidth = input.Ywidth / 2;
            dsCbCrheight = input.Yheight / 2;
            xStep = 2;
            yStep = 2;
        }
        else if( downsampling == DOWNSAMPLING_2h1v )
        {
            dsCbCrwidth = input.Ywidth / 2;
            dsCbCrheight = input.Yheight;
            xStep = 2;
            yStep = 1;
        }
        else if( downsampling == DOWNSAMPLING_1h2v )
        {
            dsCbCrwidth = input.Ywidth;
            dsCbCrheight = input.Yheight / 2;
            xStep = 1;
            yStep = 2;
        }

        downsampledOutput.Init( input.Ywidth, input.Yheight, dsCbCrwidth, dsCbCrheight );

        //
        for( uint32_t x = 0; x < input.Ywidth; x++ )
            for( uint32_t y = 0; y < input.Yheight; y++ )
                downsampledOutput.Y[ x ][ y ] = input.Y[ x ][ y ];

        for( uint32_t x = 0; x < dsCbCrwidth; x++ )
            for( uint32_t y = 0; y < dsCbCrheight; y++ )
            {
                downsampledOutput.Cb[ x ][ y ] = input.Cb[ x * xStep ][ y * yStep ];
                downsampledOutput.Cr[ x ][ y ] = input.Cr[ x * xStep ][ y * yStep ];
            }
    }


    //
    void UpsamplingAndClamp( const YCbCr_int& input, YCbCr_ubyte& output, DOWNSAMPLING downsampling )
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
        for( uint32_t x = 0; x < input.Ywidth; x++ )
            for( uint32_t y = 0; y < input.Yheight; y++ )
            {
                output.Y[ x ][ y ] = clamp( input.Y[ x ][ y ], 0, 255 );
                output.Cb[ x ][ y ] = clamp( input.Cb[ x / xStep ][ y / yStep ], 0, 255 );
                output.Cr[ x ][ y ] = clamp( input.Cr[ x / xStep ][ y / yStep ], 0, 255 );
            }

        output.Ywidth       = input.Ywidth;
        output.Yheight      = input.Yheight;
        output.CbCrwidth    = input.CbCrwidth;
        output.CbCrheight   = input.CbCrheight;
    }


    //
    void DCT( uint8_t** inData, float** outDct, uint32_t width, uint32_t height )
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
                            sum += DCT_MATRIX[ i ][ r ] * inData[ bx * 8 + j ][ by * 8 + r ];
                        temp[ i ][ j ] = sum;
                    }
                for( uint32_t i = 0; i < 8; i++ )
                    for( uint32_t j = 0; j < 8; j++ )
                    {
                        float sum = 0.0f;
                        for( uint8_t r = 0; r < 8; r++ )
                            sum += temp[ i ][ r ] * DCT_MATRIX[ j ][ r ];
                        outDct[ bx * 8 + j ][ by * 8 + i ] = sum;
                    }
            }
    }


    //
    void IDCT( float** inDct, int32_t** outData, uint32_t width, uint32_t height )
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
                            sum += DCT_MATRIX[ r ][ i ] * inDct[ bx * 8 + j ][ by * 8 + r ];
                        temp[ i ][ j ] = sum;
                    }
                for( uint32_t i = 0; i < 8; i++ )
                    for( uint32_t j = 0; j < 8; j++ )
                    {
                        float sum = 0.0f;
                        for( uint8_t r = 0; r < 8; r++ )
                            sum += temp[ i ][ r ] * DCT_MATRIX[ r ][ j ];
                        outData[ bx * 8 + j ][ by * 8 + i ] = sum;
                    }
            }
    }


    //
    void QuantizationMax( float** inData, quant_t** outData, uint32_t width, uint32_t height, uint32_t n )
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
                        toSort[ c ].val = inData[ bx * 8 + i ][ by * 8 + j ];
                        toSort[ c ].i = i;
                        toSort[ c ].j = j;
                        outData[ bx * 8 + i ][ by * 8 + j ] = 0;
                        c++;
                    }
                std::sort( &toSort[ 0 ], &toSort[ 63 ], []( const ToSort& a, const ToSort& b)
                    {
                        return fabs( a.val ) > fabs( b.val );
                    });
                for( uint32_t i = 0; i < n && i < 64; i++ )
                {
                    outData[ bx * 8 + toSort[ i ].i ][ by * 8 + toSort[ i ].j ] = toSort[ i ].val;
                }
            }
    }


    //
    void QuantizationMatrix( float** inData, quant_t** outData, uint32_t width, uint32_t height, const float matrix[ 8 ][ 8 ] )
    {
        for( uint32_t bx = 0; bx < width / 8; bx++ )
            for( uint32_t by = 0; by < height / 8; by++ )
            {
                for( uint32_t i = 0; i < 8; i++ )
                    for( uint32_t j = 0; j < 8; j++ )
                        outData[ bx * 8 + i ][ by * 8 + j ] = inData[ bx * 8 + i ][ by * 8 + j ] / matrix[ i ][ j ];
            }
    }


    //
    void QuantizationAlfaGamma( float** inData, quant_t** outData, uint32_t width, uint32_t height, uint32_t alfa, uint32_t gamma )
    {
        float q[ 8 ][ 8 ];
        for( uint32_t i = 0; i < 8; i++ )
            for( uint32_t j = 0; j < 8; j++ )
                q[ i ][ j ] = alfa * ( 1 + gamma * ( i + j + 2 ) );
        QuantizationMatrix( inData, outData, width, height, q );
    }


    //
    void DequantizationMax( quant_t** inData, float** outData, uint32_t width, uint32_t height, uint32_t n )
    {
        for( uint32_t i = 0; i < width; i++ )
            for( uint32_t j = 0; j < height; j++ )
                outData[ i ][ j ] = inData[ i ][ j ];
    }


    //
    void DequantizationMatrix( quant_t** inData, float** outData, uint32_t width, uint32_t height, const float matrix[ 8 ][ 8 ] )
    {
        for( uint32_t bx = 0; bx < width / 8; bx++ )
            for( uint32_t by = 0; by < height / 8; by++ )
            {
                for( uint32_t i = 0; i < 8; i++ )
                    for( uint32_t j = 0; j < 8; j++ )
                        outData[ bx * 8 + i ][ by * 8 + j ] = inData[ bx * 8 + i ][ by * 8 + j ] * matrix[ i ][ j ];
            }
    }


    //
    void DequantizationAlfaGamma( quant_t** inData, float** outData, uint32_t width, uint32_t height, uint32_t alfa, uint32_t gamma )
    {
        float q[ 8 ][ 8 ];
        for( uint32_t i = 0; i < 8; i++ )
            for( uint32_t j = 0; j < 8; j++ )
                q[ i ][ j ] = alfa * ( 1 + gamma * ( i + j + 2 ) );
        DequantizationMatrix( inData, outData, width, height, q );
    }


    //
    void ZigZag( quant_t** inData, quant_t* outData, int32_t width, int32_t height )
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


    //
    void DeZigZag( quant_t* inData, quant_t** outData, int32_t width, int32_t height )
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
                   outData[ bx * 8 + i ][ by * 8 + j ] = inData[ totalCounter++ ];
               }
            }
    }


    //
    uint8_t* Compress( YCbCr_ubyte& input, DOWNSAMPLING downsampling, QUANTIZATION quantization, uint32_t qParam1, uint32_t qParam2, uint32_t qParam3, uint32_t qParam4, uint32_t& compressedLength )
    {
        if( input.Ywidth != input.Yheight )
        {
            // only square images
            return nullptr;
        }

        Init();

        YCbCr_ubyte downsampled;
        YCbCr_float dct;
        YCbCr_quant quantized;

        DownsamplingAndInitOutput( downsampling, input, downsampled );

        dct.Init( downsampled.Ywidth, downsampled.Yheight, downsampled.CbCrwidth, downsampled.CbCrheight );
        quantized.Init( downsampled.Ywidth, downsampled.Yheight, downsampled.CbCrwidth, downsampled.CbCrheight );

        DCT( downsampled.Y,   dct.Y,  downsampled.Ywidth,     downsampled.Yheight );
        DCT( downsampled.Cb,  dct.Cb, downsampled.CbCrwidth,  downsampled.CbCrheight );
        DCT( downsampled.Cr,  dct.Cr, downsampled.CbCrwidth,  downsampled.CbCrheight );

        if( quantization == QUANTIZATION_MAX )
        {
            QuantizationMax( dct.Y,  quantized.Y,   downsampled.Ywidth,     downsampled.Yheight,    qParam1 );
            QuantizationMax( dct.Cb, quantized.Cb,  downsampled.CbCrwidth,  downsampled.CbCrheight, qParam2 );
            QuantizationMax( dct.Cr, quantized.Cr,  downsampled.CbCrwidth,  downsampled.CbCrheight, qParam2 );
        }
        else if( quantization == QUANTIZATION_ALFA_GAMMMA )
        {
            QuantizationAlfaGamma( dct.Y,   quantized.Y,  downsampled.Ywidth,     downsampled.Yheight,      qParam1, qParam2 );
            QuantizationAlfaGamma( dct.Cb,  quantized.Cb, downsampled.CbCrwidth,  downsampled.CbCrheight,   qParam3, qParam4 );
            QuantizationAlfaGamma( dct.Cr,  quantized.Cr, downsampled.CbCrwidth,  downsampled.CbCrheight,   qParam3, qParam4 );
        }
        else if( quantization == QUANTIZATION_STD_MATRIX )
        {
            QuantizationMatrix( dct.Y,   quantized.Y,  downsampled.Ywidth,     downsampled.Yheight,     g_stdQuantizationMatrixY );
            QuantizationMatrix( dct.Cb,  quantized.Cb, downsampled.CbCrwidth,  downsampled.CbCrheight,  g_stdQuantizationMatrixCbCr );
            QuantizationMatrix( dct.Cr,  quantized.Cr, downsampled.CbCrwidth,  downsampled.CbCrheight,  g_stdQuantizationMatrixCbCr );
        }
        else if( quantization == QUANTIZATION_STD_MATRIX_HALF )
        {
            QuantizationMatrix( dct.Y,   quantized.Y,  downsampled.Ywidth,     downsampled.Yheight,     g_stdQuantizationMatrixYHalf );
            QuantizationMatrix( dct.Cb,  quantized.Cb, downsampled.CbCrwidth,  downsampled.CbCrheight,  g_stdQuantizationMatrixCbCrHalf );
            QuantizationMatrix( dct.Cr,  quantized.Cr, downsampled.CbCrwidth,  downsampled.CbCrheight,  g_stdQuantizationMatrixCbCrHalf );
        }

        uint32_t maxCompressedLength = downsampled.Ywidth * downsampled.Yheight * 3 * sizeof( quant_t );
        uint8_t* compressed = new uint8_t[ maxCompressedLength + sizeof( CompressedHeader )];

        CompressedHeader* header = ( CompressedHeader* )compressed;
        header->yCompLength     = compressBound( downsampled.Ywidth * downsampled.Yheight * sizeof( quant_t ) ); // Y compressed length
        header->cbCompLength    = compressBound( downsampled.CbCrwidth * downsampled.CbCrheight * sizeof( quant_t ) ); // Cb compressed length
        header->crCompLength    = header->cbCompLength; // Cr compressed length
        header->downsampling    = downsampling;
        header->quantization    = quantization;
        header->param1          = qParam1;
        header->param2          = qParam2;
        header->param3          = qParam3;
        header->param4          = qParam4;
        header->Ywidth          = downsampled.Ywidth;
        header->Yheight         = downsampled.Yheight;
        header->CbCrwidth       = downsampled.CbCrwidth;
        header->CbCrheight      = downsampled.CbCrheight;

        quant_t* line = new quant_t[ downsampled.Ywidth * downsampled.Yheight ];

        uint32_t lineLength =  downsampled.Ywidth * downsampled.Yheight * sizeof( quant_t );
        ZigZag( quantized.Y,    line,  downsampled.Ywidth,     downsampled.Yheight  );
        compress( ( Bytef* )( compressed + sizeof( CompressedHeader ) ),  &header->yCompLength,  ( const Bytef* )line, lineLength );
        compressedLength = header->yCompLength;

        lineLength =  downsampled.CbCrwidth * downsampled.CbCrheight * sizeof( quant_t );
        ZigZag( quantized.Cb,    line,  downsampled.CbCrwidth,     downsampled.CbCrheight  );
        compress( ( Bytef* )( compressed + sizeof( CompressedHeader ) + header->yCompLength ),  &header->cbCompLength,  ( const Bytef* )line, lineLength );
        compressedLength += header->cbCompLength;

        ZigZag( quantized.Cr,    line,  downsampled.CbCrwidth,     downsampled.CbCrheight  );
        compress( ( Bytef* )( compressed + sizeof( CompressedHeader ) + header->yCompLength + header->cbCompLength ),  &header->crCompLength,  ( const Bytef* )line, lineLength );
        compressedLength += header->crCompLength;

        delete[] line;

        return compressed;
    }



    //
    void Decompress( uint8_t* compressed, uint32_t compressedLength, YCbCr_ubyte& output )
    {
        CompressedHeader* header = ( CompressedHeader* )compressed;

        YCbCr_quant quantitazed;
        YCbCr_int downsampled;
        YCbCr_float dct;
        quantitazed.Init( header->Ywidth, header->Yheight, header->CbCrwidth, header->CbCrheight );
        downsampled.Init( header->Ywidth, header->Yheight, header->CbCrwidth, header->CbCrheight );
        dct.Init( header->Ywidth, header->Yheight, header->CbCrwidth, header->CbCrheight );

        quant_t* line = new quant_t[ header->Ywidth * header->Yheight ];

        uLongf lineLength = header->Ywidth * header->Yheight * sizeof( quant_t );
        uncompress( ( Bytef* )line, &lineLength, ( const Bytef* )( compressed + sizeof( CompressedHeader ) ), header->yCompLength );
        DeZigZag( line, quantitazed.Y, header->Ywidth, header->Yheight );

        lineLength = header->CbCrwidth * header->CbCrheight * sizeof( quant_t );
        uncompress( ( Bytef* )line, &lineLength, ( const Bytef* )( compressed + sizeof( CompressedHeader ) + header->yCompLength ), header->cbCompLength );
        DeZigZag( line, quantitazed.Cb, header->CbCrwidth, header->CbCrheight );

        lineLength = header->CbCrwidth * header->CbCrheight * sizeof( quant_t );
        uncompress( ( Bytef* )line, &lineLength, ( const Bytef* )( compressed + sizeof( CompressedHeader ) + header->yCompLength + header->cbCompLength ), header->crCompLength );
        DeZigZag( line, quantitazed.Cr, header->CbCrwidth, header->CbCrheight );

        delete[] line;

        // decompress
        if( header->quantization == QUANTIZATION_MAX )
        {
            DequantizationMax( quantitazed.Y,  dct.Y,   header->Ywidth,     header->Yheight,    header->param1 );
            DequantizationMax( quantitazed.Cb, dct.Cb,  header->CbCrwidth,  header->CbCrheight, header->param2 );
            DequantizationMax( quantitazed.Cr, dct.Cr,  header->CbCrwidth,  header->CbCrheight, header->param2 );
        }
        else if( header->quantization == QUANTIZATION_ALFA_GAMMMA )
        {
            DequantizationAlfaGamma( quantitazed.Y,  dct.Y,  header->Ywidth,     header->Yheight,      header->param1, header->param2 );
            DequantizationAlfaGamma( quantitazed.Cb, dct.Cb, header->CbCrwidth,  header->CbCrheight,   header->param3, header->param4 );
            DequantizationAlfaGamma( quantitazed.Cr, dct.Cr, header->CbCrwidth,  header->CbCrheight,   header->param3, header->param4 );
        }
        else if( header->quantization == QUANTIZATION_STD_MATRIX )
        {
            DequantizationMatrix( quantitazed.Y,  dct.Y,  header->Ywidth,     header->Yheight,     g_stdQuantizationMatrixY );
            DequantizationMatrix( quantitazed.Cb, dct.Cb, header->CbCrwidth,  header->CbCrheight,  g_stdQuantizationMatrixCbCr );
            DequantizationMatrix( quantitazed.Cr, dct.Cr, header->CbCrwidth,  header->CbCrheight,  g_stdQuantizationMatrixCbCr );
        }
        else if( header->quantization == QUANTIZATION_STD_MATRIX_HALF )
        {
            DequantizationMatrix( quantitazed.Y,  dct.Y,  header->Ywidth,     header->Yheight,     g_stdQuantizationMatrixYHalf );
            DequantizationMatrix( quantitazed.Cb, dct.Cb, header->CbCrwidth,  header->CbCrheight,  g_stdQuantizationMatrixCbCrHalf );
            DequantizationMatrix( quantitazed.Cr, dct.Cr, header->CbCrwidth,  header->CbCrheight,  g_stdQuantizationMatrixCbCrHalf );
        }

        IDCT( dct.Y,    downsampled.Y,  dct.Ywidth,     dct.Yheight );
        IDCT( dct.Cb,   downsampled.Cb, dct.CbCrwidth,  dct.CbCrheight );
        IDCT( dct.Cr,   downsampled.Cr, dct.CbCrwidth,  dct.CbCrheight );

        UpsamplingAndClamp( downsampled, output, header->downsampling );
    }

} // namespace jpeg
