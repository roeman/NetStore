/*
 * StoreException.h
 *
 *  Created on: Oct 5, 2011
 *      Author: nathan
 */

#ifndef STOREEXCEPTION_H_
#define STOREEXCEPTION_H_

#include <exception>

namespace Stores {

class StoreException : public std::exception {
public:
	StoreException();
	virtual ~StoreException() throw();
};

class UndefinedStoreTypeException : public StoreException {
public:
	UndefinedStoreTypeException();
	virtual ~UndefinedStoreTypeException() throw();
};

}

#endif /* STOREEXCEPTION_H_ */
