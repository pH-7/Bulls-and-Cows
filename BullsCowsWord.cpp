//
//  BullsCowsWord.cpp
//  Bulls and Cows, c++ game - https://en.wikipedia.org/wiki/Bulls_and_Cows
//
//  Created by Pierre-Henry Soria on 06/08/2016.
//  Copyright © 2016 Pierre-Henry Soria. All rights reserved.
//  Email: pierrehenrysoria@gmail.com
//  My Github: https://github.com/pH-7
//

#include "BullsCowsWord.hpp"

using namespace std;

const int BullsCowsWord::MAX_TRIES = 8;
const string BullsCowsWord::HIDDEN_WORD = "ant";

BullsCowsWord::BullsCowsWord() : replay(false), myCurrentTry(0), myMaxTries(0)
{
    reset();
}

BullsCowsWord::BullsCowsWord(string answer)
{
    input = answer;
}

string BullsCowsWord::showIntro()
{
    string text;
    text = "Welcome to Bulls & Cows Game!\n";
    text += "Can you guess the word\n";
    text += "Be smarter than this stupid game! :D\n";
    return text;
}

bool BullsCowsWord::isReplay() const
{
    return replay;
}

void BullsCowsWord::askReplay()
{
    getline(cin, input);
    replay = (input[0] == 'y' || input[0] == 'Y');
}

int BullsCowsWord::getMaxTries() const
{
    return myMaxTries;
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
    for(int i = 1; i <= MAX_TRIES; i++)
    {
        cout << "Your guess was" << getGuess() << endl;
    }

}

void BullsCowsWord::reset()
{
    myMaxTries = MAX_TRIES;
    myHiddenWord = HIDDEN_WORD;
    myCurrentTry = 1;
}

bool BullsCowsWord::isGameWon() const
{
    return false;
}

string BullsCowsWord::getGuess() const
{
    int currentTry(0);
    currentTry = getCurrentTry();
    
    // Get the answer fromt the player
    cout << "Enter Your Guess: " << endl;
    
    string guess;
    getline(cin, guess);
    return guess;
}

bool BullsCowsWord::isTheWord(string word)
{
    if (word.length() <= 1) {
        return true;
    }
    
    // Initialize the map
    map<char, bool> letterSeen;
    for (auto letter : word) // for all letters of the word, set aut type (inference)
    {
        letter = tolower(letter); // set it incenstitve
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

WordStatus BullsCowsWord::checkAnswerValidity(string answer)
{
    if (isTheWord(answer))
    {
        return WordStatus::wrong;
    }
    else if (isLowerCase(answer))
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
            return false;
        }
    }
    return true;
}
