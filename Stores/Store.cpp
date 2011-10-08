/*
 * Store.cpp
 *
 *  Created on: Oct 5, 2011
 *      Author: nathan
 */

#include "Store.h"

namespace Stores {

Store::Store(const std::string & id)
	: mID(id)
{

}

std::string Store::getID() const {
	return mID;
}

Store::store_type Store::getType() const {
	return mType;
}

Store::~Store() {

}

}
