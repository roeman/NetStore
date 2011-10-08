/*
 * Synchronizing.h
 *
 *  Created on: Oct 7, 2011
 *      Author: nathan
 */

#ifndef SYNCHRONIZING_H_
#define SYNCHRONIZING_H_

#include "NodeState.h"

namespace NodeStates {

class Synchronizing: public NodeStates::NodeState {
public:
	Synchronizing(Node & n);
	virtual ~Synchronizing();
};

}

#endif /* SYNCHRONIZING_H_ */
