/*
 * Expression.h
 *
 *  Created on: Oct 6, 2011
 *      Author: nathan
 */

#ifndef EXPRESSION_H_
#define EXPRESSION_H_

#include <string>

namespace Stores {

namespace Commands {

class Expression {
public:
	Expression();
	static Expression parseString(std::string str);
	virtual ~Expression();
};

}

}

#endif /* EXPRESSION_H_ */
