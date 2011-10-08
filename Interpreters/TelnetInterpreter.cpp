/*
 * TelnetInterpreter.cpp
 *
 *  Created on: Oct 5, 2011
 *      Author: nathan
 */

#include "TelnetInterpreter.h"

#include <boost/bind.hpp>
#include <iostream>
#include <boost/typeof/typeof.hpp>
#include <boost/tokenizer.hpp>
#include <boost/foreach.hpp>
#include <string>

namespace Interpreters {

TelnetInterpreter::TelnetInterpreter(Node & n, boost::shared_ptr<boost::asio::ip::tcp::socket> sock) :
		Interpreter(n),
		mSocket(sock),
		escape(false)
{
	std::cout << "New connection to " << mSocket->remote_endpoint() << " formed." << std::endl;
}

void TelnetInterpreter::start() {
	mHeartBeat = shared_from_this();
	boost::asio::streambuf buf;
	std::ostream os(&buf);
	os << "Welcome to NetStore" << std::endl;
	os << "(c) 2011, Nathan Roe" << std::endl << std::endl;
	boost::asio::async_write(*mSocket, buf,
			boost::bind(&TelnetInterpreter::handleWrite, this,
					boost::asio::placeholders::error,
					boost::asio::placeholders::bytes_transferred));
	run();
}

void TelnetInterpreter::run() {
	if(!escape) {
		boost::asio::streambuf buf;
		std::ostream os(&buf);
		if(mCurrentStore) {
			os << mCurrentStore->getID() << ">";
		} else {
			os << "NetStore>";
		}
		boost::asio::async_write(*mSocket, buf,
				boost::bind(&TelnetInterpreter::handleWrite, this,
						boost::asio::placeholders::error,
						boost::asio::placeholders::bytes_transferred));

		mSocket->async_receive(mInBuffer.prepare(1024), boost::bind(&TelnetInterpreter::handleReceive, this,
																boost::asio::placeholders::error,
																boost::asio::placeholders::bytes_transferred));
	} else {
		boost::asio::async_write(
				*mSocket,
				boost::asio::buffer("Goodbye!\n", 11),
				boost::bind(&TelnetInterpreter::handleQuit, this,
						boost::asio::placeholders::error,
						boost::asio::placeholders::bytes_transferred));
	}
}

void TelnetInterpreter::help(std::ostream & os) {
	os << "Available commands include:" << std::endl;
	os << "\thelp - displays this help" << std::endl;
	os << "\ttypes - displays the available types of store" << std::endl;
	os << "\tcreate id type - creates a store with the given id and type" << std::endl;
	os << "\tlist - lists all stores" << std::endl;
	os << "\tdestroy id - destroys a store" << std::endl;
	os << "\tenter id - enters the context of a store" << std::endl;
	os << "\tquit - exits this program" << std::endl;
	os << std::endl <<"\tCommands for within a store" << std::endl;
	os << "\texit - exits the current context" << std::endl;
	os << "\tinsert - inserts a given value into the current store" << std::endl;
	os << "\tremove - removes a given value from the current store" << std::endl;
	os << "\tfetch - fetches a value from the current store" << std::endl;
	os << "\tsettings - display current metadata settings for this store" << std::endl;
	os << "\tset - change the value of a metadata setting" << std::endl;
	os << "\t(the arguments to insert, delete, and fetch vary based on what type the current store is)" << std::endl;
}

void TelnetInterpreter::types(std::ostream & os) {
	os << "Available store types:" << std::endl;
	os << "\tVALUE" << std::endl;
}

void TelnetInterpreter::list(std::ostream & os) {
	os << "Current stores:" << std::endl;
	BOOST_FOREACH(std::string str, mNode.listStores()) {
		os << str << std::endl;
	}
	os << std::endl;
}

void TelnetInterpreter::create(std::ostream & os, std::string args) {
	std::cout << "Arguments to create are : " << args << std::endl;
	typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
	boost::char_separator<char> sep(" ");
	tokenizer tokens(args, sep);

	BOOST_AUTO(token_iter, tokens.begin());

	std::string new_store_id, new_store_type;
	if(token_iter != tokens.end()) {
		new_store_id = *token_iter;
		token_iter++;
		if(token_iter != tokens.end()) {
			new_store_type = *token_iter;
			if(new_store_type == "VALUE") {
				mNode.createStore(new_store_id, Stores::Store::STORE_VALUE);
			} else {
				os << "Error: invalid type supplied" << std::endl;
			}
		} else {
			os << "Error: please give a type for this store" << std::endl;
		}
	} else {
		os << "Error: please give an ID for this store" << std::endl;
	}
}

void TelnetInterpreter::destroy(std::ostream & os, std::string store) {
	if(store != "") {
		if(mNode.destroyStore(store)) {
			os << "Success: destroyed store: " << store << std::endl;
		} else {
			os << "Store " << store << " does not exist" << std::endl;
		}
	} else {
		os << "Error: please provide an ID identifying the store to be destroyed" << std::endl;
	}
}

void TelnetInterpreter::enter(std::ostream & os, std::string store) {
	mCurrentStore = mNode.retrieveStore(store);
	if(mCurrentStore) {
		os << "Now working with store " << store << std::endl;
	} else {
		os << "Error: store " << store << " does not exist" << std::endl;
	}
}

void TelnetInterpreter::exit(std::ostream & os) {
	os << "Done working with store " << mCurrentStore->getID() << std::endl;
	mCurrentStore.reset();
}

void TelnetInterpreter::quit(std::ostream & os) {
	escape = true;
}

void TelnetInterpreter::handleReceive(const boost::system::error_code & ec, std::size_t bytes_transferred) {
	if(!ec) {
		boost::asio::streambuf buf;
		std::ostream os(&buf);

		mInBuffer.commit(bytes_transferred);
		std::istream is(&mInBuffer);
		char * line_tmp = new char[bytes_transferred];
		is.read(line_tmp, bytes_transferred);
		std::string line(line_tmp);
		delete[] line_tmp;

		line.erase(line.length()-2,2);

		std::cout << "Received:" << std::endl << "[" << line << "]" << std::endl;

		typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
		boost::char_separator<char> sep(" \n\r;");
		tokenizer tokens(line, sep);
		std::string command;
		BOOST_AUTO(token_iter, tokens.begin());
		if(token_iter != tokens.end()) {
			command = *token_iter;
		}

		if(command == "help" || command == "?") {
			help(os);
		} else if(command == "types") {
			types(os);
		} else if(command == "list") {
			list(os);
		} else if(command == "create") {
			std::string args = *(++token_iter);
			args += ' ';
			args += *(++token_iter);
			create(os, args);
		} else if(command == "destroy") {
			std::string args = *(++token_iter);
			destroy(os, args);
		} else if(command == "enter") {
			std::string args = *(++token_iter);
			enter(os, args);
		} else if(command == "exit") {
			exit(os);
		} else if(command == "insert") {
			std::string args = line.substr(std::min(command.length()+1, line.length()));
			if(mCurrentStore) {
				mCurrentStore->insert(args);
				os << "Inserted :" << std::endl << mCurrentStore->fetch(args) << std::endl;
			} else {
				os << "You must enter a store before manipulating the values within" << std::endl;
			}
		} else if(command == "remove") {
			std::string args = line.substr(std::min(command.length()+1, line.length()));
			if(mCurrentStore) {
				os << "Removing :" << std::endl << mCurrentStore->fetch(args) << std::endl;
				mCurrentStore->remove(args);
			} else {
				os << "You must enter a store before manipulating the values within" << std::endl;
			}
		} else if(command == "fetch") {
			std::string args = line.substr(std::min(command.length()+1, line.length()));
			if(mCurrentStore) {
				os << "Fetched :" << std::endl << mCurrentStore->fetch(args) << std::endl;
			} else {
				os << "You must enter a store before manipulating the values within" << std::endl;
			}
		} else if(command == "quit") {
			quit(os);
		} else {
			os << "Unknown command" << std::endl;
		}

		boost::asio::async_write(*mSocket, buf, boost::bind(&TelnetInterpreter::handleWrite, this,
				boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
	} else {
		escape = true;
	}
	run();
}

void TelnetInterpreter::handleWrite(const boost::system::error_code & ec, std::size_t bytes_transferred) {
	if(!ec) {
	} else {
		escape = true;
	}
}

void TelnetInterpreter::handleQuit(const boost::system::error_code & ec, std::size_t bytes_transferred) {
	if(mSocket->is_open()) {
		mSocket->close();
	}
	mHeartBeat.reset(); // Goodbye cruel world!
}

TelnetInterpreter::~TelnetInterpreter() {
	std::cout << "TelnetInterpreter destroyed, connection terminated." << std::endl;
	if(mSocket->is_open()) {
		mSocket->close();
	}
}

}
