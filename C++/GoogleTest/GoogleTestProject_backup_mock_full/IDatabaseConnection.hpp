#pragma once

#include <string>
#include <vector>

#include "Employee.hpp"
#include <functional>

//interface because we might subclass it
//example: IOracleDatabaseConnectionManager, ISQLDatabaseConnectionManager
class IDatabaseConnection
{
	
private:
	virtual void onConnect() {};

public:
  IDatabaseConnection(std::string serverAddress);
  using Callback = std::function<void(int, int)>;

  virtual float getSalary(int id) const = 0; // SELECT * FROM employees WHERE id=...
  virtual void updateSalary(int id, float newSalary) = 0;

  virtual std::vector<Employee> getSalariesRange(float low) const = 0; //just greater than low
  virtual std::vector<Employee> getSalariesRange(float low, float high) const = 0;

  virtual void connect();
  virtual void disconnect();

  void setOnConnect(Callback onConnect);

protected:
  std::string mServerAddress;
  Callback mOnConnect;
};
