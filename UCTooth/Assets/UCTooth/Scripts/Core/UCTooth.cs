/**
 * $File: UCTooth.cs $
 * $Date: 2020-08-01 01:23:18 $
 * $Revision: $
 * $Creator: Jen-Chieh Shen $
 * $Notice: See LICENSE.txt for modification and distribution information 
 *	                 Copyright © 2020 by Shen, Jen-Chieh $
 */
using AOT;
using System;
using System.Runtime.InteropServices;
using UnityEngine;

namespace UCTooth
{
    /// <summary>
    /// UCTooth game object, that will activate for plugin usage.
    /// </summary>
    public class UCTooth : MonoBehaviour
    {
        /* Variables */
#if UNITY_EDITOR_WIN || UNITY_STANDALONE_WIN
        private const string PLUGIN_NAME = "UCTooth_Win32";
#elif UNITY_EDITOR_OSX || UNITY_STANDALONE_OSX
        private const string PLUGIN_NAME = "__Internal";
#elif UNITY_EDITOR_LINUX || UNITY_STANDALONE_LINUX
        private const string PLUGIN_NAME = "UCTooth_Linux";
#elif UNITY_ANDROID
        private const string PLUGIN_NAME = "UCTooth_Android";
#elif UNITY_IOS
        private const string PLUGIN_NAME = "__Internal";
#endif

        enum Color { red, green, blue, black, white, yellow, orange, };

        /* Setter & Getter */

        /* Functions */

        // Use this for initialization
        private void OnEnable()
        {
            RegisterDebugCallback(OnDebugCallback);
        }

        [DllImport(PLUGIN_NAME, CallingConvention = CallingConvention.Cdecl)]
        private static extern void RegisterDebugCallback(debugCallback cb);

        // Create string param callback delegate
        private delegate void debugCallback(IntPtr request, int color, int size);

        [MonoPInvokeCallback(typeof(debugCallback))]
        private static void OnDebugCallback(IntPtr request, int color, int size)
        {
            //Ptr to string
            string debug_string = Marshal.PtrToStringAnsi(request, size);

            //Add Specified Color
            debug_string =
                String.Format("{0}{1}{2}{3}{4}",
                "<color=",
                ((Color)color).ToString(),
                ">",
                debug_string,
                "</color>");

            Debug.Log(debug_string);
        }
    }
}
