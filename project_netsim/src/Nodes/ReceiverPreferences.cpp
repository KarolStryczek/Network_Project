//
// Created by Karol on 2018-12-31.
//

#include "Nodes/ReceiverPreferences.hpp"
#include <random>

/**
 * Adds to preferences or reassigns receiver with pointer given.
 * @param receiver: Pointer to any among ReceiverType object.
 * @param priority: Value of priority, the higher the more preferred the receiver is.
 * @return: True if receiver was added. False if receiver was reassigned.
 */
bool ReceiverPreferences::addReceiver(std::shared_ptr<IPackageReceiver> receiver, double priority) {
    return (_preferences.insert_or_assign(receiver, priority)).second;
}


/**
 * Removes from preferences receiver with shared pointer given.
 * @param receiver: Pointer to any among ReceiverType object.
 * @return: True if receiver was removed. False if receiver was not found.
 */
bool ReceiverPreferences::removeReceiver(std::shared_ptr<IPackageReceiver> receiver) {
    auto iter = _preferences.find(receiver);
    if( iter == _preferences.end()){
        return false;
    }
    else{
        _preferences.erase(receiver);
        return true;
    }
}


/**
 * Chooses and returns pointer to receiver. Choice is implicitly based on randomly generated number.
 * Can be changed by passing function to ReceiverPreferences constructor.
 * @return: Pointer to chosen receiver.
 */
std::shared_ptr<IPackageReceiver> ReceiverPreferences::chooseReceiver() const {
    if(_preferences.cbegin()==_preferences.cend()){
        throw std::domain_error("There is no receiver associated with this object");
    }
    const double chosenDouble = _choosingFunction();
    if(chosenDouble > 1 || chosenDouble < 0) {
        throw std::domain_error("Choosing Function did not return value between 0 and 1.");
    }
    double prioritiesSum = 0;
    // Sum priorities
    for(const auto& receiver: _preferences) {
        prioritiesSum += receiver.second;
    }
    double newSum = 0;
    // Sum priorities, cast into [0, 1] interval and choose adequate receiver from distribute function.
    for(const auto& receiver: _preferences) {
        newSum += receiver.second;
        if(newSum/prioritiesSum >= chosenDouble) {
            return receiver.first;
        }
    }
    // This return is unreachable, but prevents warnings.
    return nullptr;
}