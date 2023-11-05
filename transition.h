//
// Created by mikhail.syvachenko on 28.10.2023.
//

#ifndef LLKANALYZER_TRANSITION_H
#define LLKANALYZER_TRANSITION_H
#include <vector>
#include <utility>
#include "static_definitions.h"

using namespace std;

class transition {
public:
    transition(char from, vector<char> to);

    ~transition();

    [[nodiscard]] char getFrom() const;
    [[nodiscard]] vector<char> getTo() const;

private:
    char from;
    vector<char> to;
    static vector<char> removeEpsilons(vector<char> to);
};


#endif //LLKANALYZER_TRANSITION_H
