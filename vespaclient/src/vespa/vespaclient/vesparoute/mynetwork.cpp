// Copyright 2017 Yahoo Holdings. Licensed under the terms of the Apache 2.0 license. See LICENSE in the project root.

#include "mynetwork.h"
#include <vespa/messagebus/emptyreply.h>
#include <vespa/messagebus/sendproxy.h>
#include <vespa/messagebus/network/oosmanager.h>


class MyServiceAddress : public mbus::IServiceAddress {
private:
    std::string _address;

public:
    MyServiceAddress(const std::string &address) :
        _address(address) {
        // empty
    }

    const std::string &getAddress() {
        return _address;
    }
};

MyNetwork::MyNetwork(const mbus::RPCNetworkParams &params) :
    mbus::RPCNetwork(params),
    _nodes()
{
    // empty
}


bool
MyNetwork::allocServiceAddress(mbus::RoutingNode &recipient)
{
    recipient.setServiceAddress(mbus::IServiceAddress::UP(new MyServiceAddress(recipient.getRoute().getHop(0).toString())));
    return true;
}

void
MyNetwork::freeServiceAddress(mbus::RoutingNode &recipient)
{
    recipient.setServiceAddress(mbus::IServiceAddress::UP());
}

bool
MyNetwork::verifyOOS(const std::string &address)
{
    return getOOSManager().isOOS(address);
}

void
MyNetwork::send(const mbus::Message &msg, const std::vector<mbus::RoutingNode*> &nodes)
{
    (void)msg;
    _nodes.insert(_nodes.begin(), nodes.begin(), nodes.end());
}

void
MyNetwork::removeNodes(std::vector<mbus::RoutingNode*> &nodes)
{
    nodes.insert(nodes.begin(), _nodes.begin(), _nodes.end());
    _nodes.clear();
}
