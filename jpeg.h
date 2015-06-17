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
    void Compress( YCbCr_ubyte& input, YCbCr_ubyte& output, DOWNSAMPLING downsampling, QUANTIZATION quantization, uint32_t qParam1, uint32_t qParam2, uint32_t qParam3, uint32_t qParam4, uint32_t& uncompressed, uint32_t& compressed);

}
