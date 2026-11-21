#include <iostream>
#include <string>
#include <vector>
#include <random>

using namespace std;

enum check_state{
    MATCH,
    MISS,
    END
};

struct RNG_Engine{
    default_random_engine generator;
    uniform_int_distribution<int> distribution;

    int gen(){
        return distribution(generator);
    }
};

check_state check(char letter, int index, string sen);

bool initList(vector<string>& wordList, int& lengthVar);

void initRNG(RNG_Engine& engine, int rangeMin, int rangeMax);

string genSen(int senLength, vector<string>& wordList, RNG_Engine& engine);
