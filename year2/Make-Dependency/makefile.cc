#include "makefile.h"
#include <iostream>
#include <string>
using namespace std;

// Constructor
Makefile::Makefile(ostream &out) :
	out{out},
	clock{0},
	numTargets{0},
	targetArray{ new Target*[maxTargets] {nullptr} } {
}

// Delete all target objects stored in heap
Makefile::~Makefile() {
	for(int i = 0; i < numTargets; i++) {
		delete targetArray[i];
	}
	delete[] targetArray;
}

// Add dependency
void Makefile::addDepend(const string &t, const string &d) {
	Target *target = searchTarget(t);
	Target *depend = searchTarget(d);

	// If target is not created
	if(target == nullptr) {
		if (numTargets == maxTargets) {
			out << "Max targets exceeded" << endl;
			return;
		}
		target = new Target{ t };
		targetArray[numTargets] = target;
		numTargets++;
	}

	// If depend is not created
	if (depend == nullptr) {
		if (numTargets == maxTargets) {
			out << "Max targets exceeded" << endl;
			return;
		}
		depend = new Target{ d };
		targetArray[numTargets] = depend;
		numTargets++;
	}

	target->addDepend(depend);
}

// Touch target
void Makefile::changeTarget(const string &t) {
	clock++;
	Target *target = searchTarget(t);

	if (target == nullptr)
		return;

	// If target is a leaf obj, update timestamp
	if (target->isLeaf()) {
		target->update(clock);
		out << target->name << " updated at time " << target->lastUpdated() << endl;
	}
	else {
		out << "Cannot update non-leaf object" << endl;
	}
}

// Rebuild calls build on target if it exists
void Makefile::rebuild(const string &t) {
	Target *target = searchTarget(t);

	if (target == nullptr)
		return;

	target->build();
}

// If target exists already, return its pointer, else return nullptr
Target *Makefile::searchTarget(const std::string &name) {
	for(int i = 0; i < numTargets; i++) {
		if(name == targetArray[i]->name)
			return targetArray[i];
	}
	return nullptr;
}