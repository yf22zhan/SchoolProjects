#include <iostream>
#include <sstream>
#include <string>
using namespace std;

int main(int argc, char *argv[]) {
  // Default line width
  int line_width = 25;

  int width_used = 0;
  string word;

  // If argument provided, set line_width
  if(argc > 1){
  	istringstream ss(argv[1]);
  	if(!(ss >> line_width)){
		cerr << "Invalid number " << argv[1] << endl;
		return 1;
  	}
  }

  // Read in word by word
  while(cin >> word){
  	// If word_length is greater than line_width
	if(word.length() > line_width){
		// If current display line has some words already, new line 
		if(width_used != 0){
			cout << endl;
		}
		// Output the lengthy word and set width_used
		int line_counter = 0;
		while((word.length() - line_width * line_counter) > line_width){
			for(int i = 0; i < line_width; i++){
				cout << word[i + line_width * line_counter];
  			}
  			cout << endl;
  			line_counter++;
		}
  		for(int i = 0; i < (word.length() - line_width * line_counter); i++){
			cout << word[i + line_width * line_counter];
  		}
  		if((word.length() - line_width * line_counter + 1) <= line_width){
			cout << " ";
			width_used = word.length() - line_width * line_counter + 1;
		}else{
			cout << endl;
			width_used = 0;
		}
	// If word_length is less than line_width and line is empty
	}else if((word.length() <= line_width) && (width_used == 0)){
		if(word.length() < line_width){
			cout << word << " ";
			width_used = word.length() + 1;
		}else{
			cout << word << endl;
			width_used = 0;
		}
	// // If word_length is less than line_width and line is not empty
	}else if((word.length() <= line_width) && (width_used != 0)){
		if((width_used + word.length()) < line_width){
			cout << word << " ";
			width_used = width_used + word.length() + 1;
		}else if((width_used + word.length()) == line_width){
			cout << word << endl;
			width_used = 0;
		}else{
			cout << endl;
			if(word.length() < line_width){
				cout << word << " ";
				width_used = word.length() + 1;
			}else{
				cout << word << endl;
				width_used = 0;
			}
		}
	}
  }
}
