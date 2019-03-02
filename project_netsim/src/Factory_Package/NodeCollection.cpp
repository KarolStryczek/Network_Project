// 4a_2: Stryczek (297457), Świerczek (297464), Śliwińska(297462)
//
// Created by gosia on 2019-01-12.
//
#include "Factory_Package/NodeCollection.hpp"
#include <list>
#include <iterator>
#include<algorithm>
#include <Nodes/Ramp.hpp>
#include <Nodes/Worker.hpp>
#include <Nodes/Storehouse.hpp>
#include "DataTypes.hpp"
#include "Nodes/IPackageReceiver.hpp"
#include "Nodes/ReceiverPreferences.hpp"

template<typename Node>
using iterator = typename std::list<Node>::iterator;
template<typename Node>
using const_iterator = typename std::list<Node>::const_iterator;

template<typename Node>
iterator<Node> NodeCollection<Node>::findByID(ElementID nodeID) {
    auto it = std::find_if(_nodes.begin(), _nodes.end(), [&nodeID](const auto& elem) { return (elem.getID() == nodeID); });
    return it;
}

template<typename Node>
void NodeCollection<Node>::removeByID(ElementID nodeID) {
    auto it = NodeCollection::findByID(nodeID);
    if (it != _nodes.end()) {
        _nodes.erase(it);
    }
}

template<typename Node>
void NodeCollection<Node>::add(Node node) {
    _nodes.push_back(std::move(node));
}

template class NodeCollection<Ramp>;
template class NodeCollection<Worker>;
template class NodeCollection<Storehouse>;


// 4a_2: Stryczek (297457), Świerczek (297464), Śliwińska(297462)