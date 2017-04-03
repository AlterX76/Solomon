
#ifndef TYPES_H
#define TYPES_H

#include "IBaseType.h"


namespace Solomon {

    namespace Types {
        //
        // declarations for primitive types:
        typedef IBaseType<byte>                 Byte;
        typedef IBaseType<geo>                  GeoCoordinate;
        typedef IBaseType<integer>              Integer;
        typedef IBaseType<sock>                 SocketHandle;
        typedef IBaseType<u_integer>            UInteger;
        typedef IBaseType<u_longer>             ULong;
        typedef IBaseType<shorter>              Short;
        typedef IBaseType<u_short>              UShort;
        typedef IBaseType<SolomSmallString *>   SmallString;
        typedef IBaseType<SolomLargeString *>   LargeString;
        typedef IBaseType<SolomDateTime *>      DateTime;
    }
}

#endif // TYPES_H
