/**
 * $File: Main.cpp $
 * $Date: 2020-07-30 22:48:57 $
 * $Revision: $
 * $Creator: Jen-Chieh Sehn $
 * $Notice: See LICENSE.txt for modification and distribution information
 *                   Copyright © 2020 by Shen, Jen-Chieh $
 */
#include "./BtBridge.h"

/**
 * @func main
 * @brief Program entry point.
 */
void main()
{
    long btAddr = 0xB827EB651B47;
    UCTooth::Connect(btAddr);

    char msg[] = "Hello World";
    UCTooth::Send(msg);

    UCTooth::Recv(msg);

    printf("Data is: %s\n", msg);
}
