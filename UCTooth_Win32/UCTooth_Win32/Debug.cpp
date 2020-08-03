/**
 * $File: Debug.cpp $
 * $Date: 2020-08-01 01:20:40 $
 * $Revision: $
 * $Creator: Jen-Chieh Shen $
 * $Notice: See LICENSE.txt for modification and distribution information
 *                   Copyright © 2020 by Shen, Jen-Chieh $
 */

#include "./Debug.h"

#include <stdio.h>
#include <string>
#include <stdio.h>
#include <sstream>

void Debug::Log(const char* message, Color color)
{
#ifdef _WINDLL
	if (callbackInstance != nullptr)
		callbackInstance(message, (int)color, (int)strlen(message));
#else
	std::string msg(message);
	msg.append("\n");
	printf(msg.c_str());
#endif
}

void Debug::Log(const std::string message, Color color)
{
	const char* tmsg = message.c_str();
#ifdef _WINDLL
	if (callbackInstance != nullptr)
		callbackInstance(tmsg, (int)color, (int)strlen(tmsg));
#else
	std::string msg(message);
	msg.append("\n");
	printf(msg.c_str());
#endif
}

void Debug::Log(const int message, Color color)
{
#ifdef _WINDLL
	std::stringstream ss;
	ss << message;
	send_log(ss, color);
#else
	printf("%d\n", message);
#endif
}

void Debug::Log(const char message, Color color)
{
#ifdef _WINDLL
	std::stringstream ss;
	ss << message;
	send_log(ss, color);
#else
	printf("%c\n", message);
#endif
}

void Debug::Log(const float message, Color color)
{
#ifdef _WINDLL
	std::stringstream ss;
	ss << message;
	send_log(ss, color);
#else
	printf("%f\n", message);
#endif
}

void Debug::Log(const double message, Color color)
{
#ifdef _WINDLL
	std::stringstream ss;
	ss << message;
	send_log(ss, color);
#else
	printf("%f\n", message);
#endif
}

void Debug::Log(const bool message, Color color)
{
#ifdef _WINDLL
	std::stringstream ss;
	if (message)
		ss << "true";
	else
		ss << "false";
	send_log(ss, color);
#else
	printf("%s\n", message ? "true" : "false");
#endif
}

void Debug::send_log(const std::stringstream& ss, const Color& color)
{
	const std::string tmp = ss.str();
	const char* tmsg = tmp.c_str();
#ifdef _WINDLL
	if (callbackInstance != nullptr)
		callbackInstance(tmsg, (int)color, (int)strlen(tmsg));
#else
	std::string msg(tmsg);
	msg.append("\n");
	printf(msg.c_str());
#endif
}

// Create a callback delegate
void RegisterDebugCallback(FuncCallBack cb)
{
	callbackInstance = cb;
}
