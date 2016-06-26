#include "mastermind.h"
#include <cstdlib>
#include <iostream>
using namespace std;

// Constructor
Mastermind::Mastermind(int seed, int codeLength, int guessCount) :
	seed(seed), codeLength(codeLength), guessLimit(guessCount),
	code(new char[codeLength]), guess(new char[codeLength]),
	codeSequence(new bool[codeLength] {false}),
	guessSequence(new bool[codeLength] {false})
{
	srand(seed);
}

// Destructor
Mastermind::~Mastermind() {
	delete[] code;
	delete[] guess;
	delete[] codeSequence;
	delete[] guessSequence;
}

// Function "playGame" calls helper functions needed 
void Mastermind::playGame() {
	bool success = false; // Bool flag to determine if game won

	setCode(); // Set passcode

	// Read in guess code, compute black/white pegs and output
	cout << "Welcome to Mastermind! Please enter your first guess." << endl;
	for(int i = 0; i < guessLimit; i++) {
		readGuess(); // Read guess code from user
		int b = blackPeg();
		int w = whitePeg();
		resetSequence();
		cout << b << "b, " << w << "w" << endl; 
		if(b != codeLength && (i + 1) < guessLimit) {
			cout << guessLimit - i - 1 << " guesses left. Enter guess:" << endl;
		}
		if(b == codeLength) {
			success = true;
			break;
		}
	}

	// Output game won or lost
	if(success) {
		cout << "You won in guessCount guesses!" << endl;
	} else {
		cout << "You lost! The password was:" << endl;
		printCode();
	}

	// Recursively calling itself if play again
	cout << "Would you like to play again? (Y/N): ";
	if(playAgain())
		playGame();
}

// Function to set passcode based on random number generator
void Mastermind::setCode() {
	for(int i = 0; i < codeLength; i++) {
		switch(rand() % 6) {
			case 0:
				code[i] = 'A';
				break;
			case 1:
				code[i] = 'B';
				break;
			case 2:
				code[i] = 'C';
				break;
			case 3:
				code[i] = 'D';
				break;
			case 4:
				code[i] = 'E';
				break;
			case 5:
				code[i] = 'F';
				break;
			default:
				break;
		}
	}
}

// Function to read user's guess code
void Mastermind::readGuess() {
	char c;
	int numValid = 0;

	while(numValid < codeLength && cin >> c) {
		switch(c) {
			case 'A':
			case 'a':
				guess[numValid] = 'A';
				numValid++;
				break;
			case 'B':
			case 'b':
				guess[numValid] = 'B';
				numValid++;
				break;
			case 'C':
			case 'c':
				guess[numValid] = 'C';
				numValid++;
				break;
			case 'D':
			case 'd':
				guess[numValid] = 'D';
				numValid++;
				break;
			case 'E':
			case 'e':
				guess[numValid] = 'E';
				numValid++;
				break;
			case 'F':
			case 'f':
				guess[numValid] = 'F';
				numValid++;
				break;
			default:
				break;
		}
	}
}

// Function to print passcode
void Mastermind::printCode() {
	for(int i = 0; i < codeLength; i++) {
		cout << code[i];
	}
	cout << endl;
}

// Function to prompt user if play again
bool Mastermind::playAgain() {
	bool playAgain = false;
	char c;

	cin >> c;
	if(c == 'Y' || c == 'y')
		playAgain = true;

	return playAgain;
}

// Function to reset the 2 bool arrays
void Mastermind::resetSequence() {
	for(int i = 0; i < codeLength; i++) {
		codeSequence[i] = false;
		guessSequence[i] = false;
	}
}

// Function to compute black pegs
int Mastermind::blackPeg() {
	int blackPeg = 0;
	for(int i = 0; i < codeLength; i++) {
		if(guess[i] == code[i]) {
			blackPeg++;
			codeSequence[i] = true;
			guessSequence[i] = true;
		}
	}
	return blackPeg;
}

// Function to compute white pegs
int Mastermind::whitePeg() {
	int whitePeg = 0;
	for(int i = 0; i < codeLength; i++) {
		if(guessSequence[i])
			continue;
		for(int j = 0; j < codeLength; j++) {
			if(codeSequence[j])
				continue;
			if(guess[i] == code[j]){
				whitePeg++;
				guessSequence[i] = true;
				codeSequence[j] = true;

				#ifdef DEBUG
				cout << "iteration (i,j): (" << i << "," << j << ")" << endl;
				cout << "passcode: ";
				for(int i = 0; i < codeLength; i++) {
					cout << noboolalpha << codeSequence[i] << " ";
				}
				cout << endl;
				cout << "guesscode: ";
				for(int i = 0; i < codeLength; i++) {
					cout << noboolalpha << guessSequence[i] << " ";
				}
				cout << endl;
				#endif

				break;
			}
		}
	}
	return whitePeg;
}