/*****************************************
** File:       proj1.cpp
** Author:     Layan Akhras
**
** This file contains the main driver program
   for a Wordle game. This file runs a program that
   prompts the user for letters to guess a word
   puzzle, and checks for case sensitivity, data
   type, repeated guesses, and correct/incorrect
   guesses.
*****************************************/

// Libraries
#include <iostream>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <string>
using namespace std;


// Global constants
const int NUM_WORDS = 4000;     // the length of the array that contains the imported words
const int LENGTH_ALPHABET = 26; // the length of the char array that stores the user's valid guesses
const int BAD_GUESSES = 6;      // the starting number of bad guesses the user has
const int LOWERCASE_MIN = 97;   // the smallest ascii number for lowercase letters
const int LOWERCASE_MAX = 122;  // the largest ascii number for lowercase letters

// Function prototypes

// Name: loadFile
// Precondition: NUM_WORDS is greater than zero
// Postcondition: returns the number of words in the file
int loadFile (string array[NUM_WORDS]);
// Name: chooseWord
// Precondition: number of words is greater than zero
// Postcondition: returns the chosen random string
string chooseWord(string array[], int numberOfWords);
// Name: underscoreCreator
// Precondition: length is greater than zero
// Postcondition: returns the underscore-populated cstring
string underscoreCreator(char underscoreWord[], int length);
// Name: displayPuzzle
// Precondition: length is greater than zero
// Postcondition: does not return anything, outputs the underscores and displays the puzzle
void displayPuzzle(int length, char underscores[]);
// Name: lettersRemaining
// Precondition: length is greater than zero
// Postcondition: returns the number of letters left to guess (or underscores)
int lettersRemaining(int length, char underscores[], int numOfUnderscores);
// Name: playGame
// Precondition: length, badGuesses, and underscoresLeft are greater than 0
// Postcondition: does not return anything, runs the guessing and input validation process
void playGame(int length, int badGuesses, string chosenWord, char guessList[LENGTH_ALPHABET], char underscores[], int underscoresLeft);


// Main function
int main (){
  string wordArray[NUM_WORDS];     // declares a string array that will be populated with the imported words
  int arrayWords = 0;              // stores the number of words in the imported file
  string chosenWord;               // stores the chosen random word that the user will guess
  int badGuesses = BAD_GUESSES;    // stores the starting number of bad guesses the user has
  char guessList[LENGTH_ALPHABET]; // stores each of the user's previous guesses in cstring
  int underscoresLeft = 0;         // stores the amount of letters the user still has to guess
  int wordLength;                  // stores the length of the chosen random word
  string playAgain;                // stores the user's response when prompted to play again

  // Loads the words
  cout << "Welcome to UMBC Word Guess!" << endl;
  arrayWords = loadFile(wordArray);
  cout << arrayWords << " words were imported" << endl;

  // Chooses a random word, determines the length, and declares array with that length
  chosenWord = chooseWord(wordArray, arrayWords);
  //cout << chosenWord << endl;
  wordLength = chosenWord.length();
  char underscoreWord[wordLength];

  // Outputs length of word, populates underscoreWord with underscores and begins the game
  cout << "Ok. I am thinking of a word with " << wordLength << " letters" << endl;
  underscoreCreator(underscoreWord, wordLength);
  playGame(wordLength, badGuesses, chosenWord, guessList, underscoreWord, underscoresLeft);

  // prompts the user for another game in a loop and populates guessList cstring with underscores
  // to clear the letters from the previous game
  cout << "Another game? (y/n)" << endl;
  cin >> playAgain;
  while (playAgain == "y"){
    for (int i = 0; i < LENGTH_ALPHABET; i++){
      guessList[i] = '_';
    }
    // chooses another word, calculates its length, creates a cstring with the new length
    chosenWord = chooseWord(wordArray, arrayWords);
    wordLength = chosenWord.length();
    char underscoreWord[wordLength];
    cout << "Ok. I am thinking of a word with " << wordLength << " letters" << endl;
    // resets underscoreWord from previous game and creates new underscores with new word
    underscoreCreator(underscoreWord, wordLength);
    // calls play game function to play again and prompts the user for another game again
    playGame(wordLength, badGuesses, chosenWord, guessList, underscoreWord, underscoresLeft);
    cout << "Another game? (y/n)" << endl;
    cin >> playAgain;
  }
  cout << "Ok. Goodbye!" << endl;
}


// loads the text file and populates the given array with the words from the file
int loadFile (string array[NUM_WORDS]){
  int count = 0;   // stores the amount of words counted
  string word;     // stores each word as it is added to the array
  // open the file, load each word as an element in the array, and close the file
  ifstream myfile ("words.txt");
  if (myfile.is_open()){
    for (int i = 0; myfile >> word; i++){
      array[i] = word;
      count++;
    }
    cout << "Your file was imported!" << endl;
  }else{
    cout << "Unable to open file" << endl;
  }
  myfile.close();
  return count;
}


// picks and returns a random word from an array
string chooseWord(string array[], int numberOfWords){
  int randomNum; // stores the random number
  // pick a random number in the domain of the number of words
  // and return the word at that index
  srand(time(NULL));
  randomNum = rand() % numberOfWords + 1;
  return array[randomNum];
}


// populates an array with underscores and returns it
string underscoreCreator(char underscoreWord[], int length){
  // loop through the length of the word and add an underscore
  // for each letter
  for (int i = 0; i < length; i++){
    underscoreWord[i] = '_';
  }
  return underscoreWord;
}


// loops through the cstring and displays it with spaces in between each element
void displayPuzzle(int length, char underscores[]){
  for (int i = 0; i < length; i++){
    cout << underscores[i] << " ";
  }
  cout << endl << endl;
}


// calculates and returns the amount of letters left to guess
int lettersRemaining(int length, char underscores[], int numOfUnderscores){
  // loop through the ctring and increment each time there is an underscore
  for (int i = 0; i < length; i++){
    if (underscores[i] == '_'){
      numOfUnderscores++;
      }
  }
  cout << numOfUnderscores << " letters remain." << endl;
  return numOfUnderscores;
}


// runs the guessing and input validation process of the game
void playGame(int length, int badGuesses, string chosenWord, char guessList[LENGTH_ALPHABET], char underscores[], int underscoresLeft){
  char userGuess;            // stores the user's guess
  bool correctGuess = false; // a marker for running code only if the guess is correct
  int underscoresNum;        // stores the amount of letters left to guess
  // do while loop that runs as long as the user still has either bad guesses or letters to guess left
  do{

    // calculate letters left to guess and display the puzzle
    underscoresNum = lettersRemaining(length, underscores, underscoresLeft);
    displayPuzzle(length, underscores);
    cout << "What letter would you like to guess?" << endl;
    cin >> userGuess;

    // loop through the list of previous guesses (guessList)
    // if the guess is in there, then it has already been guessed
    // if not, then it has not been guessed already
    for (int i = 0; i < LENGTH_ALPHABET; i++){
      // if it has been guessed already, subtract a bad guess
      if (userGuess == guessList[i]){
	badGuesses--;
        cout << "That letter was already guessed" << endl;
        cout << badGuesses << " bad guesses remain" << endl;
      }
    }

    // check if the guess is in the word
    for (int i = 0; i < length; i++){
      // loop through the word, if the letter is in there, then it is correct
      // if its correct, update the underscore at that exact index to the user's guess
      if (userGuess == chosenWord[i]){
        correctGuess = true;
        underscores[i] = userGuess;
      }
    }

    // if the guess is correct
    if (correctGuess == true){
      cout << "The guess is correct" << endl;
      // convert to int and subtract 97 to calculate its ascii
      // at that index, add it to the cstring (guessList)
      int arrayIndex = int(userGuess) - LOWERCASE_MIN;
      guessList[arrayIndex] = userGuess;
      // subtract one from the amount of letters left to guess
      underscoresNum--;
      correctGuess = false;
    }
 // but if the guess is not in the word
    else if (correctGuess == false){
      // store the guess in the same way
      int arrayIndex = int(userGuess) - LOWERCASE_MIN;
        guessList[arrayIndex] = userGuess;
        // subtract a bad guess
        badGuesses--;
        cout << "There is no " << userGuess << " in the puzzle" << endl;
        cout << "You have " << badGuesses << " bad guesses left" << endl;
    }
    // run the loop as long as they still have bad guesses and underscores to guess
  }while(badGuesses > 0 and underscoresNum > 0);


  // if they run out of underscores to guess, they win
  if (underscoresNum <= 0){
    cout << "Congrats you won!" << endl;
    cout << "The correct word was: " << chosenWord << endl;
    // if they run out of bad guesses, they lose
  }else if (badGuesses <= 0){
    cout << "Sorry, you lost" << endl;
    cout << "The correct word was: " << chosenWord << endl;
    // give control back to main to prompt the user for another game
  }
}

