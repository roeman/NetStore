/*
 * StartingUp.h
 *
 *  Created on: Oct 7, 2011
 *      Author: nathan
 */

#ifndef STARTINGUP_H_
#define STARTINGUP_H_

#include "NodeState.h"

namespace NodeStates {

class StartingUp: public NodeStates::NodeState {
public:
	StartingUp(Node & n);
	virtual ~StartingUp();
};

}

#endif /* STARTINGUP_H_ */
