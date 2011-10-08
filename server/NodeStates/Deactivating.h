/*
 * Deactivating.h
 *
 *  Created on: Oct 7, 2011
 *      Author: nathan
 */

#ifndef DEACTIVATING_H_
#define DEACTIVATING_H_

#include "NodeState.h"

namespace NodeStates {

class Deactivating: public NodeStates::NodeState {
public:
	Deactivating(Node & n);
	virtual ~Deactivating();
};

}

#endif /* DEACTIVATING_H_ */
