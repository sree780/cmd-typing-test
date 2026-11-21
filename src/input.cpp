#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <vector>
#include <chrono>

#include "input.hpp"


using namespace std;


bool initList(vector<string>& wordList, int& lengthVar){
    std::ifstream words("wordlist.txt");

    string line;
    lengthVar = 0;     // allows for refresh feature (not implemented),
    wordList.clear();  // in case you want to hot swap wordlists,
                        //for some reason.

    if (!words.is_open()){
        return false;
    }

    while (getline(words, line)){ //stores words
        lengthVar++;
        wordList.push_back(line);
    }

    words.close();
    return true;
}


void initRNG(RNG_Engine& engine, int rangeMin, int rangeMax){
    default_random_engine G(chrono::steady_clock::now().time_since_epoch().count()); //seeding with current time
    engine.generator = G;
    uniform_int_distribution<int> D(rangeMin,rangeMax);
    engine.distribution   = D;
}


string genSen(int senLength, vector<string>& wordList, RNG_Engine& engine){ 

    string result = "";
    vector<string> sen(senLength);

    for (string word: sen){
        word = wordList[engine.gen()];
        result += word.substr(1,word.size()-2) + " ";
    }
    
    return result.substr(0,result.size()-1);
}


check_state check(char letter, int index, string sen){
    if (sen[index] == letter){
        if (index == sen.size()-1){
            return END;
        }
        else{
            return MATCH;
        }
    }
    else{
        return MISS;
    }
}
