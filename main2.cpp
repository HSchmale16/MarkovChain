#include <iostream>
#include <cmath>
#include <ctime>
#include <random>
#include <array>
#include <sstream>
#include <functional>
#include "GenericMarkov.hh"

class TestState {
public:
    int a;
    int b;
    int c;
    
    TestState(int _a, int _b, int _c)
        : a(_a), b(_b), c(_c) {}
    
    ~TestState(){}

    std::string toString()const{
        std::stringstream s;
        s << this->a << ":" << b << ":" << c;
        return s.str();
    }

    uint64_t hashSelf()const{
        return (a * 9576890767 + b) * 1500450271 + c;
    }

    friend std::ostream& operator<<(std::ostream& out, const TestState& s);

    bool operator==(TestState t){
        return (a == t.a) && (b == t.b) && (c == t.c);
    }

    bool operator<(const TestState& t)const{
        return this->hashSelf() < t.hashSelf();
    }
};

std::ostream& operator<<(std::ostream& out, const TestState& s){
    out << s.toString();
    return out;
}

// begin actual code
typedef std::pair<TestState, TestState> CPair;

int rnd(){
    return rand() % 10;
}

TestState getRndState(){
    return TestState(rnd(), rnd(), rnd());
}

CPair getRndPair(){
    return CPair(getRndState(), getRndState());
}

int main(int argc, char** argv){
    Markov<TestState> m;
    for(int i = 0; i < 1000000; i++){
        m.increaseStateWeight(getRndPair(), rand() % 100);
    }
    m.printStateList(std::cout);
}
