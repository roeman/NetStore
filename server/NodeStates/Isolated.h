/*
 * Isolated.h
 *
 *  Created on: Oct 7, 2011
 *      Author: nathan
 */

#ifndef ISOLATED_H_
#define ISOLATED_H_

#include "NodeState.h"

namespace NodeStates {

class Isolated: public NodeStates::NodeState {
public:
	Isolated(Node & n);
	virtual ~Isolated();
};

}

#endif /* ISOLATED_H_ */
