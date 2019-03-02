//
// Created by Karol on 2018-12-31.
//

#include "Nodes/Worker.hpp"


/**
 * Collects Package given as reference to value (rval reference).
 * @param package: Rvalue reference to Package.
 */
void Worker::collectPackage(Package &&package) {
    _packageQueue->push(std::move(package));
}


/**
 * Execute Package processing.
 * Process current package, or take new one. If that was last turn of processing, pass package to toSendBuffer.
 */
void Worker::process() {
    // If packageQueue is not empty
    if(_processingBuffer.second == 0) {
        // If there is no Package to process in buffer, take next one.
        if(_packageQueue->cend() - _packageQueue->cbegin() != 0) {
            _processingBuffer.first = _packageQueue->pop();
            _processingBuffer.second = _processInterval - 1;
        }
    }
    // If there is Package in buffer, process it.
    else if(_processingBuffer.second > 0) {
        _processingBuffer.second--;
    }
    // If Package processing has been finished, give it to toSendBuffer.
    if(_processingBuffer.second == 0) {
        _toSendBuffer.first = std::move(_processingBuffer.first);
        _toSendBuffer.second = true;
    }
}