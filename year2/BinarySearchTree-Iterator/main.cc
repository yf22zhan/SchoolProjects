#include <iostream>
#include <string>
#include <sstream>
#include "tree.h"
using namespace std;

// Note:  this program will not compile until you have written the functions
//        required for the Iterator pattern.

int main() {
  string s;
  Tree *t = new Tree;

  while (getline(cin, s)) {
    istringstream ss{s};
    string cmd;
    ss >> cmd;
    if (cmd == "i") {  // i n  inserts the integer n into the tree
	  int n;
      ss >> n;
      t->insert(n);
    }
    if (cmd == "p") {  // p  prints the tree
      for (auto d : *t) {
        cout << d << endl;
      }
    }
    if (cmd == "c") {  // c  creates a new tree
      delete t;
      t = new Tree;
    }
  }
  delete t;
}
