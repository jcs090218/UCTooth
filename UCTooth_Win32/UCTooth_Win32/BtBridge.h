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

#include <winsock2.h>
#include <ws2bth.h>

#include <stdio.h>

#pragma comment(lib, "WS2_32.lib")

#define UCTOOTH_EXPORT  // Exporting.

#define UCTOOTH_NS_BEG namespace UCTooth {
#define UCTOOTH_NS_END }

#define UCTOOTH_C_BEG extern "C" {
#define UCTOOTH_C_END }

#ifdef UCTOOTH_EXPORT
#define UCTOOTH_API __declspec(dllexport)
#else
#define UCTOOTH_API __declspec(dllimport)
#endif

UCTOOTH_C_BEG
UCTOOTH_NS_BEG

UCTOOTH_API int Connect(BTH_ADDR btAddr);
UCTOOTH_API void Close();

UCTOOTH_API int Send(char msg[]);
UCTOOTH_API void Recv(char msg[]);

UCTOOTH_NS_END
UCTOOTH_C_END

#endif /* __BTBRIDGE_H__ */
