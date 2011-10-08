/*
 * Store.h
 *
 *  Created on: Oct 5, 2011
 *      Author: nathan
 */

#ifndef STORE_H_
#define STORE_H_

#include <string>
#include "StoreException.h"
#include <map>

namespace Stores {

class Store {
public:
	enum store_type {
		STORE_VALUE,
		STORE_BUCKET,
		STORE_ARRAY,
		STORE_VECTOR,
		STORE_STACK,
		STORE_QUEUE,
		STORE_TABLE,
		STORE_GRAPH,
		STORE_BINARYTREE,
		STORE_BTREE
	};

	Store(const std::string & id);

	std::string getID() const;
	store_type getType() const;

	virtual void insert(const std::string & command) = 0;
	virtual void remove(const std::string & command) = 0;
	virtual std::string fetch(const std::string & command) = 0;

	virtual ~Store();

protected:
	std::string mID;
	store_type mType;
};

}

#endif /* STORE_H_ */
