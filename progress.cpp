#include <iostream>
#include <windows.h>
#include <time.h>



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

  int colours[6] = {64, 192, 96, 32, 160, 160};
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

  void print(){
    if (current == 0) {
      start = clock();
    }

    if (current <= outOf) {
      SetConsoleTextAttribute(hConsole, 15);

      int percentage = (current*100) / outOf;
      double eta = float(int(((float(clock()-start)/percentage)*(100-percentage))/10))/100;

      std : std::cout << current << '/' << outOf << " ";

      SetConsoleTextAttribute(hConsole, colours[int(percentage/20)]);
      std::cout << std::string(percentage/4, ' ');

      SetConsoleTextAttribute(hConsole, 15);
      std::cout << std::string(25 - percentage/4, ' ');


      SetConsoleTextAttribute(hConsole, 15);
      if (percentage == 100) {
        std::cout << " " << percentage << "% || time taken: " << float(int((clock()-start)/10))/100 <<  "s\t\r" << std::flush;
        std::cout << '\n';
      }
      else{
        std::cout << " " << percentage << "% || eta: " << eta <<  "s\t\r" << std::flush;

      }
    }
  }

  void itterate(){
    current++;
    print();
  }
};

int main() {
  std::cout << "\033[1;31mbold red text\033[0m\n";

  progress_bar loading;
  loading.outOf = 100;

  for (size_t i = 0; i < loading.outOf; i++) {
    loading.itterate();
    Sleep(200);
  }

  return 0;
}
