#pragma once
#include "ycbcr.h"

namespace wavelet
{

    enum WAVELET
    {
        WAVELET_D2 = 0,
        WAVELET_D4,
        WAVELET_D6,
        WAVELET_D8,

        WAVELET_COUNT
    };

    uint8_t* Compress( YCbCr_ubyte& input, WAVELET wavelet, uint8_t threshold, uint32_t& compressedLength );
    void Decompress( uint8_t* compressed, YCbCr_ubyte& output );

}
