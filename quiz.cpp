#include <fstream>
#include <iostream>
#include <random>
#include <set>
#include <sstream>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

typedef pair<string, string> flashcard;

void print_all(vector<flashcard> v) {

  for (flashcard c : v) {
    cout << c.first << " " << c.second << endl;
  }
}

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

  if (cards.size() < 4) {

    cerr << "Please have at least 4 cards" << endl;
    return 6;
  }

  // for randomness
  int max = cards.size() - 1;
  random_device rd; // Only used once to initialise (seed) engine
  mt19937 rng(rd());

  // which card is showing
  uniform_int_distribution<int> uni(0, max); // Guaranteed unbiased
  int front_index = uni(rng);

  // which option is correct
  vector<int> answer_indexes = {0, 0, 0, 0};
  uniform_int_distribution<int> correct_index_gen(
      0, (int)answer_indexes.size() - 1); // Guaranteed unbiased
  int correct = correct_index_gen(rng);

  // distinct answers
  set<int> rand_set = {front_index};

  // populate answers
  for (int i = 0; i < (int)answer_indexes.size(); i++) {
    if (i == correct)
      answer_indexes[i] = front_index;
    else {
      // regen until unique
      int x = uni(rng);
      while (rand_set.find(x) != rand_set.end()) {
        x = uni(rng);
      }
      rand_set.insert(x);
      answer_indexes[i] = x;
    }
  }

  // control loop
  char command;
  cout << "\nYou are using my very simple flash card reviwer" << endl;

  cout << "Direction: \n type q to quit \n p to print all\n or keep answering"
       << endl;

  cout << "\n====== Front side of your flash card ======= \n"
       << cards[front_index].first << endl;

  cout << "1) " << cards[answer_indexes[0]].second << endl
       << "2) " << cards[answer_indexes[1]].second << endl
       << "3) " << cards[answer_indexes[2]].second << endl
       << "4) " << cards[answer_indexes[3]].second << endl;

  while (cin >> command) {

    switch (command) {
    case 'p':
      print_all(cards);
      break;

    case 'q':
      cout << "Bye!" << endl;
      return 0;

    case '1':
      if (correct == 0)
        cout << "\nCorrect! :D" << endl << endl;
      else
        cout << "\nWrong! :(\n It was " << cards[front_index].second << endl
             << endl;
      break;
    case '2':
      if (correct == 1)
        cout << "\nCorrect! :D" << endl << endl;
      else
        cout << "\nWrong! :(\n It was " << cards[front_index].second << endl
             << endl;
      break;
    case '3':
      if (correct == 2)
        cout << "\nCorrect! :D" << endl << endl;
      else
        cout << "\nWrong! :(\n It was " << cards[front_index].second << endl
             << endl;
      break;
    case '4':
      if (correct == 3)
        cout << "\nCorrect! :D" << endl << endl;
      else
        cout << "\nWrong! :(\n It was " << cards[front_index].second << endl
             << endl;
      break;
    default:
      cerr << "Invalid command" << endl << endl;
      return 4;
    }
    // next one!
    front_index = uni(rng);

    correct = correct_index_gen(rng);
    rand_set = {front_index};

    // populate answers
    for (int i = 0; i < (int)answer_indexes.size(); i++) {
      if (i == correct)
        answer_indexes[i] = front_index;
      else {
        // regen until unique
        int x = uni(rng);
        while (rand_set.find(x) != rand_set.end()) {
          x = uni(rng);
        }
        rand_set.insert(x);
        answer_indexes[i] = x;
      }
    }
    cout << "====== Front side of your flash card ======= \n"
         << cards[front_index].first << endl;

    cout << "1) " << cards[answer_indexes[0]].second << endl
         << "2) " << cards[answer_indexes[1]].second << endl
         << "3) " << cards[answer_indexes[2]].second << endl
         << "4) " << cards[answer_indexes[3]].second << endl;
  }
  return 0;
}
