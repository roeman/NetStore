/*
 * KeyValuePair.h
 *
 *  Created on: Oct 7, 2011
 *      Author: nathan
 */

#ifndef KEYVALUEPAIR_H_
#define KEYVALUEPAIR_H_

#include <utility>
#include "Key/Key.h"
#include "Value/Value.h"

class KeyValuePair : private std::pair<Key, Value> {
public:
	KeyValuePair(Key, Value);
	virtual ~KeyValuePair();
};

#endif /* KEYVALUEPAIR_H_ */
