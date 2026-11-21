#include <iostream>
#include "interface.hpp"


using namespace std;

void printResults(int words, int keys, float time, int mistakes){
    cout << "[RESULTS]\n\n";
    cout << "Words Per Minute: " << 60*words/time << " WPM\n";
    cout << "Time taken: " << time <<"s\n";
    cout << "Accuracy: " << 100 - (mistakes/(float)(keys+mistakes))*100 << "%\n";
    cout << "Mistakes: " << mistakes << "\n";
    cout << "Words: " << words << " Words (" << keys << " Keys)\n\n";
    
}

void printMenu(){
    cout << "------------||  Typing  Test  ||--------------------------------------------------\n\n";
    cout << "[1] Play \n[2]Quit\n\n Enter 1 or 2: ";
}
