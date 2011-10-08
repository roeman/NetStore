/*
 * main.cpp
 *
 *  Created on: Oct 5, 2011
 *      Author: nathan
 */

#include <iostream>
#include "Node.h"
#include <exception>
#include <boost/foreach.hpp>
#include <boost/tokenizer.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>

int main(int argc, char ** argv)
{
	Node me;

	boost::asio::io_service ios;

	ios.run();

	return 0;
}

