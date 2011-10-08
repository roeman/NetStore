/*
 * NodePeer.h
 *
 *  Created on: Oct 7, 2011
 *      Author: nathan
 */

#ifndef NODEPEER_H_
#define NODEPEER_H_

#include "NodeID.h"

class NodePeer {
public:
	NodePeer(const NodeID & id);
	NodeID & getID();
	const NodeID & getID() const;
	virtual ~NodePeer();
private:
	NodeID mID;
};

#endif /* NODEPEER_H_ */
