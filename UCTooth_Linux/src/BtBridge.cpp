/**
 * $File: BtBridge.cpp $
 * $Date: 2020-07-30 22:52:32 $
 * $Revision: $
 * $Creator: Jen-Chieh Shen $
 * $Notice: See LICENSE.txt for modification and distribution information
 *                   Copyright © 2020 by Shen, Jen-Chieh $
 */
#include "./BtBridge.h"

UCTOOTH_C_BEG
UCTOOTH_NS_BEG

int Connect(long btAddr)
{
    return 0;
}

void Close()
{
    // empty..
}

int Send(char msg[])
{
    return 0;
}

void Recv(char msg[])
{
    // empty..
}

UCTOOTH_NS_END
UCTOOTH_C_END
