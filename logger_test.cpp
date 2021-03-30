#include <gtest/gtest.h>

#include "logger.h"
#include "mock.h"
#include "error_handle.h"
#include "agentmock.h"

//--------------------------------------------------------
class LoggerTest : public ::testing::Test
{
protected:
    SemaphoreFuncsMock semaphoreMock;
    AgentMock agentMock;
};
//--------------------------------------------------------

TEST_F(LoggerTest, SuccessGetInstanceTest)
{
    using ::testing::_;
    using ::testing::AtLeast;
    using ::testing::ReturnNull;
    using ::testing::Invoke;

    EXPECT_CALL(agentMock, a_pthread_mutex_lock(_))
        .Times(AtLeast(1))
        .WillOnce(Invoke(pthread_mutex_lock));

    EXPECT_CALL(agentMock, a_pthread_mutex_unlock(_))
        .Times(AtLeast(1))
        .WillOnce(Invoke(pthread_mutex_unlock));

    EXPECT_CALL(agentMock, a_sem_open(_, _, _, _))
        .Times(AtLeast(1))
        .WillOnce(Invoke(sem_open));

    EXPECT_CALL(agentMock, a_strerror(_))
        .Times(0);

    EXPECT_CALL(agentMock, a_exit(_))
        .Times(0);

    Logger::getInstance(agentMock);
}

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
    Agent agent;
    Logger::getInstance(agent)->printLog(Logger::MSG_TYPE::MSG_INFO, "msg");
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

//--------------------------------------------------------
TEST_F(LoggerTest, FailGetInstanceTest)
{
    using ::testing::_;
    using ::testing::AtLeast;
    using ::testing::ReturnNull;

    EXPECT_CALL(agentMock, a_pthread_mutex_lock(_))
        .Times(AtLeast(1));

    EXPECT_CALL(agentMock, a_pthread_mutex_unlock(_))
        .Times(AtLeast(1));

    EXPECT_CALL(agentMock, a_sem_open(_, _, _, _))
        .Times(AtLeast(1))
        .WillOnce(ReturnNull());

    EXPECT_CALL(agentMock, a_strerror(_))
        .Times(AtLeast(1));

    EXPECT_CALL(agentMock, a_exit(_))
        .Times(AtLeast(1));

    Logger::getInstance(agentMock);
}
//--------------------------------------------------------

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}