#include "IDatabaseConnection.hpp"
#include <iostream>

IDatabaseConnection::IDatabaseConnection(std::string serverAddress) : mServerAddress{serverAddress}
{
}


void IDatabaseConnection::connect()
{
  std::cout << "Connecting to database server " << mServerAddress << "\n";
  //initialize real DB connection
  if (mOnConnect != nullptr)
  {
	  std::cout << "Callback was set";
  }
  else
  {
	  std::cout << "Callback was not set";
	  return;
  }
  //mOnConnect(1,2);
  onConnect();
}

void IDatabaseConnection::disconnect()
{
 std::cout << "Disconnecting from database\n";
 //close the real connection
}

void IDatabaseConnection::setOnConnect(Callback onConnect)
{
	mOnConnect = onConnect;
}