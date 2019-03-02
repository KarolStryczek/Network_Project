//
// Created by Karol on 2018-12-31.
//

#include "Storage/PackageQueue.hpp"

void PackageQueue::push(Package &&package) {
    _packageQueue.push_back(std::move(package));
}

Package PackageQueue::pop() {
    switch(_queueType){
        case QueueType::LIFO: {
            Package lastPackage = *(_packageQueue.rbegin());
            _packageQueue.pop_back();
            return lastPackage;
        }
        case QueueType::FIFO: {
            Package firstPackage = *(_packageQueue.begin());
            _packageQueue.pop_front();
            return firstPackage;
        }
    }
    return Package();
}