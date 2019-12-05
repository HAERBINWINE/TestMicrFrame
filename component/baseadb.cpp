#include "baseadb.h"

BaseADB::BaseADB()
{
    IncreaseRefCnt();
}



int BaseADB::reference_cnt=0;
QAdb* BaseADB::m_adb=new QAdb();
