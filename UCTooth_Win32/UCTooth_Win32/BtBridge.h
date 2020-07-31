#ifndef __BTBRIDGE_H__
/**
 * $File: BtBridge.h $
 * $Date: 2020-07-30 22:49:52 $
 * $Revision: $
 * $Creator: Jen-Chieh Shen $
 * $Notice: See LICENSE.txt for modification and distribution information
 *                   Copyright © 2020 by Shen, Jen-Chieh $
 */
#define __BTBRIDGE_H__

#include "./Util.h"

UCTOOTH_C_BEG
UCTOOTH_NS_BEG

UCTOOTH_API void Test();

UCTOOTH_API int Connect(BTH_ADDR btAddr);
UCTOOTH_API void Close();

UCTOOTH_API int Send(char msg[]);
UCTOOTH_API char* Recv();

UCTOOTH_API void Cleanup();

UCTOOTH_API int RecvLen();

UCTOOTH_NS_END
UCTOOTH_C_END

#endif /* __BTBRIDGE_H__ */
