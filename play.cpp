#include <iostream>
#include <string>
#include <cctype>
#include "hangman.h"

using namespace std;

int main() {
  char playAgain; // to ask user if they want to play again (y/n)

  do {
    Hangman hangmanGame; // hangmanGame Object
    char letter; // for user to guess letter
    bool gameOver = false; // state of game (gameOver)
    bool gameWon = false; // state of game (gameFalse)
    string filename = "/home/fac/sreeder/class/cs1430/p1input.dat";

    // reading the file
    if (!hangmanGame.initializeFile(filename)) {
      cout << "File problem...exiting" << endl;
      return 0;
    } else {
      cout << "File loaded OK" << endl << endl;
    }

    hangmanGame.displayStatistics();

    while (true) {
      hangmanGame.newWord();
      hangmanGame.displayGame();
      gameOver = false;
      gameWon = false;

      while (!gameOver) {
        cout << "What letter? ";
        cin >> letter;
        hangmanGame.guess(toupper(letter), gameOver, gameWon);
        hangmanGame.displayGame();
      }

      hangmanGame.revealWord();
      if (gameWon)
        cout << "You won!" << endl;

      hangmanGame.displayStatistics();

      cout << "Do you want to play again? (Y/N): ";
      cin >> playAgain;
      playAgain = toupper(playAgain);

      if (playAgain != 'Y') {
        break; // Exit the loop if the user doesn't want to play again
      }
    }

  } while (playAgain == 'Y');

  cout << "Thanks for playing!\n";

  return 0;
}// end of main
