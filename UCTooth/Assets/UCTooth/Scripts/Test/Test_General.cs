/**
 * $File: Test_General.cs $
 * $Date: 2020-07-26 15:04:28 $
 * $Revision: $
 * $Creator: Jen-Chieh Shen $
 * $Notice: See LICENSE.txt for modification and distribution information 
 *	                 Copyright © 2020 by Shen, Jen-Chieh $
 */
using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UCTooth;
using System.Text;
using System.Runtime.InteropServices;

/// <summary>
/// Any test can be placed here.
/// </summary>
public class Test_General 
    : MonoBehaviour 
{
    /* Variables */

    /* Setter & Getter */

    /* Functions */

    private void Update()
    {
        if (Input.GetKeyDown(KeyCode.A))
            TryConnect();
    }

    private void TryConnect()
    {
        BtBridge.Connect(0xB827EB651B47);

        string author = "Mahesh Chand";
        byte[] sendData = Encoding.ASCII.GetBytes(author);

        int bytesSend = BtBridge.Send(sendData);

        IntPtr data = BtBridge.Recv();

        byte[] trueData = new byte[8];
        Marshal.Copy(data, trueData, 0, 8);

        string hex = BitConverter.ToString(trueData);

        //print(bytesRead);
        print(hex);

        BtBridge.Cleanup();

        //string result = System.Text.Encoding.UTF8.GetString(recvData);
        //Debug.Log(result);
    }
}
