#include "./utils/utils.h"

int main() {

  progress_bar loading;
  loading.initiate(10);

  for (size_t i = 0; i < loading.outOf; i++) {
    loading.itterate();
    Sleep(200);
  }

  return 0;

}
