// 4a_2: Stryczek (297457), Świerczek (297464), Śliwińska(297462)
//
// Created by Karol on 2018-12-31.
//

#ifndef PROJECT_NETSIM_RECEIVERPREFERENCES_HPP
#define PROJECT_NETSIM_RECEIVERPREFERENCES_HPP

#include <map>
#include <functional>
#include <cstdlib>
#include <memory>
#include "IPackageReceiver.hpp"

// Used in order to simplify code.
using preferencesT = std::map<std::shared_ptr<IPackageReceiver>, double>;
using preferencesConstIterator = preferencesT::const_iterator;
using preferencesIterator = preferencesT::iterator;

/**
 * This class manages adding, removing and choosing receivers to which Package should be sent.
 */
class ReceiverPreferences {
private:
    preferencesT _preferences;
    std::function<double()> _choosingFunction;
public:
    /**
     * @param choosingFunction: Function which executes choosing receivers. Allows to make choice deterministic.
     *                          Returned value should be between 0 and 1 to avoid exceptions being thrown.
     */
    explicit ReceiverPreferences(std::function<double()> choosingFunction):
        _preferences(), _choosingFunction(std::move(choosingFunction)) {};
    /**
     * Default constructor initializes choosingFunction with random [0, 1] double generator.
     */
    ReceiverPreferences(): ReceiverPreferences([](){ return rand()/RAND_MAX; }) {};

    // Defined in .cpp
    std::shared_ptr<IPackageReceiver> chooseReceiver() const ;
    bool addReceiver(std::shared_ptr<IPackageReceiver>, double = 1);
    bool removeReceiver(std::shared_ptr<IPackageReceiver>);

    // Getters
    const preferencesT& getPreferences() const { return _preferences; };

    // Non-const iterators
    preferencesIterator begin() { return _preferences.begin(); };
    preferencesIterator end() { return _preferences.end(); };
    // Const iterators
    preferencesConstIterator begin() const { return _preferences.cbegin(); };
    preferencesConstIterator end() const { return _preferences.cend(); };
    preferencesConstIterator cbegin() const { return _preferences.cbegin(); };
    preferencesConstIterator cend() const { return _preferences.cend(); };
};

#endif //PROJECT_NETSIM_RECEIVERPREFERENCES_HPP
// 4a_2: Stryczek (297457), Świerczek (297464), Śliwińska(297462)