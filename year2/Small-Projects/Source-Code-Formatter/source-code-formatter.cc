#include <iostream>
#include <string>
using namespace std;

// To print indent for each new line
void printIndent(int indent){
	for(int i = 0; i < indent; i++){
		cout << " ";
	}
}

// To check if the read-in word is a special word
// If it is, deal with it accordingly
bool specialWordCheck(string &word, int &line_length, int &indent){
	bool is_special_word = false;

	if(word == ";"){
		is_special_word = true;
		if(line_length != 0){
  			cout << " " << word << endl;
  		}else{
  			printIndent(indent);
  			cout << word << endl;
  		}
  		line_length = 0;
  	}else if(word == "{"){
  		is_special_word = true;
  		if(line_length != 0){
  			cout << " " << word << endl;
  		}else{
  			printIndent(indent);
  			cout << word << endl;
  		}
  		indent++;
  		line_length = 0;
  	}else if(word == "}"){
  		is_special_word = true;
  		indent--;
  		if(line_length != 0){
  			cout << endl;
  			printIndent(indent);
  			cout << word << endl;
  		}else{
  			printIndent(indent);
  			cout << word << endl;
  		}
  		line_length = 0;
  	}else if(word == "//"){
  		is_special_word = true;
  		if(line_length != 0){
  			cout << " " << word;
  			getline(cin, word);
  			cout << word << endl;
  		}else{
  			printIndent(indent);
  			cout << word;
  			getline(cin, word);
  			cout << word << endl;
  		}
  		line_length = 0;
  	}

  	return is_special_word;
}

int main(int argc, char *argv[]) {
  int indent = 0;
  int line_length = 0;
  string word; // variable to store each read-in word

  // Read in word by word
  while(cin >> word){
  	// Check for special word first
  	// If not special word, print word normally
  	if(!(specialWordCheck(word, line_length, indent))){
  		if(line_length != 0){
  			cout << " " << word;
  			line_length = line_length + word.length() + 1;
  		}else{
  			printIndent(indent);
  			cout << word;
  			line_length = line_length + word.length();
  		}
  	}
  }

  return 0;
}
