//
// Created by mikhail.syvachenko on 28.10.2023.
//

#include "transition.h"

#include <utility>

transition::transition(char from, vector<char> to) {
    this->from = from;
    vector<char> optimizedTransitions = removeEpsilons(to);
    this->to = std::move(optimizedTransitions);
}

transition::~transition() = default;

char transition::getFrom() const {
    return from;
}

vector<char> transition::getTo() const {
    return to;
}

vector<char> transition::removeEpsilons(vector<char> to) {
    if (to.size() == 1)
        return to;

    vector<char> toWithoutEpsilons;

    for (auto element : to) {
        if (element != getEpsilon())
            toWithoutEpsilons.push_back(element);
    }

    return toWithoutEpsilons;
}

char transition::getEpsilon() {
    return 'e';
}