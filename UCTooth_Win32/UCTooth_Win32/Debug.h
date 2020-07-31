#ifndef __DEBUG_H__
/**
 * $File: Debug.h $
 * $Date: 2020-08-01 01:20:33 $
 * $Revision: $
 * $Creator: Jen-Chieh Shen $
 * $Notice: See LICENSE.txt for modification and distribution information
 *                   Copyright © 2020 by Shen, Jen-Chieh $
 */
#define __DEBUG_H__

// SOURCE: https://stackoverflow.com/questions/43732825/use-debug-log-from-c

#include<stdio.h>
#include <string>
#include <stdio.h>
#include <sstream>

#define DLLExport __declspec(dllexport)

extern "C"
{
    //Create a callback delegate
    typedef void(*FuncCallBack)(const char* message, int color, int size);
    static FuncCallBack callbackInstance = nullptr;
    DLLExport void RegisterDebugCallback(FuncCallBack cb);
}

enum class Color { Red, Green, Blue, Black, White, Yellow, Orange };

class  Debug
{
public:
    static void Log(const char* message, Color color = Color::Black);
    static void Log(const std::string message, Color color = Color::Black);
    static void Log(const int message, Color color = Color::Black);
    static void Log(const char message, Color color = Color::Black);
    static void Log(const float message, Color color = Color::Black);
    static void Log(const double message, Color color = Color::Black);
    static void Log(const bool message, Color color = Color::Black);

private:
    static void send_log(const std::stringstream &ss, const Color &color);
};

#endif /* __DEBUG_H__ */
