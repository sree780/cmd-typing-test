#include <iostream>
#include "input.hpp"
#include "interface.hpp"
#include <conio.h>
#include <chrono>


using namespace std;

int gameloop(vector<string>& wordList, RNG_Engine& engine, int diff) {
    bool isEnd = false;

    string sen = genSen(diff, wordList, engine);

    int mistakes = 0; //counters
    int words = 1;
    int index = 0;

    char data;   
    int key;

    chrono::steady_clock::time_point begin;
    chrono::steady_clock::time_point end;

    std::cout << sen;
    std::cout<< "\n";

    while (!isEnd) { //impossible naturally

        //reading

        if (_kbhit()) {
            key = _getch();
            if (key >= 32 && key <= 126) { // basic ASCII
                data = static_cast<char>(key);
            }
            else{
                continue; //invalid key
            }
        }
        else{
            continue; //keyboard not hit
        }

        if (index==0 && mistakes==0){
            begin = chrono::steady_clock::now(); // starts timer when first valid key is clicked
        }
        
        //processing

        switch (check(data, index, sen)){
            case MATCH:
                index++;
                std::cout << data;
                if (data == ' '){   //word check
                    words++;
                }
                break;
            
            case MISS:
                mistakes++;
                break;

            case END:
                index++;
                std::cout << data << "\n\n";
                isEnd = true;
        }
    }

    end = chrono::steady_clock::now();
    float time = chrono::duration_cast<std::chrono::milliseconds>(end - begin).count()/1000.0;

    printResults(words, index+1, time, mistakes);
    return 1;
}


bool menu(){
    int query;
    while (true)
    {
        printMenu();
        if(!(std::cin >> query) || query<1 || query>2){ //1 or 2 only
                std::cin.clear(); 
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                cout << "\033[2J\033[1;1H";
            }
        else{
            break;
        }
    }
    switch (query){
        case 1:
            return true;
        case 2:
            return false;
    }
    return false;
}


int main(){
    if (!menu()){
        return 0;
    }
    vector<string> W;
    int L;

    if (!initList(W, L)){ // load check + assign word list and length
        return -1;
    }

    RNG_Engine E;
    initRNG(E, 0, L-1);

    int query;

    while (true){
        while (true)
        {
            std::cout << "No. of words? : ";
            if(!(std::cin >> query) || query < 1){
                std::cin.clear(); 
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                cout << "\033[2J\033[1;1H";
            }
            else{
                break;
            }
        }
        

        gameloop(W, E, query);
        if (!menu()){
            break;
        }
        
    }
    return 0;
}

