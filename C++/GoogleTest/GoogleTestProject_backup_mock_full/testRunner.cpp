#include <iostream>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <map>

#include "IDatabaseConnection.hpp"
#include "Employee.hpp"
#include "EmployeeManager.hpp"

#include <vector>
#include <stdexcept>

void realCallback()
{
    std::cout << "Real callback invoked\n";
}

std::vector<int> generateNumbers(int n, int limit)
{
    std::vector<int> result;
    if (limit <= 0)
    {
        throw std::runtime_error("Argument must be >= 0");
    }
    for (int i = 0; i < n; i++)
    {
        result.push_back(i % limit);
    }
    return result;
}

class MockDatabaseConnection : public IDatabaseConnection
{
public:
    MockDatabaseConnection(std::string serverAddress);

    //MOCK_METHODn n=0,10
    MOCK_METHOD0(connect, void());
    MOCK_METHOD0(disconnect, void());
    MOCK_METHOD0(disconnect2, void());
    MOCK_METHOD0(onConnect, void());

    MOCK_CONST_METHOD1(getSalary, float(int));
    MOCK_METHOD2(updateSalary, void(int, float) );

    MOCK_CONST_METHOD1(getSalariesRange, std::vector<Employee>(float));
    MOCK_CONST_METHOD2(getSalariesRange, std::vector<Employee>(float, float));

};

MockDatabaseConnection::MockDatabaseConnection(std::string serverAddress) : IDatabaseConnection(serverAddress)
{
}


TEST(TestEmployeeManager, TestConnection)
{
    MockDatabaseConnection dbConnection("dummyConnection");
    EXPECT_CALL(dbConnection, connect());
    EXPECT_CALL(dbConnection, disconnect());

    EmployeeManager employeeManager(&dbConnection);
}


TEST(TestEmployeeManager, TestUpdateSalary)
{
    MockDatabaseConnection dbConnection("dummyConnection");
    EXPECT_CALL(dbConnection, connect());
    EXPECT_CALL(dbConnection, disconnect());
    EXPECT_CALL(dbConnection, updateSalary(testing::_, testing::_)).Times(1);   

    EmployeeManager employeeManager(&dbConnection);

    employeeManager.setSalary(50, 6000);
}


TEST(TestEmployeeManager, TestGetSalary)
{
    const int employeeId = 50;
    const float salary = 6100.0;
    MockDatabaseConnection dbConnection("dummyConnection");
    EXPECT_CALL(dbConnection, connect());
    EXPECT_CALL(dbConnection, disconnect());
    EXPECT_CALL(dbConnection, getSalary(testing::_)).Times(1).WillOnce(testing::Return(salary));

    EmployeeManager employeeManager(&dbConnection);

    float returnedSalary = employeeManager.getSalary(employeeId);

    ASSERT_EQ(salary, returnedSalary);
}

TEST(TestEmployeeManager, TestGetSalaryInRange)
{
    const int low = 5000, high = 8000;
    std::vector<Employee> returnedVector{Employee{1, 5600, "John"},
                                    Employee{2, 7000, "Jane"},
                                    Employee{3, 6600, "Alex"}};

    MockDatabaseConnection dbConnection("dummyConnection");
    EXPECT_CALL(dbConnection, connect());
    EXPECT_CALL(dbConnection, disconnect());
    EXPECT_CALL(dbConnection, getSalariesRange(low, high)).WillOnce(testing::Return(returnedVector));

    EmployeeManager employeeManager(&dbConnection);

    std::map<std::string, float> returnedMap = employeeManager.getSalariesBetween(low, high);

    for(auto it=returnedMap.begin(); it!=returnedMap.end(); ++it)
    {
        std::cout << it->first << " " << it->second << '\n';
        //Testet, ob sich die Gehälter sich in der Range befinden
        ASSERT_THAT(it->second, testing::Gt(low));
        ASSERT_THAT(it->second, testing::Lt(high));
        ASSERT_THAT(it->second, testing::AllOf(testing::Gt(low), testing::Lt(high)));

        //ASSERT_THAT(it->second, testing::AnyOf(testing::Gt(low), testing::Lt(high-3000)) );
    }
}
/*
TEST(TestEmployeeManager, TestError)
{
    MockDatabaseConnection dbConnection("dummyConnection");
    EXPECT_CALL(dbConnection, disconnect()).WillOnce(testing::Throw(std::runtime_error("Dummy error")));
    EXPECT_CALL(dbConnection, connect());
    ASSERT_THROW(EmployeeManager employeeManager(&dbConnection),std::runtime_error);

}
*/
/*
ACTION(myThrow)
{
    std::cout << "Throwing an error";
    throw std::runtime_error("Dummy error");
}
*/
/*
ACTION(MyReturn)
{
    return(10);
}
*/

/*
TEST(TestEmployeeManager, TestConnectionErrorAction)
{
    MockDatabaseConnection dbConnection("dummyConnection");
    EXPECT_CALL(dbConnection, disconnect()).WillOnce(myThrow());

    ASSERT_THROW(EmployeeManager employeeManager(&dbConnection), std::runtime_error);

}
*/

/*
TEST(TestEmployeeManager, TestgetSalaryAction)
{
    MockDatabaseConnection dbConnection("dummyConnection");
    EXPECT_CALL(dbConnection, getSalary(4)).WillOnce(MyReturn());
    
    EmployeeManager employeeManager(&dbConnection);

    auto result=employeeManager.getSalary(4);
    std::cout << "Result: " << result;
    ASSERT_EQ(50, result);
}
*/


TEST(VectorTests, ElementsAreTest)
{
    std::vector<int> v = generateNumbers(5, 3);
    // 0, 1, 2, 0, 1

    ASSERT_THAT(v, testing::ElementsAre(0, 1, 2, 0, 1));
}

TEST(VectorTests, RangeTest)
{
    using namespace testing;
    std::vector<int> v = generateNumbers(5, 3);

    ASSERT_THAT(v, Each(AllOf(Ge(0), Lt(3))));
}

TEST(TestEmployeeManager, CallbackTest)
{
    std::cout << "CallbackTest!\n";
    MockDatabaseConnection dbConnection("dummyConnection");
    testing::MockFunction<void(int, int)> mockFunction;
    dbConnection.setOnConnect(mockFunction.AsStdFunction());
    EXPECT_CALL(mockFunction, Call(testing::_, testing::_));
    dbConnection.connect();

}


int main(int argc, char **argv)
{
 ::testing::InitGoogleTest(&argc, argv);
 return RUN_ALL_TESTS();
}
