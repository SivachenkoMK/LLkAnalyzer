//
// Created by mikhail.syvachenko on 28.10.2023.
//

#ifndef LLKANALYZER_GRAMMAR_H
#define LLKANALYZER_GRAMMAR_H
#include <utility>
#include <vector>
#include "transition.h"

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
    vector<char> first(char letter, int k);

private:
    int terminalAmount;
    int nonTerminalAmount;
    int transitionsAmount;
    char axiom;
    vector<char> nonTerminals;
    vector<char> terminals;
    vector<transition> transitions;

    vector<char> first(char letter, int k, vector<char> processedNonTerminals);

    static bool isEpsilon(vector<char> word);
    static vector<char> getEpsilonVector();
    static char getEpsilon();
};

#endif //LLKANALYZER_GRAMMAR_H
