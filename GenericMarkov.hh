#ifndef GENERIC_MARKOV_H_INC
#define GENERIC_MARKOV_H_INC

#include <iostream>
#include <map>

template<class T>
class Markov {
private:
    std::map<std::pair<T, T>, uint64_t> _chain;
public:
    Markov(){}
    virtual ~Markov(){}

    inline void increaseStateWeight(std::pair<T, T> state, uint64_t value){
        _chain[state] += value;
    }

    inline void reduceStateWeight(std::pair<T, T> state, uint64_t value){
        _chain[state] -= value;
    }

    inline void setStateWeight(std::pair<T, T> state, uint64_t value){
        _chain[state] = value;
    }

    void printStateList(std::ostream& out){
        for(auto it = _chain.begin(); it != _chain.end(); ++it){
            out << it->first.first << "\t" << it->first.second
                << "\t" << it->second << std::endl;
        }
    }

    void printStats(std::ostream& out){
        out << "Keys: " << _chain.size() << std::endl;
    }
};


#endif // GENERIC_MARKOV_H_INC
