#ifndef TESTCOMP_H
#define TESTCOMP_H
#include "base.h"



class TestComp : public Base
{
public:
    TestComp();
    ~TestComp();
    void start();
    void setParameter(int);
};


#endif // TESTCOMP_H
