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

        /* Send */
        {
            string author = "Mahesh Chand";
            byte[] sendData = Encoding.ASCII.GetBytes(author);
            int bytesSend = BtBridge.Send(sendData);
        }

        /* Receive */
        {
            IntPtr data = BtBridge.Recv();

            int bytesRead = BtBridge.RecvLen();
            byte[] trueData = new byte[bytesRead];
            Marshal.Copy(data, trueData, 0, bytesRead);

            string hex = BitConverter.ToString(trueData);

            print("bytesRead: " + bytesRead);
            print("Data: " + hex);
        }

        BtBridge.Close();
    }
}
