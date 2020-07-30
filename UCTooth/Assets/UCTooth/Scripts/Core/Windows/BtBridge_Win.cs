#if UNITY_EDITOR_WIN || UNITY_STANDALONE_WIN
/**
 * $File: BtBridge_Win.cs $
 * $Date: 2020-07-30 21:44:47 $
 * $Revision: $
 * $Creator: Jen-Chieh Shen $
 * $Notice: See LICENSE.txt for modification and distribution information 
 *	                 Copyright © 2020 by Shen, Jen-Chieh $
 */
using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using UnityEngine;

namespace UCTooth
{
    /// <summary>
    /// Bluetooth bridge to Windows.
    /// </summary>
    public static class BtBridge_Win
    {
        /* Variables */

        /* Setter & Getter */

        /* Functions */

        [DllImport("UCTooth_Win32")]
        public static extern int Connect(long btAddr);

        [DllImport("UCTooth_Win32")]
        public static extern void Close();

        [DllImport("UCTooth_Win32")]
        public static extern int Send(byte[] msg);

        [DllImport("UCTooth_Win32")]
        public static extern void Recv(byte[] msg);
    }
}
#endif
