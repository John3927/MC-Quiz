#include <fstream>
#include <iostream>
#include <random>
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

  // for randomness
  int max = cards.size() - 1;
  random_device rd; // Only used once to initialise (seed) engine
  mt19937 rng(rd());
  uniform_int_distribution<int> uni(0, max); // Guaranteed unbiased
  int rand_int = uni(rng);

  // control loop
  char command;

  cout << "Direction: \n type q to quit \n p to print all\n or keep answering"
       << endl;

  cout << "====== Front side of your flash card ======= \n"
       << cards[rand_int].first;

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

    cout << "====== Front side of your flash card ======= \n"
         << cards[rand_int].first;
  }
  return 0;
}
