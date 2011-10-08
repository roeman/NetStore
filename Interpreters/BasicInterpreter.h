/*
 * BasicInterpreter.h
 *
 *  Created on: Oct 5, 2011
 *      Author: nathan
 */

#ifndef BASICINTERPRETER_H_
#define BASICINTERPRETER_H_

#include <boost/shared_ptr.hpp>
#include "../Stores/Store.h"
#include <string>
#include <boost/foreach.hpp>
#include <boost/tokenizer.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/shared_ptr.hpp>
#include <ostream>
#include "Interpreter.h"

namespace Interpreters {

class BasicInterpreter : public Interpreter {
public:
	BasicInterpreter(Node & n);

	virtual ~BasicInterpreter();

protected:
	void run();
	bool processLine(std::string line) throw (std::exception);
	void help();
	void types();
	void list();
	void create(std::string store);
	void destroy(std::string store);
	void enter(std::string store);
	void exit();
	void quit();

	std::ostream & mOutput;
};

} // namespace Interpreters

#endif /* INTERPRETER_H_ */
