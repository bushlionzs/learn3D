#ifndef __NETLIBERROR_H__
#define __NETLIBERROR_H__

#include <stdint.h>
enum
{
    NetlibError_None = 0,
    NetlibError_ConnectionTimeout = -1,
    NetlibError_ConnectionError = -2,
    NetlibError_BindError = -3,
    NetlibError_ListenError = -4,
    NetlibError_SendError = -5,
    NetlibError_RecvError = -6,
    NetlibError_SocketInvalid = -7,
    NetlibError_BufferOver = -8,
    NetlibError_HandleError = -9,
    NetlibError_BufferError = -10,
    NetlibError_SocketError = -11,
    NetlibError_InvalidUrl = -12,
    NetlibError_SSL_Error = -13,
    NetlibError_Try_Later = -14,
    NetlibError_Dns_Error = -15,
    NetlibError_Dns_Timeout = -16,
    NetlibError_Dns_Id_Error = -17,
    NetlibError_Dns_Close    = -18,
    NetlibError_Redirect_Error = -19,
    NetlibError_302_Error = -20,
    NetlibError_Trans_Proto_Error = -21,
    NetlibError_OpenPipeError = -22,
    NetlibError_PipeSendError = -23,
    NetlibError_Timeout  = -24,
};

//io event error code.
#define  DY_NET_OK       0
#define  DY_NET_ERROR   -1
#define  DY_NET_AGAIN   -2
#define  DY_NET_INTR    -3

#endif //__NETLIBERROR_H__
