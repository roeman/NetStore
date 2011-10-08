/*
 * Activating.h
 *
 *  Created on: Oct 7, 2011
 *      Author: nathan
 */

#ifndef ACTIVATING_H_
#define ACTIVATING_H_

#include "NodeState.h"

namespace NodeStates {

class Activating: public NodeStates::NodeState {
public:
	Activating(Node & n);
	virtual ~Activating();
};

}

#endif /* ACTIVATING_H_ */
