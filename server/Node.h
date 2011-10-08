/*
 * Node.h
 *
 *  Created on: Oct 5, 2011
 *      Author: nathan
 */

#ifndef NODE_H_
#define NODE_H_

#include "NodeStates/NodeStateFwdDcl.h"
#include <boost/shared_ptr.hpp>

class Node {
public:
	Node();
	void loadDataFromStorage();
	void saveDataToStorage();
	virtual ~Node();

	friend class NodeStates::Activating;
	friend class NodeStates::Active;
	friend class NodeStates::Deactivating;
	friend class NodeStates::Isolated;
	friend class NodeStates::NodeState;
	friend class NodeStates::ShuttingDown;
	friend class NodeStates::StartingUp;
	friend class NodeStates::Synchronized;
	friend class NodeStates::Synchronizing;
	friend class NodeStates::Uninstantiated;
	friend class NodeStates::Unsynchronizing;

private:
	boost::shared_ptr<NodeStates::NodeState> mState;
};

#include "NodeStates/NodeState.h"

#endif /* NODE_H_ */
