#include <gtest/gtest.h>

#include "logger.h"
#include "mock.h"

//--------------------------------------------------------
class LoggerTest : public ::testing::Test
{
protected:
    SemaphoreFuncsMock semaphoreMock;
};
//--------------------------------------------------------

//--------------------------------------------------------
//Test return result of Logger::getInstance
TEST_F(LoggerTest, GetInstanceTest)
{
    EXPECT_NE(Logger::getInstance(), nullptr);
}
//--------------------------------------------------------

//--------------------------------------------------------
//Test semaphore management of printlog()
//For synchronization, printlog() need to call sem_wait()
//and after that sem_post()
TEST_F(LoggerTest, SemaphoreControlTest)
{
    using ::testing::_;
    using ::testing::Return;
    using ::testing::InSequence;

    {
        InSequence sequence;

        EXPECT_CALL(semaphoreMock, sem_wait(_))
            .Times(1)
            .WillOnce(Return(0));

        EXPECT_CALL(semaphoreMock, sem_post(_))
            .Times(1)
            .WillOnce(Return(1));
    }

    Logger::getInstance()->printLog(Logger::MSG_TYPE::MSG_INFO, "msg");
}
//--------------------------------------------------------

//--------------------------------------------------------
//Test closing and unlinking semaphore after
//deleteInstance() call
TEST_F(LoggerTest, SemaphoreCloseTest)
{
    using ::testing::_;
    using ::testing::Return;
    using ::testing::InSequence;

    {
        InSequence sequence;

        EXPECT_CALL(semaphoreMock, sem_close(_))
            .Times(1)
            .WillOnce(Return(0));

        EXPECT_CALL(semaphoreMock, sem_unlink(_))
            .Times(1)
            .WillOnce(Return(0));    
    }

    Logger::deleteInstance();
}
//--------------------------------------------------------

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}