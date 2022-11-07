#ifndef CPPQUERYABLETEST_QUERYABLE_TESTCASEPARAMS_TESTCASEPARAMS_H
#define CPPQUERYABLETEST_QUERYABLE_TESTCASEPARAMS_TESTCASEPARAMS_H

#include <string>

class TestCaseParams
{
public:
    TestCaseParams() { }
    virtual ~TestCaseParams() { }

    virtual std::string ToString() const { return ""; }
};

#endif