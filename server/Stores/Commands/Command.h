/*
 * Command.h
 *
 *  Created on: Oct 6, 2011
 *      Author: nathan
 */

#ifndef COMMAND_H_
#define COMMAND_H_

#include <vector>
#include "Expression.h"

namespace Stores {

namespace Commands {

class Command {
public:
	virtual Expression operator()(std::vector<Expression> args) = 0;
	virtual ~Command();
};

}

}

#endif /* COMMAND_H_ */
