#ifndef _DS_OPERATOR_H_
#define _DS_OPERATOR_H_
#include "DsDataOperator.h"
#include "DsAnimationOperator.h"
#include "DsIoOperator.h"

class DsOperator 
{
    public:
        static DsAnimationOperator* animation();
        static DsIoOperator* io();

        /* it a mistake to use static data here */
        static DsDataOperator* data();
};


#endif /*_DS_OPERATOR_H_*/


