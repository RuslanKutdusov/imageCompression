#pragma once
#include <stdint.h>

//
template< class T >
struct YCbCr
{
    T** Y   = nullptr;
    T** Cb  = nullptr;
    T** Cr  = nullptr;
    uint32_t    Ywidth   = 0;
    uint32_t    Yheight  = 0;
    uint32_t    CbCrwidth   = 0;
    uint32_t    CbCrheight  = 0;

    YCbCr()
    {

    }

    YCbCr( T** Y, T** Cb, T** Cr, uint32_t width, uint32_t height )
    {
        this->Y = Y;
        this->Cb = Cb;
        this->Cr = Cr;
        this->Ywidth = width;
        this->Yheight = height;
        this->CbCrwidth = width;
        this->CbCrheight = height;

        doDelete = false;
    }

    YCbCr( uint32_t width, uint32_t height )
    {
        Init( width, height );
    }

    void Init( uint32_t width, uint32_t height )
    {
        Delete();

        Y  = new T*[ width ];
        Cb = new T*[ width ];
        Cr = new T*[ width ];
        for( uint32_t x = 0; x < width; x++ )
        {
            Y[ x ]  = new T[ height ];
            Cb[ x ] = new T[ height ];
            Cr[ x ] = new T[ height ];
        }

        this->Ywidth = width;
        this->Yheight = height;
        this->CbCrwidth = width;
        this->CbCrheight = height;

        Zero();

        doDelete = true;
    }

    void Init( uint32_t Ywidth, uint32_t Yheight, uint32_t CbCrwidth, uint32_t CbCrheight )
    {
        Delete();

        Y  = new T*[ Ywidth ];
        Cb = new T*[ CbCrwidth ];
        Cr = new T*[ CbCrwidth ];
        for( uint32_t x = 0; x < Ywidth; x++ )
            Y[ x ]  = new T[ Yheight ];

        for( uint32_t x = 0; x < CbCrwidth; x++ )
        {
            Cb[ x ] = new T[ CbCrheight ];
            Cr[ x ] = new T[ CbCrheight ];
        }

        this->Ywidth = Ywidth;
        this->Yheight = Yheight;
        this->CbCrwidth =  CbCrwidth;
        this->CbCrheight = CbCrheight;

        Zero();

        doDelete = true;
    }

    ~YCbCr()
    {
        if( !doDelete )
            return;

        for( uint32_t x = 0; x < Ywidth; x++ )
            delete[] Y[ x ];

        for( uint32_t x = 0; x < CbCrwidth; x++ )
        {
            delete[] Cb[ x ];
            delete[] Cr[ x ];
        }

        delete[] Y;
        delete[] Cb;
        delete[] Cr;
    }

    const YCbCr< T >& operator=( const YCbCr< T >& ) = delete;

private:
    //
    bool    doDelete    = true;

    //
    void Delete()
    {
        if( !doDelete )
        {
            doDelete = false;
        }
        else
        {
            for( uint32_t x = 0; x < Ywidth; x++ )
                delete[] Y[ x ];

            for( uint32_t x = 0; x < CbCrwidth; x++ )
            {
                delete[] Cb[ x ];
                delete[] Cr[ x ];
            }

            delete[] Y;
            delete[] Cb;
            delete[] Cr;
        }

        Y = nullptr;
        Cb = nullptr;
        Cr = nullptr;
    }

    void Zero()
    {
        if( !Y || !Cb || !Cr )
            return;

        for( uint32_t x = 0; x < Ywidth; x++ )
            for( uint32_t y = 0; y < Yheight; y++ )
                Y[ x ][ y ] = 0;

        for( uint32_t x = 0; x < CbCrwidth; x++ )
            for( uint32_t y = 0; y < CbCrheight; y++ )
            {
                Cb[ x ][ y ] = 0;
                Cr[ x ][ y ] = 0;
            }
    }
};

typedef YCbCr< uint8_t > YCbCr_ubyte;
typedef YCbCr< int32_t > YCbCr_int;
typedef YCbCr< float > YCbCr_float;
