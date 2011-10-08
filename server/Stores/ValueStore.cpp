/*
 * ValueStore.cpp
 *
 *  Created on: Oct 5, 2011
 *      Author: nathan
 */

#include "ValueStore.h"

namespace Stores {

ValueStore::ValueStore(const std::string & id) :
		Store(id),
		mValue()
{
	// TODO Auto-generated constructor stub

}

void ValueStore::setValue(std::string val) {
	mValue = val;
}

void ValueStore::insert(const std::string & command) {
	mValue = command;
}

void ValueStore::remove(const std::string & command) {
	mValue = "";
}

std::string ValueStore::fetch(const std::string & command) {
	return mValue;
}

ValueStore::~ValueStore() {
	// TODO Auto-generated destructor stub
}

}
