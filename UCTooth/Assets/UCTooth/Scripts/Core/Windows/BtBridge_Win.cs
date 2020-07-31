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

        private const string PLUGIN_NAME = "UCTooth_Win32";

        /* Setter & Getter */

        /* Functions */

        [DllImport(PLUGIN_NAME, EntryPoint = "Connect")]
        public static extern int Connect(long btAddr);

        [DllImport(PLUGIN_NAME, EntryPoint = "Close")]
        public static extern void Close();

        [DllImport(PLUGIN_NAME, EntryPoint = "Send")]
        public static extern int Send(byte[] msg);

        [DllImport(PLUGIN_NAME, EntryPoint = "Recv")]
        public static extern System.IntPtr Recv();

        [DllImport(PLUGIN_NAME, EntryPoint = "Cleanup")]
        public static extern void Cleanup();

        [DllImport(PLUGIN_NAME, EntryPoint = "RecvLen")]
        public static extern int RecvLen();
    }
}
#endif
