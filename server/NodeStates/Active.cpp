/*
 * Active.cpp
 *
 *  Created on: Oct 7, 2011
 *      Author: nathan
 */

#include "Active.h"

namespace NodeStates {

Active::Active(Node & n) :
	NodeState(n) {
	// TODO Auto-generated constructor stub

}

void Active::deactivate() {
	setState<Deactivating>();
}

Active::~Active() {
	// TODO Auto-generated destructor stub
}

}
