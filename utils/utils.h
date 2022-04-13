#ifndef ADD_H
#define ADD_H

#include <iostream>
#include <time.h>
#include <math.h>
#include "utils.h"

#ifdef _WIN32
#include <windows.h>
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#define DISABLE_NEWLINE_AUTO_RETURN  0x0008
#endif

std::string operator*(std::string const &s, size_t n)
{
  std::string r;
  r.reserve(n * s.size());
  for (size_t i=0; i<n; i++)
  r += s;
  return r;
}

class progress_bar {
  public:

  int outOf;
  int current = 0;
  double start;

  void initiate(int setOutOf){
    outOf = setOutOf;
    #ifdef _WIN32
    #include <windows.h>
    HANDLE handleOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD consoleMode;
    GetConsoleMode( handleOut , &consoleMode);
    consoleMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    consoleMode |= DISABLE_NEWLINE_AUTO_RETURN;
    SetConsoleMode( handleOut , consoleMode );
    #endif
  }

  void print(){
    if (current == 0) {
      start = clock();
    }

    if (current <= outOf) {

      int percentage = (current*100) / outOf;
      int colour =  2.55*percentage;
      double eta = float(int(((float(clock()-start)/percentage)*(100-percentage))/10))/100;

      int r =  500 - (1.5 * colour) <= 255 ? 500 - (1.5 * colour):255;
      int g = 1 * colour <= 255 ? 1 * colour:255;

      std::cout <<  std::string((outOf > 0 ? (int) log10 ((double) outOf) + 1 : 1) - (current > 0 ? (int) log10 ((double) current) + 1 : 1), ' ') << current << '/' << outOf;
      std::cout << " \e[48;2;" << r << ";" << g <<";0m" << std::string(percentage/4, ' ') << "\033[0m\e[48;2;50;50;50m" << std::string(25 - percentage/4, ' ') << "\033[0m " << percentage << "% || ";

      if (percentage == 100)
        std::cout <<"time: " << float(int((clock()-start)/10))/100 <<  "s\t\r" << std::flush << "\n";
      else
        std::cout << "eta: " << eta <<  "s\t\r" << std::flush;
    }
  }

  void itterate(){
    current++;
    print();
  }
};


#endif
