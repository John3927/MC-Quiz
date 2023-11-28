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

  int front_index = uni(rng);
  int a1 = uni(rng);
  int a2 = uni(rng);
  int a3 = uni(rng);
  int a4 = uni(rng);

  // control loop
  char command;

  cout << "Direction: \n type q to quit \n p to print all\n or keep answering"
       << endl;

  cout << "====== Front side of your flash card ======= \n"
       << cards[front_index].first << endl;

  cout << "1) " << cards[a1].second << endl
       << "2) " << cards[a2].second << endl
       << "3) " << cards[a3].second << endl
       << "4) " << cards[a4].second << endl;

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

    case '1':
      if (front_index == a1)
        cout << "\nCorrect! :D" << endl << endl;
      else
        cout << "\nWrong! :(" << endl << endl;
      break;
    case '2':
      if (front_index == a2)
        cout << "\nCorrect! :D" << endl << endl;
      else
        cout << "\nWrong! :(" << endl << endl;
      break;
    case '3':
      if (front_index == a3)
        cout << "\nCorrect! :D" << endl << endl;
      else
        cout << "\nWrong! :(" << endl << endl;
      break;
    case '4':
      if (front_index == a4)
        cout << "\nCorrect! :D" << endl << endl;
      else
        cout << "\nWrong! :(" << endl << endl;
      break;
    default:
      cerr << "Invalid command" << endl << endl;
      return 4;
    }
    // next one!
    front_index = uni(rng);
    a1 = uni(rng);
    a2 = uni(rng);
    a3 = uni(rng);
    a4 = uni(rng);

    cout << "====== Front side of your flash card ======= \n"
         << cards[front_index].first << endl;

    cout << "1) " << cards[a1].second << endl
         << "2) " << cards[a2].second << endl
         << "3) " << cards[a3].second << endl
         << "4) " << cards[a4].second << endl;
  }
  return 0;
}
