#include <iostream>
using namespace std;

struct IntArray {
  int size;
  int capacity;
  int *contents;
};

// Helper function to double array.capacity when (size == capacity)
void doubleCapacity(IntArray& array) {
  if(array.capacity == 0) { // Case for doubling capacity for empty array
    IntArray newArray;
    newArray.size = 0;
    newArray.capacity = 5;
    newArray.contents = new int[newArray.capacity] {0};
    swap(array, newArray);
    delete[] newArray.contents;
  } else { // Case for doubling capacity when array not empty
    IntArray newArray;
    newArray.size = array.size;
    newArray.capacity = array.capacity * 2;
    newArray.contents = new int[newArray.capacity] {0};

    for(int i = 0; i < array.size; i++) {
      newArray.contents[i] = array.contents[i];
    }
    swap(array, newArray);
    delete[] newArray.contents;
  }
  return;
}

IntArray readIntArray() {
  // Create an IntArray obj and initialize it
  IntArray array;
  array.size = 0;
  array.capacity = 0;
  array.contents = nullptr;

  int integer; // Variable to read in integer

  // Read in an integer and store in in array
  while(cin >> integer && !cin.eof()) {
    if(array.size == array.capacity) {
      doubleCapacity(array);
    }
    array.contents[array.size++] = integer;
  }

  cin.clear();
  cin.ignore();

  return array;
}

void addToIntArray(IntArray& ia) {
  int integer; // Variable to read in integer

  // Read in integer and append to array
  while(cin >> integer && !cin.eof()) {
    if(ia.size == ia.capacity) {
      doubleCapacity(ia);
    }
    ia.contents[ia.size++] = integer;
  }

  cin.clear();
  cin.ignore();
}

// Print array
void printIntArray(const IntArray& ia) {
  for(int i = 0; i < ia.size; i++) {
    cout << ia.contents[i] << " ";
  }
  cout << endl;
}

// Do not change this function!

int main() {  // Test harness for IntArray functions.
  bool done = false;
  IntArray a[4];
  a[0].contents = a[1].contents = a[2].contents = a[3].contents = nullptr;

  while(!done) {
    char c;
    char which;

    // Note:  prompt prints to stderr, so it should not occur in .out files
    cerr << "Command?" << endl;  // Valid commands:  ra, rb, rc, rd,
                                 //                  +a, +b, +c, +d,
                                 //                  pa, pb, pc, pd, q
    cin >> c;  // Reads r, +, p, or q
    if (cin.eof()) break;
    switch(c) {
      case 'r':
        cin >> which;  // Reads a, b, c, or d
        delete [] a[which-'a'].contents;
        a[which-'a'].contents = nullptr;
        a[which-'a'] = readIntArray();
        break;
      case '+':
        cin >> which;  // Reads a, b, c, or d
        addToIntArray(a[which-'a']);
        break;
      case 'p':
        cin >> which;  // Reads a, b, c, or d
        printIntArray(a[which-'a']);
        cout << "Capacity: " << a[which-'a'].capacity << endl;
        break;
      case 'q':
        done = true;
    }
  }

  for (int i = 0; i < 4; ++i) delete [] a[i].contents;
}
