/*
 * NodeException.h
 *
 *  Created on: Oct 5, 2011
 *      Author: nathan
 */

#ifndef NODEEXCEPTION_H_
#define NODEEXCEPTION_H_

#include <exception>

class NodeException : public std::exception {
public:
	NodeException();
	virtual ~NodeException() throw();
};

class UniqueIDNodeException : public NodeException {

};

#endif /* NODEEXCEPTIONS_H_ */
