//
//  BullsCowsWord.hpp
//  Bulls and Cows, c++ game - https://en.wikipedia.org/wiki/Bulls_and_Cows
//
//  Created by Pierre-Henry Soria on 06/08/2016.
//  Copyright © 2016 Pierre-Henry Soria. All rights reserved.
//  Email: pierrehenrysoria+github@gmail.com
//  My Github: https://github.com/pH-7
//

#ifndef BullsCowsWord_hpp
#define BullsCowsWord_hpp

#include <iostream>
#include <string>
#include <map>

struct BullCowCount
{
    int bulls = 0;
    int cows = 0;
};

// From C++ 11, we can use "class" keyword to have each enum value scoped
enum class WordStatus
{
    invalid,
    ok,
    wrong,
    notLowerCase,
    wrongLength
};

class BullsCowsWord
{
    static const std::string HIDDEN_WORD;

    public:
    BullsCowsWord();
    BullsCowsWord(std::string);
    std::string showIntro();
    std::string showGameOver();
    void askReplay() const;
    bool isReplay() const;
    void askReplay();
    void play();
    void reset();
    bool isTheWord(std::string word);

    // Getters are const! (as they just return the property value and cannot modify them)
    int getMaxTries() const;
    int getCurrentTry() const;
    int getHiddenWordLength() const;

    // Won't change anything as well, so "const" functions too
    bool isLowerCase(std::string) const;
    bool isWon() const;

    std::string checkValidAnser();
    BullCowCount submitAnswer(std::string);
    WordStatus checkAnswerValidity(std::string);

    private:
    bool replay;
    int myCurrentTry;
    bool won;
    std::string myHiddenWord;

};

#endif /* BullsCowsWord_hpp */
