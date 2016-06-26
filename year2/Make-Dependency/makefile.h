#ifndef _MAKEFILE_
#define _MAKEFILE_
#include <string>
#include <iostream>
#include "target.h"

const int maxTargets = 20;

struct Makefile {
  std::ostream &out;  // Stream where Makefile will print its output.
  int clock;
  int numTargets;
  Target **targetArray; // Array of Target pointers

  Makefile(std::ostream &out = std::cout);
  ~Makefile();

  void addDepend(const std::string &t, const std::string &d);

  void changeTarget(const std::string &t);

  void rebuild(const std::string &t);

  // If target exists already, return its pointer, else return nullptr
  Target *searchTarget(const std::string &name);
};

#endif
