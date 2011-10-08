/*
 * BasicInterpreter.cpp
 *
 *  Created on: Oct 5, 2011
 *      Author: nathan
 */

#include "BasicInterpreter.h"
#include <iostream>

namespace Interpreters {

BasicInterpreter::BasicInterpreter(Node & n) :
	Interpreter(n),
	mOutput(std::cout)
{
}

void BasicInterpreter::run() {
	bool escape = false;
	while(!escape) {
		std::string command_line;
		if(!mCurrentStore) {
			mOutput << "NetStore>";
		} else {
			mOutput << mCurrentStore->getID() << ">";
		}
		std::getline(std::cin, command_line);
		try {
			escape = processLine(command_line);
		} catch(std::exception e) {
			mOutput << "Exception: " << e.what() << std::endl;
		}
	}
}

bool BasicInterpreter::processLine(std::string line) throw (std::exception) {
	typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
	boost::char_separator<char> sep(" ");
	tokenizer tokens(line, sep);
	std::string command;
	BOOST_AUTO(token_iter, tokens.begin());
	if(token_iter != tokens.end()) {
		command = *token_iter;
	}

	if(command == "help" || command == "?") {
		help();
	} else if(command == "types") {
		types();
	} else if(command == "list") {
		list();
	} else if(command == "create") {
		std::string args = line.substr(std::min(command.length()+1, line.length()));
		create(args);
	} else if(command == "destroy") {
		std::string args = line.substr(std::min(command.length()+1, line.length()));
		destroy(args);
	} else if(command == "enter") {
		std::string args = line.substr(std::min(command.length()+1, line.length()));
		enter(args);
	} else if(command == "exit") {
		exit();
	} else if(command == "insert") {
		std::string args = line.substr(std::min(command.length()+1, line.length()));
		if(mCurrentStore) {
			mCurrentStore->insert(args);
			mOutput << "Inserted :" << std::endl << mCurrentStore->fetch(args) << std::endl;
		} else {
			mOutput << "You must enter a store before manipulating the values within" << std::endl;
		}
	} else if(command == "remove") {
		std::string args = line.substr(std::min(command.length()+1, line.length()));
		if(mCurrentStore) {
			mOutput << "Removing :" << std::endl << mCurrentStore->fetch(args) << std::endl;
			mCurrentStore->remove(args);
		} else {
			mOutput << "You must enter a store before manipulating the values within" << std::endl;
		}
	} else if(command == "fetch") {
		std::string args = line.substr(std::min(command.length()+1, line.length()));
		if(mCurrentStore) {
			mOutput << "Fetched :" << std::endl << mCurrentStore->fetch(args) << std::endl;
		} else {
			mOutput << "You must enter a store before manipulating the values within" << std::endl;
		}
	} else if(command == "quit") {
		quit();
		return true;
	} else {
		mOutput << "Unknown command" << std::endl;
	}
	return false;
}

void BasicInterpreter::help() {
	mOutput << "Available commands include:" << std::endl;
	mOutput << "\thelp - displays this help" << std::endl;
	mOutput << "\ttypes - displays the available types of store" << std::endl;
	mOutput << "\tcreate id type - creates a store with the given id and type" << std::endl;
	mOutput << "\tlist - lists all stores" << std::endl;
	mOutput << "\tdestroy id - destroys a store" << std::endl;
	mOutput << "\tenter id - enters the context of a store" << std::endl;
	mOutput << "\tquit - exits this program" << std::endl;
	mOutput << std::endl <<"\tCommands for within a store" << std::endl;
	mOutput << "\texit - exits the current context" << std::endl;
	mOutput << "\tinsert - inserts a given value into the current store" << std::endl;
	mOutput << "\tremove - removes a given value from the current store" << std::endl;
	mOutput << "\tfetch - fetches a value from the current store" << std::endl;
	mOutput << "\tsettings - display current metadata settings for this store" << std::endl;
	mOutput << "\tset - change the value of a metadata setting" << std::endl;
	mOutput << "\t(the arguments to insert, delete, and fetch vary based on what type the current store is)" << std::endl;
}

void BasicInterpreter::types() {
	mOutput << "Available store types:" << std::endl;
	mOutput << "\tVALUE" << std::endl;
}

void BasicInterpreter::list() {
	mOutput << "Current stores:" << std::endl;
	BOOST_FOREACH(std::string str, mNode.listStores()) {
		mOutput << str << std::endl;
	}
	mOutput << std::endl;
}

void BasicInterpreter::create(std::string args) {
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
				mOutput << "Error: invalid type supplied" << std::endl;
			}
		} else {
			mOutput << "Error: please give a type for this store" << std::endl;
		}
	} else {
		mOutput << "Error: please give an ID for this store" << std::endl;
	}
}

void BasicInterpreter::destroy(std::string store) {
	if(store != "") {
		if(mNode.destroyStore(store)) {
			mOutput << "Success: destroyed store: " << store << std::endl;
		} else {
			mOutput << "Store " << store << " does not exist" << std::endl;
		}
	} else {
		mOutput << "Error: please provide an ID identifying the store to be destroyed" << std::endl;
	}
}

void BasicInterpreter::enter(std::string store) {
	mCurrentStore = mNode.retrieveStore(store);
	if(mCurrentStore) {
		mOutput << "Now working with store " << store << std::endl;
	} else {
		mOutput << "Error: store " << store << " does not exist" << std::endl;
	}
}

void BasicInterpreter::exit() {
	mOutput << "Done working with store " << mCurrentStore->getID() << std::endl;
	mCurrentStore.reset();
}

void BasicInterpreter::quit() {
	mOutput << "Goodbye" << std::endl;
}

BasicInterpreter::~BasicInterpreter() {
}

} // namespace Interpreters
