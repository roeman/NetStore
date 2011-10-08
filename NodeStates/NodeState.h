/*
 * NodeState.h
 *
 *  Created on: Oct 7, 2011
 *      Author: nathan
 */

#ifndef NODESTATE_H_
#define NODESTATE_H_

#include "../Node.h"

#include "NodeStateFwdDcl.h"
#include <boost/make_shared.hpp>
#include <boost/ref.hpp>

namespace NodeStates {

class NodeState {
public:
	virtual void startUp() {}
	virtual void shutDown() {}
	virtual void synchronize() {}
	virtual void unsynchronize() {}
	virtual void activate() {}
	virtual void deactivate() {}
	virtual ~NodeState();
protected:
	NodeState(Node & n);
	NodeState(const NodeState & n);
	template<class state> void setState();
	Node & mNode;
};

template<class state> void NodeState::setState() {
	mNode.mState = boost::make_shared<state>(boost::ref(mNode));
}

} // NodeStates

#include "NodeState.h"
#include "Uninstantiated.h"
#include "StartingUp.h"
#include "ShuttingDown.h"
#include "Isolated.h"
#include "Synchronizing.h"
#include "Unsynchronizing.h"
#include "Synchronized.h"
#include "Activating.h"
#include "Deactivating.h"
#include "Active.h"

#endif /* NODESTATE_H_ */
