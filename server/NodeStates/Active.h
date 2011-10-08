/*
 * Active.h
 *
 *  Created on: Oct 7, 2011
 *      Author: nathan
 */

#ifndef ACTIVE_H_
#define ACTIVE_H_

#include "NodeState.h"

namespace NodeStates {

class Active: public NodeStates::NodeState {
public:
	Active(Node & n);
	void deactivate();
	virtual ~Active();
};

}

#endif /* ACTIVE_H_ */
