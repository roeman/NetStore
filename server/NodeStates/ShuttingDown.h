/*
 * ShuttingDown.h
 *
 *  Created on: Oct 7, 2011
 *      Author: nathan
 */

#ifndef SHUTTINGDOWN_H_
#define SHUTTINGDOWN_H_

#include "NodeState.h"

namespace NodeStates {

class ShuttingDown: public NodeStates::NodeState {
public:
	ShuttingDown(Node & n);
	virtual ~ShuttingDown();
};

}

#endif /* SHUTTINGDOWN_H_ */
