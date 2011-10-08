/*
 * Uninstantiated.cpp
 *
 *  Created on: Oct 7, 2011
 *      Author: nathan
 */

#include "Uninstantiated.h"

namespace NodeStates {

Uninstantiated::Uninstantiated(Node & n) :
	NodeState(n) {
}

void Uninstantiated::startUp() {
	setState<StartingUp>();
}

Uninstantiated::~Uninstantiated() {
}

} // NodeStates
