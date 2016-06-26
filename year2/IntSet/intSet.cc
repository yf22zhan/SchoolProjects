#include "intSet.h"
#include <iostream>
#include <sstream>

// Constructor
intSet::intSet() :
	data{nullptr},
	size{0},
	capacity{0}
{}

// Copy Constructor
intSet::intSet(const intSet& is) :
	data{nullptr},
	size{is.size},
	capacity{is.capacity}
{
	// If the intSet argument has data, then deep copy the data
	if (is.size) {
		data = new int[is.capacity] {0};
		for (int i = 0; i < is.size; i++) {
			data[i] = is.data[i];
		}
	}
}

// Destructor
intSet::~intSet() {
	if (size) {
		delete[] data;
	}
}

// Move Constructor
intSet::intSet(intSet &&is) :
	data{is.data},
	size{is.size},
	capacity{is.capacity}
{
	is.data = nullptr;
}

// Assignment operator
intSet &intSet::operator=(const intSet& is) {
	intSet copy = is;
	swap(copy);
	return *this;
}

// Move assignment operator
intSet &intSet::operator=(intSet &&is) {
	swap(is);
	return *this;
}

// Swap function
void intSet::swap(intSet &is) {
	int *copyData = data;
	int copySize = size;
	int copyCapacity = capacity;

	data = is.data;
	size = is.size;
	capacity = is.capacity;

	is.data = copyData;
	is.size = copySize;
	is.capacity = copyCapacity;
}

// Set union
intSet intSet::operator|(const intSet &other) {
	intSet setUnion{*this};
	for (int i = 0; i < other.size; i++) {
			setUnion.add(other.data[i]); // Add(int e) only adds int e if it does not exist in the data array
	}
	return setUnion;
}

// Set intersection
intSet intSet::operator&(const intSet &other) {
	intSet setIntersection;
	for (int i = 0; i < other.size; i++) {
		if (contains(other.data[i]))
			setIntersection.add(other.data[i]); // Add in-common int to setIntersection
	}
	return setIntersection;
}

// Set equality.
bool intSet::operator==(const intSet &other) {
	if (size != other.size) // If cardilanities are not the same, not equal
		return false;

	for (int i = 0; i < size; i++) { // each pair of ints at the same index have to be same since sorted
		if (data[i] != other.data[i]) {
			return false;
		}
	}

	return true;
}

// True if s is a subset of *this
bool intSet::isSubset(intSet s) {
	if (size < s.size) // If cardinality of s is greater, then not subset
		return false;

	if (s.size == 0) // Empty set is a subset of any set
		return true;

	int offset = binarySearch(s.data[0], 0, size - 1); // Search for the index the subset s starts at in intSet *this

	if (offset == -1) // If *this does not contain the first int of the intSet s, then not subset
		return false;

	if ((size - offset) < s.size) // The size of the remaining portion of the set *this after first match is less than the size of s, not subset
		return false;

	for (int i = 0; i < s.size; i++) { // each pair of ints at the same index have to be same since sorted
		if (data[i + offset] != s.data[i]) {
			return false;
		}
	}

	return true;
}

// True if *this contains e
bool intSet::contains(int e) {
	return binarySearch(e, 0, size - 1) != -1;
}

// Adds int e to this set
void intSet::add(int e) {
	if (size == capacity) { // First time enter int, capacity = 5
		if (capacity == 0) {
			capacity = 5;
			data = new int[capacity] {0};
		}
		else {
			capacity = capacity * 2; // Double capacity
			int *tmp = new int[capacity] {0};
			for (int i = 0; i < size; i++) {
				tmp[i] = data[i];
			}
			delete[] data;
			data = tmp;
		}
	}
	if (contains(e)) // If int e is in the set, do nothing
		return;
	data[size] = e;
	size++;
	sort(0, size - 1);
}

// Removes int e ot this set
void intSet::remove(int e) {
	int foundAtIndex = binarySearch(e, 0, size - 1);
	if (foundAtIndex != -1) { // If contain int e, swap element e with the last element and decrease size by 1
		data[foundAtIndex] = data[size - 1];
		size--;
		sort(0, size - 1);
	}
}

// Quicksort
// Sort the data array in ascending order
void intSet::sort(int low, int high) {
	int i = low, j = high;
	int tmp;
	int pivot = data[low + (high - low) / 2];

	while (i <= j) {
		while (data[i] < pivot)
			i++;
		while (data[j] > pivot)
			j--;
		if (i <= j) {
			tmp = data[i];
			data[i] = data[j];
			data[j] = tmp;
			i++;
			j--;
		}
	}

	if (low < j)
		sort(low, j);
	if (i < high)
		sort(i, high);
}

// Search to see if the data array contains int e
// Return -1 if not found, otherwise the index
int intSet::binarySearch(int e, int low, int high) {
	if (low > high) {
		return -1;
	}

	int middle = low + (high - low) / 2;
	if (e == data[middle]) {
		return middle;
	}
	else if (e < data[middle]) {
		return binarySearch(e, low, middle - 1);
	}
	else {
		return binarySearch(e, middle + 1, high);
	}
}

// Print the data array in (x,y,z,..) format
std::ostream& operator<<(std::ostream& out, const intSet& is) {
	out << "(";
	for (int i = 0; i < is.size - 1; i++) {
		out << is.data[i] << ",";
	}
	if (is.size > 0)
		out << is.data[is.size - 1];
	out << ")";
	return out;
}
