/**
 * $File: BtBridge.cpp $
 * $Date: 2020-07-30 22:51:11 $
 * $Revision: $
 * $Creator: Jen-Chieh Shen $
 * $Notice: See LICENSE.txt for modification and distribution information
 *                   Copyright © 2020 by Shen, Jen-Chieh $
 */
#include "./BtBridge.h"
#include "./Debug.h"

UCTOOTH_C_BEG
UCTOOTH_NS_BEG

// TUTORIAL: https://www.winsocketdotnetworkprogramming.com/winsock2programming/winsock2advancedotherprotocol4p.html

SOCKET btSocket = -1;

#define BUF_LEN 512

char* g_pRetBuffer = nullptr;
int gRecvLen = 0;

/* if we fail, call ourself to find out why and return that error */
TCHAR* GetLastErrorMessage(DWORD last_error)
{
	static TCHAR errmsg[512];
	if (!FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, 0, last_error, 0, errmsg, 511, NULL))
		return (GetLastErrorMessage(GetLastError()));
	return errmsg;
}

int Connect(BTH_ADDR btAddr)
{
	int error = 0;

	WSADATA wsd;
	error = WSAStartup(MAKEWORD(2, 2), &wsd);
	if (error != 0)
	{
		Debug::Log("[ERROR] Unable to load Winsock", Color::Red);
		return error;
	}

	SOCKADDR_BTH sockAddr = { 0 };

	//u_long iMode = 1;  // 0 = blocking, 1 = non-blocking

	btSocket = socket(AF_BTH, SOCK_STREAM, BTHPROTO_RFCOMM);
	//ioctlsocket(btSocket, FIOASYNC, &iMode);
	memset(&sockAddr, 0, sizeof(sockAddr));
	sockAddr.addressFamily = AF_BTH;
	sockAddr.serviceClassId = RFCOMM_PROTOCOL_UUID;
	sockAddr.port = BT_PORT_ANY;
	sockAddr.btAddr = btAddr;

	error = connect(btSocket, (SOCKADDR*)&sockAddr, sizeof(sockAddr));
	if (error == SOCKET_ERROR)
	{
		Debug::Log("[ERROR] Network exception, when connect", Color::Red);
		return error;
	}

	return 0;
}

void Close()
{
	Cleanup();
	closesocket(btSocket);
	WSACleanup();
}

int Send(char msg[])
{
	int bytesSent = send(btSocket, msg, strlen(msg), 0);
	return bytesSent;
}

char* Recv()
{
	Cleanup();

	char buffer[BUF_LEN];
	gRecvLen = recv(btSocket, buffer, BUF_LEN, 0);

	g_pRetBuffer = (char*)malloc(gRecvLen * sizeof(char));
	memcpy(g_pRetBuffer, buffer, gRecvLen);
	return g_pRetBuffer;
}

int RecvLen()
{
	return (g_pRetBuffer) ? gRecvLen : 0;
}

void Cleanup()
{
	SafeFree(g_pRetBuffer);
	gRecvLen = 0;
}

BOOL __stdcall callback(ULONG uAttribId, LPBYTE pValueStream, ULONG cbStreamSize, LPVOID pvParam)
{
	SDP_ELEMENT_DATA element;
	if (ERROR_SUCCESS != BluetoothSdpGetElementData(pValueStream, cbStreamSize, &element))
		wprintf(L"%s\n", GetLastErrorMessage(GetLastError()));
	return true;
}

void Test()
{
	WSAPROTOCOL_INFO protocolInfo;
	int protocolInfoSize = sizeof(protocolInfo);

	if (0 != getsockopt(btSocket, SOL_SOCKET, SO_PROTOCOL_INFO, (char*)&protocolInfo, &protocolInfoSize))
	{
		Debug::Log("[ERROR] Can't get socket protocol information", Color::Red);
		return;
	}

	WSAQUERYSET querySet;
	memset(&querySet, 0, sizeof(querySet));
	querySet.dwSize = sizeof(querySet);
	querySet.dwNameSpace = NS_BTH;
	HANDLE hLookup;
	DWORD flags = LUP_RETURN_NAME | LUP_CONTAINERS | LUP_RETURN_ADDR | LUP_FLUSHCACHE | LUP_RETURN_TYPE | LUP_RETURN_BLOB | LUP_RES_SERVICE;

	int result = WSALookupServiceBegin(&querySet, flags, &hLookup);
	while (result == 0)
	{
		BYTE buffer[1000];
		DWORD bufferLength = sizeof(buffer);
		WSAQUERYSET* pResults = (WSAQUERYSET*)&buffer;
		result = WSALookupServiceNext(hLookup, flags, &bufferLength, pResults);

		if (result != 0)
		{
			wprintf(L"[WARNING] %d\n", bufferLength);
			continue;
		}

		wprintf(L"%s\n", pResults->lpszServiceInstanceName);
		CSADDR_INFO* pCSAddr = (CSADDR_INFO*)pResults->lpcsaBuffer;
		BTH_DEVICE_INFO* pDeviceInfo = (BTH_DEVICE_INFO*)pResults->lpBlob;
		WSAQUERYSET querySet2;
		memset(&querySet2, 0, sizeof(querySet2));
		querySet2.dwSize = sizeof(querySet2);
		GUID protocol = L2CAP_PROTOCOL_UUID;
		querySet2.lpServiceClassId = &protocol;

		querySet2.dwNameSpace = NS_BTH;
		LPWSTR addressAsString = { 0 };
		DWORD addressSize = sizeof(addressAsString);
		addressSize = sizeof(addressAsString);

		if (0 == WSAAddressToString(pCSAddr->LocalAddr.lpSockaddr, pCSAddr->LocalAddr.iSockaddrLength, &protocolInfo, addressAsString, &addressSize))
			wprintf(L"local address: %s\n", addressAsString);

		addressSize = sizeof(addressAsString);

		if (0 == WSAAddressToString(pCSAddr->RemoteAddr.lpSockaddr, pCSAddr->RemoteAddr.iSockaddrLength, &protocolInfo, addressAsString, &addressSize))
			wprintf(L"device address: %s\n", addressAsString);

		querySet2.lpszContext = addressAsString;
		HANDLE hLookup2;
		DWORD flags = LUP_FLUSHCACHE | LUP_RETURN_NAME | LUP_RETURN_TYPE | LUP_RETURN_ADDR | LUP_RETURN_BLOB | LUP_RETURN_COMMENT;
		int result = WSALookupServiceBegin(&querySet2, flags, &hLookup2);

		if (result != 0)
		{
			printf("[WARNING] ..\n");
			continue;
		}

		while (0 == result)
		{
			BYTE buffer[2000];
			DWORD bufferLength = sizeof(buffer);
			WSAQUERYSET* pResults = (WSAQUERYSET*)&buffer;
			result = WSALookupServiceNext(hLookup2, flags, &bufferLength, pResults);

			if (result != 0)
			{
				wprintf(L"[WARNING] %d\n", bufferLength);
				continue;
			}

			wprintf(L"%s\n", pResults->lpszServiceInstanceName);

			CSADDR_INFO* pCSAddr = (CSADDR_INFO*)pResults->lpcsaBuffer;
			addressSize = sizeof(addressAsString);

			if (0 == WSAAddressToString(pCSAddr->LocalAddr.lpSockaddr, pCSAddr->LocalAddr.iSockaddrLength, &protocolInfo, addressAsString, &addressSize))
				wprintf(L"local address: %s\n", addressAsString);

			addressSize = sizeof(addressAsString);
			if (0 == WSAAddressToString(pCSAddr->RemoteAddr.lpSockaddr, pCSAddr->RemoteAddr.iSockaddrLength, &protocolInfo, addressAsString, &addressSize))
				wprintf(L"device address: %s\n", addressAsString);

			if (pResults->lpBlob)
			{
				const BLOB* pBlob = (BLOB*)pResults->lpBlob;
				if (!BluetoothSdpEnumAttributes(pBlob->pBlobData, pBlob->cbSize, callback, 0))
				{
					wprintf(L"BluetoothSdpEnumAttributes - %s\n", GetLastErrorMessage(GetLastError()));
				}
			}
		}
	}


	HANDLE hRadio;
	BLUETOOTH_FIND_RADIO_PARAMS btfrp = { sizeof(btfrp) };
	HBLUETOOTH_RADIO_FIND hFind = BluetoothFindFirstRadio(&btfrp, &hRadio);
	if (NULL == hFind)
	{
		wprintf(L"Can't find \n");
		return;
	}

	printf("hFind\n");
	do
	{
		//
		//  TODO: Do something with the radio handle.
		//
		BLUETOOTH_RADIO_INFO radioInfo;
		radioInfo.dwSize = sizeof(radioInfo);
		if (ERROR_SUCCESS == BluetoothGetRadioInfo(hRadio, &radioInfo))
		{
			wprintf(L"Raido: %s\n", radioInfo.szName);
		}
		BLUETOOTH_DEVICE_INFO_STRUCT deviceInfo;
		deviceInfo.dwSize = sizeof(deviceInfo);
		BLUETOOTH_DEVICE_SEARCH_PARAMS deviceSearchParams;
		memset(&deviceSearchParams, 0, sizeof(deviceSearchParams));
		deviceSearchParams.dwSize = sizeof(deviceSearchParams);
		//deviceSearchParams.fReturnAuthenticated = true;
		deviceSearchParams.fReturnRemembered = true;
		//deviceSearchParams.fReturnUnknown = true;
		//deviceSearchParams.fReturnConnected = true;
		deviceSearchParams.hRadio = hRadio;
		HANDLE hDeviceFind = BluetoothFindFirstDevice(&deviceSearchParams, &deviceInfo);
		if (NULL != hDeviceFind)
		{
			do
			{
				wprintf(L"Device: %s\n", deviceInfo.szName);
				//BluetoothDisplayDeviceProperties(0, &deviceInfo);
			} while (BluetoothFindNextDevice(hDeviceFind, &deviceInfo));
			BluetoothFindDeviceClose(hDeviceFind);
		}

		if (BluetoothGetDeviceInfo(hRadio, &deviceInfo))
		{
			wprintf(L"+ Device: %s\n", deviceInfo.szName);
			// BluetoothUpdateDeviceRecord - change name
			// BluetoothRemoveDevice
		}
		GUID guidServices[10];
		DWORD numServices = sizeof(guidServices);
		DWORD result = BluetoothEnumerateInstalledServices(hRadio, &deviceInfo, &numServices, guidServices);
		CloseHandle(hRadio);
	} while (BluetoothFindNextRadio(hFind, &hRadio));
	BluetoothFindRadioClose(hFind);
}

UCTOOTH_NS_END
UCTOOTH_C_END
