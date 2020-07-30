/**
 * $File: Test_General.cs $
 * $Date: 2020-07-26 15:04:28 $
 * $Revision: $
 * $Creator: Jen-Chieh Shen $
 * $Notice: See LICENSE.txt for modification and distribution information 
 *	                 Copyright © 2020 by Shen, Jen-Chieh $
 */
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UCTooth;
using System.Text;

/// <summary>
/// 
/// </summary>
public class Test_General 
    : MonoBehaviour 
{
    /* Variables */

    /* Setter & Getter */

    /* Functions */

    private void Start()
    {
        BtBridge.Connect(0xB827EB651B47);

        string author = "Mahesh Chand";
        byte[] sendData = Encoding.ASCII.GetBytes(author);

        BtBridge.Send(sendData);

        byte[] recvData = new byte[512];
        BtBridge.Recv(recvData);

        string result = System.Text.Encoding.UTF8.GetString(recvData);
        Debug.Log(result);
    }

}
