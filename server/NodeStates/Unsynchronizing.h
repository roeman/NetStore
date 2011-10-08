/*
 * Unsynchronizing.h
 *
 *  Created on: Oct 7, 2011
 *      Author: nathan
 */

#ifndef UNSYNCHRONIZING_H_
#define UNSYNCHRONIZING_H_

#include "NodeState.h"

namespace NodeStates {

class Unsynchronizing: public NodeStates::NodeState {
public:
	Unsynchronizing(Node & n);
	virtual ~Unsynchronizing();
};

}

#endif /* UNSYNCHRONIZING_H_ */
