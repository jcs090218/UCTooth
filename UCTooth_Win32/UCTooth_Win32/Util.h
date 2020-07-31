#ifndef __UTIL_H__
/**
 * $File: Util.h $
 * $Date: 2020-08-01 03:02:56 $
 * $Revision: $
 * $Creator: Jen-Chieh Shen $
 * $Notice: See LICENSE.txt for modification and distribution information
 *                   Copyright © 2020 by Shen, Jen-Chieh $
 */
#define __UTIL_H__

#include <winsock2.h>
#include <Ws2bth.h>
#include <bthdef.h>
#include <BluetoothAPIs.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <conio.h>
#include <fcntl.h>

#pragma comment(lib, "WS2_32.lib")
#pragma comment(lib, "irprops.lib")

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

UCTOOTH_NS_BEG

template<typename T> void SafeFree(T*& ptr)
{
    if (ptr)
    {
        free(ptr);
        ptr = nullptr;
    }
}

UCTOOTH_NS_END

#endif /* __UTIL_H__ */
