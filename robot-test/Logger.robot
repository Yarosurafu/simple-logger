*** Settings ***
Library           Process
Library           String
Library           Collections

*** Variables ***
${TEST_EXECUTABLE}    ${/}home${/}ysvirin${/}Documents${/}simple-logger${/}build${/}robot-test
${MSG_INFO}       ----------{ INFO }------------
${MSG_ERROR}      XXXXXXXXXXX{ ERROR }XXXXXXXXXXX
${MSG_WARNING}    !!!!!!!!!!{ WARNING }!!!!!!!!!!

*** Test Cases ***
SuccessGetInstanceTest
    ${handle}    Run Process    ${TEST_EXECUTABLE}    -ci
    Should Be Equal As Strings    ${handle.stdout}    instance != nullptr

FailGetInstanceTest
    ${handle}    Run Process    ${TEST_EXECUTABLE}    -ni
    Should Be Equal As Integers    ${handle.rc}    1
    Log    ${handle.stdout}

MsgTypeTest
    ${infoHandle}    Run Process    ${TEST_EXECUTABLE}    -im
    ${errorHandle}    Run Process    ${TEST_EXECUTABLE}    -em
    ${warningHandle}    Run Process    ${TEST_EXECUTABLE}    -wm
    ${outInfoHeader}    Get Line    ${infoHandle.stdout}    0
    ${outErrorHeader}    Get Line    ${errorHandle.stdout}    0
    ${outWarningHeader}    Get Line    ${warningHandle.stdout}    0
    Should Be Equal As Strings    ${outInfoHeader}    ${MSG_INFO}
    Should Be Equal As Strings    ${outErrorHeader}    ${MSG_ERROR}
    Should Be Equal As Strings    ${outWarningHeader}    ${MSG_WARNING}

SynchronizationTest
    ${threadQuantity}    Set Variable    4
    ${handle}    Run Process    ${TEST_EXECUTABLE}    -t    ${threadQuantity}
    ${msgRegExp}    Set Variable    ${MSG_INFO}\nPROCESS ID -->\\d{2,5}\nTHREAD ID -->\\d{12,16}\nmsg\n####################\n\n
    Log    ${handle.stdout}
    Log    ${msgRegExp}
    ${regExpMatches}    Get Regexp Matches    ${handle.stdout}    ${msgRegExp}
    Should Not Be Empty    ${regExpMatches}
    Length Should Be    ${regExpMatches}    ${threadQuantity}
