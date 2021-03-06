#include "wavelet.h"
#include <math.h>
#include <zlib.h>
#include <string.h>

#include "utils.h"

namespace wavelet
{
    const float g_d2[] = { 1.0f / sqrtf( 2.0f ), 1.0f / sqrtf( 2.0f ) };
    const float g_d4[] = { 0.6830127f / sqrtf( 2.0f ), 1.183027f / sqrtf( 2.0f ), 0.3169873f / sqrtf( 2.0f ), -0.183027f / sqrtf( 2.0f ) };
    const float g_d6[] = { 0.47046721f / sqrtf( 2.0f ), 1.14111692f / sqrtf( 2.0f ), 0.650365f / sqrtf( 2.0f ), -0.19093442 / sqrtf( 2.0f ),
                            -0.12083221f / sqrtf( 2.0f ), 0.0498175 / sqrtf( 2.0f ) };
    const float g_d8[] = { 0.32580343f / sqrtf( 2.0f ), 1.01094572f / sqrtf( 2.0f ), 0.8922014f / sqrtf( 2.0f ), -0.03967503f / sqrtf( 2.0f ),
                           -0.26450717f / sqrtf( 2.0f ), 0.0436163f / sqrtf( 2.0f ), 0.0465036f / sqrtf( 2.0f ), -0.01498699f / sqrtf( 2.0f ) };
    const int32_t g_waveletCoeffsNum[ WAVELET_COUNT ] = { 2, 4, 6, 8 };
    const uint32_t MIN_WIDTH_HEIGHT = 16;

    typedef int16_t quant_t;


    //
    struct CompressedHeader
    {
        uint32_t    yCompLength;
        uint32_t    cbCompLength;
        uint32_t    crCompLength;
        WAVELET     wavelet;
        uint32_t    Ywidth;
        uint32_t    Yheight;
        uint32_t    CbCrwidth;
        uint32_t    CbCrheight;
    };


    //
    void GetHpfCoeffs( const float* cl, int32_t n, float* ch )
    {
        float sign = -1.0f;
        for( int32_t i = 0; i < n; i++ )
        {
            sign *= -1.0f;
            ch[ i ] = sign * cl[ n - i - 1 ];
        }
    }


    //
    void GetICoeffs( const float* cl, const float* ch, int32_t n, float* icl, float* ich )
    {
        for( int32_t k = 0; k < n; k += 2 )
        {
            ich[ k + 0 ] = cl[ n - k - 1 ];
            icl[ k + 0 ] = cl[ n - k - 2 ];

            ich[ k + 1 ] = ch[ n - k - 1 ];
            icl[ k + 1 ] = ch[ n - k - 2 ];
        }
    }


    //
    void DWT1( float* inData, float* outData, int32_t dataLen, int32_t width, const float* cl, const float* ch, int32_t coeffsNum, int32_t delta )
    {
        for( int32_t k = 0; k < dataLen; k += 2 )
        {
            float lf = 0.0f;
            float hf = 0.0f;
            for( int32_t i = 0; i < coeffsNum; i++ )
            {
                int32_t index = k + i - delta;
                index = index >= 0 ? index : dataLen + index;
                lf += inData[ ( index % dataLen ) * width ] * cl[ i ];
                hf += inData[ ( index % dataLen ) * width ] * ch[ i ];
            }
            outData[ ( k + 0 ) * width ] = lf;
            outData[ ( k + 1 ) * width ] = hf;
        }
    }


    //
    void DWT2_recursive( float* imageFloat, float* temp, uint32_t width, uint32_t height, uint32_t originWidth, const float* cl, const float* ch, int32_t coeffsNum )
    {
        if( width < MIN_WIDTH_HEIGHT )
            return;

        for( uint32_t i = 0; i < height; i++ )
            DWT1( &imageFloat[ i * originWidth ], &temp[ i * originWidth ], width, 1, cl, ch, coeffsNum, 0 );
        for( uint32_t i = 0; i < width; i++ )
            DWT1( &temp[ i ], &imageFloat[ i ], height, originWidth, cl, ch, coeffsNum, 0 );

        for( uint32_t i = 0; i < height; i++ )
        {
            for( uint32_t j = 0; j < width; j++ )
            {
                uint32_t k = ( j % 2 ) ? ( width / 2 + j / 2 ) : ( j / 2 );
                temp[ i * width + k ] = imageFloat[ i * width + j ];
            }
        }

        for( uint32_t j = 0; j < width; j++ )
        {
            for( uint32_t i = 0; i < height; i++ )
            {
                uint32_t k = ( i % 2 ) ? ( height / 2 + i / 2 ) : ( i / 2 );
                imageFloat[ k * width + j ] = temp[ i * width + j ];
            }
        }

        DWT2_recursive( imageFloat, temp, width / 2, height / 2, originWidth, cl, ch, coeffsNum );
    }


    //
    void IDWT2_recursive( float* imageFloat, float* temp, uint32_t width, uint32_t height, uint32_t originWidth, const float* icl, const float* ich, int32_t coeffsNum )
    {
        if( width > originWidth )
            return;

        for( uint32_t j = 0; j < width; j++ )
        {
            for( uint32_t i = 0; i < height; i++ )
            {
                uint32_t k = ( i % 2 ) ? ( height / 2 + i / 2 ) : ( i / 2 );
                temp[ i * width + j ] = imageFloat[ k * width + j ];
            }
        }

        for( uint32_t i = 0; i < height; i++ )
        {
            for( uint32_t j = 0; j < width; j++ )
            {
                uint32_t k = ( j % 2 ) ? ( width / 2 + j / 2 ) : ( j / 2 );
                imageFloat[ i * width + j ] = temp[ i * width + k ];
            }
        }

        for( uint32_t i = 0; i < width; i++ )
            DWT1( &imageFloat[ i ], &temp[ i ], height, originWidth, icl, ich, coeffsNum, coeffsNum - 2 );
        for( uint32_t i = 0; i < height; i++ )
            DWT1( &temp[ i * originWidth ], &imageFloat[ i * originWidth ], width, 1, icl, ich, coeffsNum, coeffsNum - 2 );

        IDWT2_recursive( imageFloat, temp, width * 2, height * 2, originWidth, icl, ich, coeffsNum );
    }


    //
    void QuantizationThreshold( const float* inImageFloat, quant_t* outImageInt, uint32_t length, uint32_t threshold )
    {
        for( uint32_t i = 0; i < length; i++ )
            outImageInt[ i ] = fabs( inImageFloat[ i ] ) > threshold ? inImageFloat[ i ] : 0.0f;
    }


    //
    void DequantizationThreshold( const quant_t* inImageInt, float* outImageFloat, uint32_t length )
    {
        for( uint32_t i = 0; i < length; i++ )
            outImageFloat[ i ] = inImageInt[ i ];
    }


    //
    uint8_t* DWT2Compress( uint8_t** inData, uint32_t width, uint32_t height, uint8_t threshold, WAVELET wavelet, uint32_t& compressedLength )
    {
    //    float data[] = { 0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f };
    //    float result[ 8 ];
    //    WAVELET wavelet = WAVELET_D8;
    //    int32_t coeffsNum = g_waveletCoeffsNum[ wavelet ];
    //    const float* cl;
    //    float ch[ 8 ], icl[ 8 ], ich[ 8 ];
    //    switch( wavelet )
    //    {
    //        case( WAVELET_D2 ):
    //            cl = g_d2;
    //            break;
    //        case( WAVELET_D4 ):
    //            cl = g_d4;
    //            break;
    //        case( WAVELET_D6 ):
    //            cl = g_d6;
    //            break;
    //        case( WAVELET_D8 ):
    //            cl = g_d8;
    //            break;
    //    }
    //    GetHpfCoeffs( cl, coeffsNum, ch );
    //    GetICoeffs( cl, ch, coeffsNum, icl, ich );
    //    DWT1( data, result, sizeof( data ) / sizeof( data[ 0 ] ), cl, ch, coeffsNum, 0 );
    //    DWT1( result, data, sizeof( data ) / sizeof( data[ 0 ] ), icl, ich, coeffsNum, coeffsNum - 2 );
    //    DWT1( data, result, sizeof( data ) / sizeof( data[ 0 ] ), icl, ich, coeffsNum, coeffsNum - 2 );

        int32_t coeffsNum = g_waveletCoeffsNum[ wavelet ];
        const float* cl;
        float ch[ 8 ], icl[ 8 ], ich[ 8 ];
        switch( wavelet )
        {
            case( WAVELET_D2 ):
                cl = g_d2;
                break;
            case( WAVELET_D4 ):
                cl = g_d4;
                break;
            case( WAVELET_D6 ):
                cl = g_d6;
                break;
            case( WAVELET_D8 ):
                cl = g_d8;
                break;
            default:
                return nullptr;
        }
        GetHpfCoeffs( cl, coeffsNum, ch );
        GetICoeffs( cl, ch, coeffsNum, icl, ich );

        uint32_t length = width * height;
        float* imageFloat = new float[ length ];
        float* temp = new float[ length ];
        quant_t* imageInt = new quant_t[ length ];

        uint8_t* compressed = new uint8_t[ length * sizeof( quant_t ) ];
        uLongf l_compressedLength = compressBound( length * sizeof( quant_t ) );

        for( uint32_t i = 0; i < height; i++ )
        {
            for( uint32_t j = 0; j < width; j++ )
                imageFloat[ i * width + j ] = inData[ j ][ i ];
        }

        // compress
        DWT2_recursive( imageFloat, temp, width, height, width, cl, ch, coeffsNum );
        QuantizationThreshold( imageFloat, imageInt, length, threshold );
        compress( ( Bytef* )compressed, &l_compressedLength, ( const Bytef* )imageInt, length * sizeof( quant_t ) );

        delete[] imageFloat;
        delete[] temp;
        delete[] imageInt;

        compressedLength = l_compressedLength;
        return compressed;
    }


    //
    void DWT2Decompress( uint8_t* compressed, uint32_t compressedLength, uint32_t width, uint32_t height, WAVELET wavelet, uint8_t** outImage )
    {
        int32_t coeffsNum = g_waveletCoeffsNum[ wavelet ];
        const float* cl;
        float ch[ 8 ], icl[ 8 ], ich[ 8 ];
        switch( wavelet )
        {
            case( WAVELET_D2 ):
                cl = g_d2;
                break;
            case( WAVELET_D4 ):
                cl = g_d4;
                break;
            case( WAVELET_D6 ):
                cl = g_d6;
                break;
            case( WAVELET_D8 ):
                cl = g_d8;
                break;
            default:
                return;
        }
        GetHpfCoeffs( cl, coeffsNum, ch );
        GetICoeffs( cl, ch, coeffsNum, icl, ich );

        uint32_t length = width * height;
        float* imageFloat = new float[ length ];
        float* temp = new float[ length ];
        quant_t* imageInt = new quant_t[ length ];
        uLongf decompLength = length * sizeof( quant_t );

        // decompress
        uncompress( ( Bytef* )imageInt, &decompLength, ( const Bytef* )compressed, compressedLength );
        DequantizationThreshold( imageInt, imageFloat, length );
        IDWT2_recursive( imageFloat, temp, MIN_WIDTH_HEIGHT, MIN_WIDTH_HEIGHT, width, icl, ich, coeffsNum );

        for( uint32_t i = 0; i < height; i++ )
        {
            for( uint32_t j = 0; j < width; j++ )
                outImage[ j ][ i ] = clamp( imageFloat[ i * width + j ], 0.0f, 255.0f );
        }

        delete[] imageFloat;
        delete[] temp;
        delete[] imageInt;
    }


    //
    uint8_t* Compress( YCbCr_ubyte& input, WAVELET wavelet, uint8_t threshold, uint32_t& compressedLength )
    {
        if( input.Ywidth != input.Yheight )
        {
            // only square images
            return nullptr;
        }
        uint32_t yCompLength = 0;
        uint32_t cbCompLength = 0;
        uint32_t crCompLength = 0;
        uint8_t* yComp  = DWT2Compress( input.Y,  input.Ywidth,     input.Yheight,      threshold, wavelet, yCompLength );
        uint8_t* cbComp = DWT2Compress( input.Cb, input.CbCrwidth,  input.CbCrheight,   threshold, wavelet, cbCompLength );
        uint8_t* crComp = DWT2Compress( input.Cr, input.CbCrwidth,  input.CbCrheight,   threshold, wavelet, crCompLength );
        compressedLength = yCompLength + cbCompLength + crCompLength + sizeof( CompressedHeader );
        uint8_t* ret = new uint8_t[ compressedLength ];
        CompressedHeader* header = ( CompressedHeader* )ret;
        header->yCompLength = yCompLength;
        header->cbCompLength = cbCompLength;
        header->crCompLength = crCompLength;
        header->wavelet = wavelet;
        header->Ywidth = input.Ywidth;
        header->Yheight = input.Yheight;
        header->CbCrwidth = input.CbCrwidth;
        header->CbCrheight = input.CbCrheight;
        memcpy( ret + sizeof( CompressedHeader ), yComp, yCompLength );
        memcpy( ret + sizeof( CompressedHeader ) + yCompLength, cbComp, cbCompLength );
        memcpy( ret + sizeof( CompressedHeader ) + yCompLength + cbCompLength, crComp, crCompLength );

        delete[] yComp;
        delete[] cbComp;
        delete[] crComp;


        return ret;
    }


    //
    void Decompress( uint8_t* compressed, YCbCr_ubyte& output )
    {
        CompressedHeader* header = ( CompressedHeader* )compressed;
        uint32_t yCompLength  = header->yCompLength;
        uint32_t cbCompLength = header->cbCompLength;
        uint32_t crCompLength = header->crCompLength;
        WAVELET wavelet   = header->wavelet;
        output.Ywidth     = header->Ywidth;
        output.Yheight    = header->Yheight;
        output.CbCrwidth  = header->CbCrwidth;
        output.CbCrheight = header->CbCrheight;

        DWT2Decompress( compressed + sizeof( CompressedHeader ),                               yCompLength,    output.Ywidth,    output.Yheight,        wavelet, output.Y );
        DWT2Decompress( compressed + sizeof( CompressedHeader ) + yCompLength,                 cbCompLength,   output.CbCrwidth, output.CbCrheight,    wavelet, output.Cb );
        DWT2Decompress( compressed + sizeof( CompressedHeader ) + yCompLength + cbCompLength,  crCompLength,   output.CbCrwidth, output.CbCrheight,    wavelet, output.Cr );
    }

} // wavelet
