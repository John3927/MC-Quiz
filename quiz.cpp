#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

typedef pair<string, string> flashcard;

int main(int argc, char *argv[]) {

  if (argc < 2) {
    cerr << "Please provide a file name" << endl;
    return 1;
  }

  // this is our list of documents to parse
  ifstream content(argv[1]);
  if (!content.is_open()) {
    // file list is bad ...
    cerr << "Error opening file: " << argv[1] << endl;

    return 2;
  }

  // parse
  vector<flashcard> cards;

  string line;
  while (getline(content, line)) {
    istringstream stream(line);
    string q;
    string a;

    // question=answer
    if (getline(stream, q, '=')) {
      getline(stream, a);
      cards.push_back(make_pair(q, a));
    } else {
      cerr << "Error parsing file: " << argv[1] << endl;
      return 3;
    }
  }

  char command;

  while (cin >> command) {
    switch (command) {
    case 'p':
      for (flashcard c : cards) {
        cout << c.first << " " << c.second << endl;
      }
      break;

    case 'q':
      cout << "Bye!" << endl;
      return 0;

    default:
      cerr << "Invalid command" << endl;
      return 4;
    }
  }
  return 0;
}
