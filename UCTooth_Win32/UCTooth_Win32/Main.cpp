/**
 * $File: Main.cpp $
 * $Date: 2020-07-30 22:48:57 $
 * $Revision: $
 * $Creator: Jen-Chieh Sehn $
 * $Notice: See LICENSE.txt for modification and distribution information
 *                   Copyright © 2020 by Shen, Jen-Chieh $
 */
#include "./BtBridge.h"

static void Test_Connect()
{
	unsigned __int64 btAddr = 0xB827EB651B47;

	char sendData[] = "Hello World Hello World Hello World";

	if (UCTooth::Connect(btAddr) == 0)
	{
		int bytesSent = UCTooth::Send(sendData);

		printf("bytesSent: %d\n", bytesSent);

		/*char* data = UCTooth::Recv();

		for (int index = 0; index < 10; ++index)
		{
			printf("data: %04x\n", *(data + index));
		}

		free(data);*/
	}
}

static void Test_SDP()
{
	UCTooth::Test();
	UCTooth::Close();
}

 /**
  * @func main
  * @brief Program entry point.
  */
int main()
{
	//Test_Connect();
	Test_SDP();

	return 0;
}
