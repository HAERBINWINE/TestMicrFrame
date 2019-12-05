#ifndef VDD_TEST_H
#define VDD_TEST_H

#include "base.h"

class VDD_test : public Base
{
public:
    VDD_test();
    ~VDD_test();
    void start();
    void setParameter(int i,QStringList);
   static QStringList getParemeterList();
private:
   double m_ampl;
   double m_timescale;
   QString m_savepath;
};

#endif // VDD_TEST_H
