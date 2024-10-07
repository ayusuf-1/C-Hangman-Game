#ifndef HANGMAN_H
#define HANGMAN_H

using namespace std;

#include <iostream>
#include <fstream>
#include <ctime>
#include <string>

class Hangman {
public:
  Hangman();

  bool initializeFile(string filename);
  void displayStatistics();
  bool newWord();
  void displayGame();
  bool guess(char letter, bool &done, bool &won);
  void revealWord();

private:
  struct WordInfo {
    string word;
    bool used;
  };

  static const int MAX_WORDS = 100;
  WordInfo wordList[MAX_WORDS];
  int wordCount;
  int remainingWords;
  string currentWord;
  string displayWord;
  char usedLetters[26];
  int incorrectGuesses;
  int wins;
  int losses;
  int maxIncorrectGuesses;

  void resetGame();
  void updateDisplayWord(char letter);
  void displayHangman();


};

#endif // HANGMAN_H
