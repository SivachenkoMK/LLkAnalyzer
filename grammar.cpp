//
// Created by mikhail.syvachenko on 28.10.2023.
//
#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"
#include <algorithm>
#include <set>
#include <utility>
#include "grammar.h"

grammar::grammar(char axiom, vector<char> terminals, vector<char> nonTerminals, vector<transition> transitions) {
    this->axiom = axiom;
    this->terminals = std::move(terminals);
    this->nonTerminals = std::move(nonTerminals);
    this->transitions = std::move(transitions);
    this->nonTerminalAmount = int(getNonTerminals().size());
    this->terminalAmount = int(getTerminals().size());
    this->transitionsAmount = int(getTransitions().size());
}

grammar::~grammar() = default;

vector<char> grammar::getTerminals() {
    return terminals;
}

vector<char> grammar::getNonTerminals() {
    return nonTerminals;
}

vector<transition> grammar::getTransitions() {
    return transitions;
}

int grammar::getTerminalsAmount() const {
    return terminalAmount;
}

int grammar::getNonTerminalsAmount() const {
    return nonTerminalAmount;
}

int grammar::getTransitionsAmount() const {
    return transitionsAmount;
}

char grammar::getAxiom() const {
    return axiom;
}

vector<char> grammar::first(char nonTerminalElement) {
    return this->first(nonTerminalElement, {});
}

vector<char> grammar::first(char nonTerminalElement, vector<char> processedNonTerminals) {
    if (std::find(processedNonTerminals.begin(), processedNonTerminals.end(), nonTerminalElement) != processedNonTerminals.end())
        return {};

    vector<char> currentTerminals = getTerminals();

    if (std::find(currentTerminals.begin(), currentTerminals.end(), nonTerminalElement) !=
            currentTerminals.end())
        return { nonTerminalElement };

    processedNonTerminals.push_back(nonTerminalElement);

    vector<transition> transitionsFromSpecifiedNonTerminal;
    vector<char> result;

    for (int i = 0; i < getTransitionsAmount(); i++) {
        if (this->transitions[i].getFrom() == nonTerminalElement)
            transitionsFromSpecifiedNonTerminal.push_back(this->transitions[i]);
    }

    // NonTerminal -> abra

    for (int i = 0; i < transitionsFromSpecifiedNonTerminal.size(); i++) {
        vector<char> subFirst = first(transitionsFromSpecifiedNonTerminal[i].getTo()[0], processedNonTerminals);
        for (char terminal: subFirst)
            result.push_back(terminal);
    }

    std::set<char> resultDistinctSet(result.begin(), result.end());
    std::vector<char> resultDistinct(resultDistinctSet.begin(), resultDistinctSet.end());

    return resultDistinct;
}

#pragma clang diagnostic pop
