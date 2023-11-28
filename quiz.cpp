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

class Quizzer {
private:
  int size;
  // max 9
  int num_ans;
  int q_index = 0;
  int curr_points = 0;
  int max_points = 0;
  // this will always has its unique copy
  vector<flashcard> cards;
  vector<int> ans_indexes;
  set<int> unique_indexes;
  mt19937 rng;
  uniform_int_distribution<int> card_gen;
  uniform_int_distribution<int> correct_index_gen;

public:
  // default to 4 ansers
  Quizzer(vector<flashcard> &v)
      : size(v.size()), num_ans(4), cards(v), ans_indexes(4), unique_indexes(),
        rng(random_device{}()), card_gen(0, v.size() - 1),
        correct_index_gen(0, 3) {}

  void instructions() {
    cout << "\nYou are using my very simple flash card reviwer" << endl;

    cout << "Direction: \n type q to quit \n p to print all\n or keep answering"
         << endl;
  }

  void print_cards() { print_all(cards); }

  void generate_new_question() {
    // for randomness
    // which card is showing
    q_index = card_gen(rng);

    // which option is correct
    ans_indexes = {0};
    int correct = correct_index_gen(rng);

    // distinct answers
    unique_indexes = {q_index};

    // populate answers
    for (int i = 0; i < num_ans; i++) {
      // the correct answer
      if (i == correct)
        ans_indexes[i] = q_index;
      else {
        // regen until unique
        int x = card_gen(rng);
        while (unique_indexes.find(x) != unique_indexes.end()) {
          x = card_gen(rng);
        }
        unique_indexes.insert(x);
        ans_indexes[i] = x;
      }
    }
  }

  void print_question() {
    cout << "====== Question || Points: " << curr_points << "/" << max_points
         << "======= \n"
         << cards[q_index].first << endl;

    for (int i = 0; i < num_ans; i++) {
      cout << i + 1 << ") " << cards[ans_indexes[i]].second << endl;
    }
  }

  void check_answer(int ans) {
    max_points++;
    if (ans == q_index) {
      curr_points++;
      cout << "\nCorrect! :D" << endl << endl;
    } else {
      cout << "\nWrong! :(\n It was " << cards[q_index].second << endl << endl;
    }
  }
};

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

  Quizzer quiz(cards);
  // empty this for memory
  cards = {};

  quiz.generate_new_question();
  quiz.print_question();

  // control loop
  char command;
  while (cin >> command) {

    // digits
    if (command >= '0' && command <= '9') {
      int i = command - '0' - 1;
      if (i == 0)
        i = 9;
      quiz.check_answer(i);
    }

    else {
      switch (command) {
      case 'p':
        quiz.print_cards();
        break;

      case 'q':
        cout << "Bye!" << endl;
        return 0;

        break;
      default:
        cerr << "Invalid command" << endl;
        return 4;
      }
      // next one!
    }
    quiz.generate_new_question();
    quiz.print_question();
  }
  return 0;
}
