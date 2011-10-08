/*
 * NodeState.cpp
 *
 *  Created on: Oct 7, 2011
 *      Author: nathan
 */

#include "NodeState.h"

namespace NodeStates {

NodeState::NodeState(Node & n) :
	mNode(n) {
}

NodeState::NodeState(const NodeState & n) :
	mNode(n.mNode) {

}

NodeState::~NodeState() {
}

} // NodeStates
