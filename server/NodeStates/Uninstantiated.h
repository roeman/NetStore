/*
 * Uninstantiated.h
 *
 *  Created on: Oct 7, 2011
 *      Author: nathan
 */

#ifndef UNINSTANTIATED_H_
#define UNINSTANTIATED_H_

#include "NodeState.h"

namespace NodeStates {

class Uninstantiated : public NodeState {
public:
	Uninstantiated(Node & n);
	void startUp();
	virtual ~Uninstantiated();
};

} // NodeStates

#endif /* UNINSTANTIATED_H_ */
