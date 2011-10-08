/*
 * TelnetListener.h
 *
 *  Created on: Oct 5, 2011
 *      Author: nathan
 */

#ifndef TELNETLISTENER_H_
#define TELNETLISTENER_H_

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include "TelnetInterpreter.h"
#include <vector>
#include "../Node.h"

class TelnetListener {
public:
	TelnetListener(boost::asio::io_service & ios, boost::asio::ip::tcp::endpoint e, Node & n);
	void listen();
	virtual ~TelnetListener();

private:
	void handleConnect(const boost::system::error_code & ec);

	boost::asio::io_service & mService;
	boost::asio::ip::tcp::acceptor mAcceptor;
	Node & mNode;
	boost::shared_ptr<boost::asio::ip::tcp::socket> mNewSocket;
};

#endif /* TELNETLISTENER_H_ */
