#pragma once
#include "ycbcr.h"

namespace jpeg
{

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
        QUANTIZATION_STD_MATRIX,
        QUANTIZATION_STD_MATRIX_HALF
    };


    //
    // compress input image
    // !!!! Output is not in jpeg file format !!!
    // for quantization by maximum:
    //  qParam1 - number of biggest DCT coeffs to get for Y component
    //  qParam2 - number of biggest DCT coeffs to get for Cb and Cr components
    // for quantization by matrix built with parameters alfa and gamma( QUANTIZATION_ALFA_GAMMMA )
    //  qParam1 - alfa parameter for Y component
    //  qParam2 - gamma parameter for Y component
    //  qParam3 - alfa parameter for Cb and Cr components
    //  qParam4 - alfa parameter for Cb and Cr components
    // for quantization with std matrix there is not params
    // compressedLength length of compressed data
    uint8_t* Compress( YCbCr_ubyte& input, DOWNSAMPLING downsampling, QUANTIZATION quantization, uint32_t qParam1, uint32_t qParam2, uint32_t qParam3, uint32_t qParam4, uint32_t& compressedLength );
    // decompress
    void Decompress( uint8_t* compressed, uint32_t compressedLength, YCbCr_ubyte& output );

}
