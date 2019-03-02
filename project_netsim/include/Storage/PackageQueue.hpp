// 4a_2: Stryczek (297457), Świerczek (297464), Śliwińska(297462)
//
// Created by Karol on 2018-12-31.
//

#ifndef PROJECT_NETSIM_PACKAGEQUEUE_HPP
#define PROJECT_NETSIM_PACKAGEQUEUE_HPP

#include <deque>
#include "IPackageQueue.hpp"

/**
 * Class implemeting IPackageQueue interface. Allows to keep packages in container
 */
class PackageQueue: public IPackageQueue {
private:
    std::deque<Package> _packageQueue;
    QueueType _queueType;
public:
    explicit PackageQueue(QueueType queueType):  _packageQueue(), _queueType(queueType){};
    void push(Package&&) override;
    Package pop() override;
    QueueType getQueueType() const override { return _queueType; };

    constIterator begin() const override { return _packageQueue.cbegin(); };
    constIterator end() const override { return _packageQueue.end(); };
    constIterator cbegin() const override { return _packageQueue.cbegin(); };
    constIterator cend() const override { return _packageQueue.cend(); };
};


#endif //PROJECT_NETSIM_PACKAGEQUEUE_HPP
// 4a_2: Stryczek (297457), Świerczek (297464), Śliwińska(297462)