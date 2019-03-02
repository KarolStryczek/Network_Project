// 4a_2: Stryczek (297457), Świerczek (297464), Śliwińska(297462)
//
// Created by Karol on 2018-12-31.
//

#ifndef PROJECT_NETSIM_WORKER_HPP
#define PROJECT_NETSIM_WORKER_HPP

#include <utility>
#include <memory>
#include "PackageSender.hpp"
#include "IPackageReceiver.hpp"
#include "Storage/IPackageQueue.hpp"

/**
 * Class Worker implements such responsibilities as processing Package, collecting new Package, getters to class fields
 * and iterators to packageQueue container.
 */
class Worker: public PackageSender, public IPackageReceiver{
private:
    ElementID _workerID;
    int _processInterval;
    std::unique_ptr<IPackageQueue> _packageQueue;
    std::pair<Package, int> _processingBuffer;
public:
    /**
     * @param id: Worker's ID.
     * @param processInterval: Numbers of cycles it takes for worker to process a Package.
     * @param packageQueue: Unique Pointer to any class implementing IPackageQueue interface.
     */
    Worker(ElementID id, int processInterval,  std::unique_ptr<IPackageQueue> packageQueue):
        PackageSender(), _workerID(id), _processInterval(processInterval),
        _packageQueue(std::move(packageQueue)), _processingBuffer(){ _processingBuffer.second = 0; };

    // Methods defined in Worker.cpp
    void collectPackage(Package&&) override ;
    void process();

    // Getters.
    ReceiverType getReceiverType() const override { return ReceiverType::Worker; }
    ElementID getID() const override { return _workerID; }
    QueueType getQueueType() const { return _packageQueue->getQueueType(); }
    int getProcessInterval() const { return _processInterval; }
    const std::pair<Package, int>& getBuffer() const { return _processingBuffer; };

    //Delegating iterators to class field _packageQueue iterators.
    constIterator begin() const override { return _packageQueue->cbegin(); }
    constIterator end() const override { return _packageQueue->cend(); }
    constIterator cbegin() const override { return _packageQueue->cbegin(); }
    constIterator cend() const override { return _packageQueue->cend(); }
};


#endif //PROJECT_NETSIM_WORKER_HPP
// 4a_2: Stryczek (297457), Świerczek (297464), Śliwińska(297462)