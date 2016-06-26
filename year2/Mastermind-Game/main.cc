#include "mastermind.h"
#include <iostream>
#include <cstdlib>
using namespace std;

int main(int argc, char** argv) {
  if (argc!=1 and argc!=4) {
    cout << "Incorrect usage, usage must be either of: " << endl;
    cout << "./main seed codeLength guessLimit" << endl;
    cout << "./main" << endl;
    return 1;
  }
  if (argc==4) {
    Mastermind mm {atoi(argv[1]),atoi(argv[2]),atoi(argv[3])};
    mm.playGame(); 
  } else {
    Mastermind mm;
    mm.playGame();
  }
  return 0;
}
