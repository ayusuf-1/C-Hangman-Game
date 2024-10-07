#include "hangman.h"

Hangman::Hangman()
{
  incorrectGuesses = 0; // number of incorrect guesses
  wins = 0; // number of wins
  losses = 0; // number of losses
  wordCount = 0; // words count of words in the file
  maxIncorrectGuesses = 7; // maximum number of incorrect guesses allowed
  remainingWords = 0; // remaining words in the file
  
  // random number generator
  srand(static_cast<unsigned int>(time(0)));
  
  // sets everything in the array to null variable 0
  for(int i = 0; i < 26 ; i++){
    usedLetters[i] = '0';
  }
  
  
}

bool Hangman::initializeFile(std::string filename)
{
  ifstream file(filename.c_str());
  if (!file) {
    return false;
  }
  
  
  while (file >> wordList[wordCount].word) {
    wordList[wordCount].used = false;
    wordCount++;
    remainingWords++;
  }
  
  file.close();
  return true;
}// end of initializeFile

void Hangman::displayStatistics()
{
  cout << endl;
  cout << "Wins: " << wins << endl;
  cout << "Losses: " << losses << endl;
  cout << "Words guessed from file: " << (wins + losses) << endl;
  cout << "Words remianing in file: " << wordCount << endl;
  cout << endl;
}// end of stats

bool Hangman::newWord() {
  int randomIndex;
  do {
    randomIndex = rand() % wordCount;
  } while (wordList[randomIndex].used);

  currentWord = wordList[randomIndex].word;
  displayWord = std::string(currentWord.length(), '_');
  wordList[randomIndex].used = true;
  remainingWords--;

  return true;
}// end of new word

void Hangman::displayGame()
{
  displayHangman();

  cout << "Word: ";

  // displays the word length in _
  for (size_t i = 0; i < currentWord.length(); i++) {
    if (usedLetters[currentWord[i] - 'A'] != '0') {
      cout << currentWord[i];
    } else {
      cout << " _ ";
    }
  }

  cout << endl;

  //letter are replaced with _
  cout << "Available letters: ";
  for (int i = 0; i < 26; i++) {
    char letter = static_cast<char>('A' + i);
    if (usedLetters[i] == '0') {
      cout << letter << " ";
    } else {
      cout << "_ ";
    }
  }
  cout << endl;
}// end of display game

bool Hangman::guess(char letter, bool &done, bool &won)
{
  int letterIndex = letter - 'A';
  if (usedLetters[letterIndex] != '0') {
    return false; // Letter already guessed
  }

  usedLetters[letterIndex] = letter;

  if (currentWord.find(letter) != string::npos) {
    updateDisplayWord(letter);
    if (displayWord == currentWord) {
      done = true;
      won = true;
      wins ++;
      resetGame();
    }
  } else {
    incorrectGuesses++;
    if (incorrectGuesses == maxIncorrectGuesses) {
      done = true;
      won = false;
      losses++;
      resetGame();
    }
  }
  cout << endl;
  return true;
}// end of guess

void Hangman::revealWord()
{
  cout << "The correct word was: " << currentWord << endl;
}// end of reveal word

void Hangman::updateDisplayWord(char letter)
{
  for (size_t i = 0; i < currentWord.length(); i++) {
    if (currentWord[i] == letter) {
      displayWord[i] = letter;
    }
  }
}// end of update display

void Hangman::resetGame()
{
  displayWord = string(currentWord.length(), '_');
  for (int i = 0; i < 26; i++) {
    usedLetters[i] = '0';
  }

  incorrectGuesses = 0;
  maxIncorrectGuesses = 7;

}// end of reset game


void Hangman::displayHangman() {
  const string hangmanParts[] = {
    "  -----  \n |     | \n |       \n |       \n |       \n |       \n-+-      \n",
    "  -----  \n |     | \n |     O \n |       \n |       \n |       \n-+-      \n",
    "  -----  \n |     | \n |     O \n |     | \n |       \n |       \n-+-      \n",
    "  -----  \n |     | \n |     O \n |    /| \n |       \n |       \n-+-      \n",
    "  -----  \n |     | \n |     O \n |    /|\\ \n |       \n |       \n-+-      \n",
    "  -----  \n |     | \n |     O \n |    /|\\ \n |    /  \n |       \n-+-      \n",
            "  -----  \n |     | \n |     O \n |    /|\\ \n |    / \\ \n |       \n-+-      \n"
  };

  cout << hangmanParts[incorrectGuesses] << endl;
}// end of display hangman



~
