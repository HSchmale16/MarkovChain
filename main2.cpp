#include <iostream>
#include <cmath>
#include <ctime>
#include <random>
#include <array>
#include "GenericMarkov.hh"

typedef std::pair<char, char> CPair;

char getRndLetter() {
    static std::default_random_engine generator;
    static std::array<char, 4> intervals {'A', 'Z', 'a', 'z'};
    static std::array<double, 3> weights {1.0, 0.0, 1.0};
    static std::piecewise_constant_distribution<float>
        distribution(intervals.begin(), intervals.end(), weights.begin());
    return (char)distribution(generator);
}
    
int main(int argc, char** argv){
    srand(time(NULL));
    Markov<char> m;
    for(int i = 0; i < 100; i++){
        m.increaseStateWeight(CPair(getRndLetter(), getRndLetter()),
            rand() % 100);
    }
    m.printStateList(std::cout);
    m.printStats(std::cout);
    std::cout << sizeof(CPair) << std::endl;
    std::cout << sizeof m << std::endl;
}
