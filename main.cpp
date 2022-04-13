#ifndef WINDOWS // Windows performs #define WINDOWS
#include <windows.h>
#endif

#include <iostream>

#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#define DISABLE_NEWLINE_AUTO_RETURN  0x0008

int main()
{
  #ifndef WINDOWS
  HANDLE handleOut = GetStdHandle(STD_OUTPUT_HANDLE);
  DWORD consoleMode;
  GetConsoleMode( handleOut , &consoleMode);
  consoleMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
  consoleMode |= DISABLE_NEWLINE_AUTO_RETURN;
  SetConsoleMode( handleOut , consoleMode );
  #endif

   for (int i = 0; i < 10; ++i)
   {
      std::cout << "\x1b[38;2;" << 5 * i << ";" << 255 - 10 * i << ";220m"
             << "ANSI Escape Sequence " << i << std::endl;
   }
}
