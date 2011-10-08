/*
 * ValueStore.h
 *
 *  Created on: Oct 5, 2011
 *      Author: nathan
 */

#ifndef VALUESTORE_H_
#define VALUESTORE_H_

#include "Store.h"

namespace Stores {

class ValueStore : public Stores::Store {
public:
	ValueStore(const std::string & id);
	void setValue(std::string val);
	std::string getValue() const;

	virtual void insert(const std::string & command);
	virtual void remove(const std::string & command);
	virtual std::string fetch(const std::string & command);

	virtual ~ValueStore();
private:
	std::string mValue;
};

}

#endif /* VALUESTORE_H_ */
