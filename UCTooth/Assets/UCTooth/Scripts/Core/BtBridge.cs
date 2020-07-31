/**
 * $File: BtBridge.cs $
 * $Date: 2020-07-30 21:37:47 $
 * $Revision: $
 * $Creator: Jen-Chieh Shen $
 * $Notice: See LICENSE.txt for modification and distribution information 
 *	                 Copyright © 2020 by Shen, Jen-Chieh $
 */
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace UCTooth
{
    /// <summary>
    /// Bluetooth bridge adapter interface.
    /// </summary>
    public static class BtBridge
    {
        /* Variables */

        /* Setter & Getter */

        /* Functions */

        public static int Connect(long btAddr)
        {
#if UNITY_EDITOR_WIN || UNITY_STANDALONE_WIN
            return BtBridge_Win.Connect(btAddr);
#elif UNITY_EDITOR_OSX || UNITY_STANDALONE_OSX

#elif UNITY_EDITOR_LINUX || UNITY_STANDALONE_LINUX

#elif UNITY_ANDROID

#elif UNITY_IOS

#endif
        }

        public static void Close()
        {
#if UNITY_EDITOR_WIN || UNITY_STANDALONE_WIN
            BtBridge_Win.Close();
#elif UNITY_EDITOR_OSX || UNITY_STANDALONE_OSX

#elif UNITY_EDITOR_LINUX || UNITY_STANDALONE_LINUX

#elif UNITY_ANDROID

#elif UNITY_IOS

#endif
        }

        public static int Send(byte[] msg)
        {
#if UNITY_EDITOR_WIN || UNITY_STANDALONE_WIN
            return BtBridge_Win.Send(msg);
#elif UNITY_EDITOR_OSX || UNITY_STANDALONE_OSX

#elif UNITY_EDITOR_LINUX || UNITY_STANDALONE_LINUX

#elif UNITY_ANDROID

#elif UNITY_IOS

#endif
        }

        public static System.IntPtr Recv()
        {
#if UNITY_EDITOR_WIN || UNITY_STANDALONE_WIN
            return BtBridge_Win.Recv();
#elif UNITY_EDITOR_OSX || UNITY_STANDALONE_OSX

#elif UNITY_EDITOR_LINUX || UNITY_STANDALONE_LINUX

#elif UNITY_ANDROID

#elif UNITY_IOS

#endif
        }

        public static void Cleanup()
        {
#if UNITY_EDITOR_WIN || UNITY_STANDALONE_WIN
            BtBridge_Win.Cleanup();
#elif UNITY_EDITOR_OSX || UNITY_STANDALONE_OSX

#elif UNITY_EDITOR_LINUX || UNITY_STANDALONE_LINUX

#elif UNITY_ANDROID

#elif UNITY_IOS

#endif
        }

        public static int RecvLen()
        {
#if UNITY_EDITOR_WIN || UNITY_STANDALONE_WIN
            return BtBridge_Win.RecvLen();
#elif UNITY_EDITOR_OSX || UNITY_STANDALONE_OSX

#elif UNITY_EDITOR_LINUX || UNITY_STANDALONE_LINUX

#elif UNITY_ANDROID

#elif UNITY_IOS

#endif
        }
    }
}
