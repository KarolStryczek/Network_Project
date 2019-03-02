// 4a_2: Stryczek (297457), Świerczek (297464), Śliwińska(297462)
//
// Created by Karol on 2018-12-31.
//

#ifndef PROJECT_NETSIM_IPACKAGEQUEUE_HPP
#define PROJECT_NETSIM_IPACKAGEQUEUE_HPP

#include "IPackageStockpile.hpp"

/**
 * Interface type for queues.
 * Allows to push and pop(from front or back, depends on queue type) and iterate through packages.
 */
enum class QueueType{
    FIFO, LIFO
};

class IPackageQueue: public IPackageStockpile {
public:
    virtual Package pop() = 0;
    virtual QueueType getQueueType() const = 0;
};


#endif //PROJECT_NETSIM_IPACKAGEQUEUE_HPP
// 4a_2: Stryczek (297457), Świerczek (297464), Śliwińska(297462)