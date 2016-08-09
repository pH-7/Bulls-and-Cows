//
//  BullsCowsWord.cpp
//  Bulls and Cows, c++ game - https://en.wikipedia.org/wiki/Bulls_and_Cows
//
//  Created by Pierre-Henry Soria on 06/08/2016.
//  Copyright © 2016 Pierre-Henry Soria. All rights reserved.
//  Email: pierrehenrysoria+github@gmail.com
//  My Github: https://github.com/pH-7
//

#include "BullsCowsWord.hpp"

using namespace std;

// It is proven that any number could be solved within 7 turns
// Source: https://en.wikipedia.org/wiki/Bulls_and_Cows
const int BullsCowsWord::MAX_TRIES = 7;

BullsCowsWord::BullsCowsWord() : replay(false), myCurrentTry(1), won(false)
{
}

string BullsCowsWord::showIntro()
{
    string text;
    text = "Welcome to Bulls & Cows Game!\n";
    text += "Can you guess the word\n";
    text += "Be smarter than this stupid game! :D";
    text += "\n\n";
    text += "               }   {         ___ \n";
    text += "               (o o)        (o o) \n";
    text += "        /-------\\ /          \\ /-------\\ \n";
    text += "       / | BULL |O            O|  COW  | \\ \n";
    text += "      *  |-,--- |              |-------|  * \n";
    text += "         ^      ^              ^       ^";
    text += "\n\n";
    return text;
}

string BullsCowsWord::showGameOver()
{
    string text;
    // Show msg if won/lost
    if (isWon()) {
         text = "Well done! You won ;)";
    } else {
        text = "Game Over! Could be better... :(\n";
        text += "The word to guess was \"" + myHiddenWord + "\"";
        text += "Okay... just play again!";
    }
    return text;
}


string BullsCowsWord::getHiddenWord() const
{
    // Initialize random number
    srand(time(NULL));

    // Letters from http://wordfinder.yourdictionary.com/letter-words/4
    string words[] = {"jazz", "buzz", "fizz", "quiz", "mazy", "jaup", "mozo", "jabs", "quey", "proxy", "quag"};

    int totalWords = sizeof(words)/sizeof(words[0]);
    int arrayIndex = rand() % totalWords;
    return words[arrayIndex];
}

bool BullsCowsWord::isReplay() const
{
    return replay;
}

void BullsCowsWord::askReplay()
{
    cout << "Do you want to replay? (y/n)" << endl;

    string input;
    getline(cin, input);
    replay = (input[0] == 'y' || input[0] == 'Y');
}

int BullsCowsWord::getHiddenWordLength() const
{
    return myHiddenWord.length();
}

int BullsCowsWord::getCurrentTry() const
{
    return myCurrentTry;
}

void BullsCowsWord::play()
{
    // Initialize the attributes
    reset();

    // Loop asking the answer while the gane is not finished
    while (!isWon() && getCurrentTry() <= MAX_TRIES) {

        // Valid the answer
        string answer = checkValidAnser();

        // Submit the valid guess
        BullCowCount BullCowCount = submitAnswer(answer);

        cout << endl;
        cout << "Bulls = " << BullCowCount.bulls << endl;
        cout << "Cows = " << BullCowCount.cows << endl;
        cout << endl;
    }
    cout << showGameOver() << endl;
}

void BullsCowsWord::reset()
{
    myHiddenWord = getHiddenWord();
    myCurrentTry = 1;
    won = false;
}

bool BullsCowsWord::isWon() const
{
    return won;
}

/*
 * Check the answer entered
 */
string BullsCowsWord::checkValidAnser()
{
    // Default values
    string answer = "";
    WordStatus status = WordStatus::invalid;

    do {
        cout << "Try " << getCurrentTry() << " of " << MAX_TRIES;
        std::cout << ". Type Your Guess: ";
        std::getline(std::cin, answer); // Get the answer fromt the player

        // Check the answer
        status = checkAnswerValidity(answer);
        switch (status)
        {
            case WordStatus::wrongLength:
                cout << "Please type a " << getHiddenWordLength() << " letters word\n\n";
                break;
            case WordStatus::wrong:
                cout << "Please type a word witout the same letters\n\n";
                break;
            case WordStatus::notLowerCase:
                cout << "Please type the word in lowercase\n\n";
                break;
            default:
                break; // OK, then the answer is valid
        }
    } while (status != WordStatus::ok); // Looping until there are no errors anymore

    return answer;
}

bool BullsCowsWord::isTheWord(string word)
{
    if (word.length() <= 1) {
        return true;
    }

    // Initialize the map containing the data of the game
    map<char, bool> letterSeen;
    for (auto letter : word) // for all letters of the word, set "auto" type (inference)
    {
        letter = tolower(letter); // set it insensitive

        // If the letter has been found in the map
        if (letterSeen[letter]) {
            return false;
        } else {
            // Otherwise, add it to the map
            letterSeen[letter] = true;
        }
    }
    return true;
}

BullCowCount BullsCowsWord::submitAnswer(string answer)
{
    myCurrentTry++;

    // Initialize the struct from the class
    BullCowCount BullCowCount;

    int wordLength = getHiddenWordLength();

    for (int countAll = 1; countAll <= wordLength; countAll++)
    {
        for (int countGuess = 1; countGuess <= wordLength; countGuess++)
        {
            // If there is a match
            if (answer[countGuess] == myHiddenWord[countAll])
            {
                if (countAll == countGuess) {
                    BullCowCount.bulls++; // Correct order, it's for bulls!
                } else {
                    BullCowCount.cows++; // If the order is incorrect, it's for cows
                }
            }
        }
    }

    won = (BullCowCount.bulls == wordLength);

    return BullCowCount;
}

WordStatus BullsCowsWord::checkAnswerValidity(string answer)
{
    if (!isTheWord(answer))
    {
        return WordStatus::wrong;
    }
    else if (!isLowerCase(answer))
    {
        return WordStatus::notLowerCase;
    }
    else if (answer.length() != getHiddenWordLength()) // If the length is wrong
    {
        return WordStatus::wrongLength;
    }
    else
    {
        // Now, everything seems OK!
        return WordStatus::ok;
    }
}

bool BullsCowsWord::isLowerCase(string word) const
{
    for (auto letter : word)
    {
        if (!islower(letter)) {
            return false; // If not lowercase
        }
    }
    return true;
}
