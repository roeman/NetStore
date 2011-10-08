/*
 * TelnetListener.cpp
 *
 *  Created on: Oct 5, 2011
 *      Author: nathan
 */

#include "TelnetListener.h"
#include <boost/make_shared.hpp>
#include <boost/bind.hpp>

TelnetListener::TelnetListener(boost::asio::io_service & ios, boost::asio::ip::tcp::endpoint e, Node & n) :
	mService(ios),
	mAcceptor(ios, e),
	mNode(n)
{
}

void TelnetListener::handleConnect(const boost::system::error_code & ec) {
	if(!ec) {
		boost::shared_ptr<Interpreters::TelnetInterpreter> ti =
				boost::make_shared<Interpreters::TelnetInterpreter>(boost::ref(mNode), mNewSocket);
		ti->start();
		listen();
	}
}

void TelnetListener::listen() {
	mNewSocket = boost::make_shared<boost::asio::ip::tcp::socket>(boost::ref(mService));
	mAcceptor.async_accept(*mNewSocket, boost::bind(&TelnetListener::handleConnect, this, boost::asio::placeholders::error));
	mAcceptor.listen();
}

TelnetListener::~TelnetListener() {
	mAcceptor.close();
}
