#pragma once

template< class T >
T clamp( T a, T s, T e )
{
    if( a < s )
        return s;
    if( a > e )
        return e;
    return a;
}


