//
//  main.cpp
//  Bulls and Cows, c++ game - https://en.wikipedia.org/wiki/Bulls_and_Cows
//
//  Created by Pierre-Henry Soria on 06/08/2016.
//  Copyright © 2016 Pierre-Henry Soria. All rights reserved.
//  Email: pierrehenrysoria@gmail.com
//  My Github: https://github.com/pH-7
//

#include <iostream>
#include <string>
#include "BullsCowsWord.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    BullsCowsWord* BCW(0);
    do {
        BCW = new BullsCowsWord;
        cout << BCW->showIntro();
        BCW->getGuess();

        delete BCW; // Deallocates the memory
        BCW = 0; // Set to 0 it the pointer doesn't point to anything
    }
    while (BCW->isReplay());
    
    return 0;
}