#ifndef __BTBRIDGE_H__
/**
 * $File: BtBridge.h $
 * $Date: 2020-07-30 22:52:40 $
 * $Revision: $
 * $Creator: Jen-Chieh Shen $
 * $Notice: See LICENSE.txt for modification and distribution information
 *                   Copyright © 2020 by Shen, Jen-Chieh $
 */
#define __BTBRIDGE_H__

#define UCTOOTH_EXPORT  // Exporting.

#define UCTOOTH_NS_BEG namespace UCTooth {
#define UCTOOTH_NS_END }

#define UCTOOTH_C_BEG extern "C" {
#define UCTOOTH_C_END }

#ifdef UCTOOTH_EXPORT
#define UCTOOTH_API __attribute__((visibility("default")))
#else
#define UCTOOTH_API
#endif

UCTOOTH_C_BEG
UCTOOTH_NS_BEG

UCTOOTH_API int Connect(long btAddr);
UCTOOTH_API void Close();

UCTOOTH_API int Send(char msg[]);
UCTOOTH_API void Recv(char msg[]);

UCTOOTH_NS_END
UCTOOTH_C_END

#endif /* __BTBRIDGE_H__ */
