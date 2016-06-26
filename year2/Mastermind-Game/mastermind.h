#ifndef _MASTERMIND_H_
#define _MASTERMIND_H_

struct Mastermind {
public:  
  int seed;
  int codeLength;
  int guessLimit;
  char* code; // Pointer to passcode
  char* guess; // Pointer to code guessed by user
  bool* codeSequence; // Pointer to an bool array; used for computing black/white pegs
  bool* guessSequence; // Pointer to an bool array; used for computing black/white pegs

  Mastermind(int seed = 42, int codeLength = 4, int guessCount = 12);
  ~Mastermind();
  void playGame();

// Below are all helper functions
private:
  void setCode();
  void readGuess();
  void printCode();
  bool playAgain();
  void resetSequence();
  int blackPeg();
  int whitePeg();
};

#endif
