#include <gtest/gtest.h>

#include "logger.h"
#include "mock.h"

class LoggerTest : public ::testing::Test
{
protected:
    SemaphoreFuncsMock semaphoreMock;
};

TEST_F(LoggerTest, WaitSemaphoreTest)
{
    using ::testing::_;
    using ::testing::Return;

    EXPECT_CALL(semaphoreMock, sem_wait(_))
        .Times(1)
        .WillOnce(Return(0));

    Logger::getInstance()->printLog(Logger::MSG_TYPE::MSG_INFO, "msg");
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}