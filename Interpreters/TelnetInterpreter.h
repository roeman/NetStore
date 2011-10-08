/*
 * TelnetInterpreter.h
 *
 *  Created on: Oct 5, 2011
 *      Author: nathan
 */

#ifndef TELNETINTERPRETER_H_
#define TELNETINTERPRETER_H_

#include "Interpreter.h"
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>

namespace Interpreters {

class TelnetInterpreter: public Interpreters::Interpreter, public boost::enable_shared_from_this<TelnetInterpreter> {
public:
	TelnetInterpreter(Node & n, boost::shared_ptr<boost::asio::ip::tcp::socket> sock);
	virtual void start();
	virtual ~TelnetInterpreter();

protected:
	virtual void run();
	void help(std::ostream & os);
	void types(std::ostream & os);
	void list(std::ostream & os);
	void create(std::ostream & os, std::string store);
	void destroy(std::ostream & os, std::string store);
	void enter(std::ostream & os, std::string store);
	void exit(std::ostream & os);
	void quit(std::ostream & os);

	void handleReceive(const boost::system::error_code & ec, std::size_t bytes_transferred);
	void handleWrite(const boost::system::error_code & ec, std::size_t bytes_transferred);
	void handleQuit(const boost::system::error_code & ec, std::size_t bytes_transferred);
	boost::shared_ptr<boost::asio::ip::tcp::socket> mSocket;
	bool escape;
	boost::shared_ptr<TelnetInterpreter> mHeartBeat;
	boost::asio::streambuf mInBuffer;
};

}

#endif /* TELNETINTERPRETER_H_ */
