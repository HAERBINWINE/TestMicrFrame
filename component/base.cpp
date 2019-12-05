#include "base.h"



Base::Base()
{
    IncreaseRefCnt();
}

int Base::reference_cnt=0;
OSC* Base::m_osc=new OSC();
