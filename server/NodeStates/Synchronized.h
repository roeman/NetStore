/*
 * Synchronized.h
 *
 *  Created on: Oct 7, 2011
 *      Author: nathan
 */

#ifndef SYNCHRONIZED_H_
#define SYNCHRONIZED_H_

#include "NodeState.h"

namespace NodeStates {

class Synchronized: public NodeStates::NodeState {
public:
	Synchronized(Node & n);
	virtual ~Synchronized();
};

}

#endif /* SYNCHRONIZED_H_ */
