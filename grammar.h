//
// Created by mikhail.syvachenko on 28.10.2023.
//

#ifndef LLKANALYZER_GRAMMAR_H
#define LLKANALYZER_GRAMMAR_H
#include <utility>
#include <vector>
#include <iostream>
#include <algorithm>
#include "transition.h"
#include "static_definitions.h"

using namespace std;

class grammar {
public:
    grammar(char axiom, vector<char> terminals, vector<char> nonTerminals, vector<transition> transitions);

    ~grammar();

    [[nodiscard]] char getAxiom() const; // Axiom is start non-terminals
    [[nodiscard]] int getTerminalsAmount() const;

    [[nodiscard]] int getNonTerminalsAmount() const;

    [[nodiscard]] int getTransitionsAmount() const;

    vector<char> getTerminals();

    vector<char> getNonTerminals();

    vector<transition> getTransitions();

    // TODO: Rewrite with First K
    vector<vector<char>> first(char letter, int k);

private:
    int terminalAmount;
    int nonTerminalAmount;
    int transitionsAmount;
    char axiom;
    vector<char> nonTerminals;
    vector<char> terminals;
    vector<transition> transitions;

    vector<vector<vector<char>>> first(char letter, int k, vector<char> processedNonTerminals);

    //static vector<vector<char>> concatenateResults(vector<vector<vector<char>>> stepsResult, int k);
    static void printVector(const vector<vector<vector<char>>>& vec);
    static bool recursiveIterationBeyondLimit(char letter, vector<char> processedNonTerminals, int k);
};

#endif //LLKANALYZER_GRAMMAR_H
