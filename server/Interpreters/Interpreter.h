/*
 * Interpreter.h
 *
 *  Created on: Oct 5, 2011
 *      Author: nathan
 */

#ifndef INTERPRETER_H_
#define INTERPRETER_H_

#include "../Node.h"
#include <boost/shared_ptr.hpp>

namespace Interpreters {

class Interpreter {
public:
	Interpreter(Node & n);
	virtual void start() { run(); }
	virtual ~Interpreter();

protected:
	virtual void run() = 0;
	Node & mNode;
	boost::shared_ptr<Stores::Store> mCurrentStore;
};

}

#endif /* INTERPRETER_H_ */
