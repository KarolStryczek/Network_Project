// 4a_2: Stryczek (297457), Świerczek (297464), Śliwińska(297462)
//
// Created by gosia on 2019-01-06.
//

#ifndef PROJEKT_NODECOLLECTION_HPP
#define PROJEKT_NODECOLLECTION_HPP

#include <list>
#include <optional>
#include "DataTypes.hpp"

template<typename Node>
class NodeCollection {
private:
    std::list<Node> _nodes;
public:
    using iterator = typename std::list<Node>::iterator;
    using const_iterator = typename std::list<Node>::const_iterator;

    explicit NodeCollection<Node>(): _nodes() {};
    iterator findByID(ElementID nodeID);
    void removeByID(ElementID nodeID);
    void add(Node node);
    void push_back(Node node) { _nodes.push_back(std::move(node)); };
    iterator begin() { return _nodes.begin(); }; //nwm czy to typename
    iterator end() { return _nodes.end(); };
    const_iterator cbegin() const { return _nodes.cbegin(); };
    const_iterator cend() const { return _nodes.cend(); };
    const std::list<Node>& getNodes() const { return _nodes; };
};

#endif //PROJEKT_NODECOLLECTION_HPP
// 4a_2: Stryczek (297457), Świerczek (297464), Śliwińska(297462)