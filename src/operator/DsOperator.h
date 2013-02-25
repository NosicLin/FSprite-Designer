#ifndef _DS_OPERATOR_H_
#define _DS_OPERATOR_H_

#include "DsDataOperator.h"
#include "DsAnimationOperator.h"
#include "DsIoOperator.h"
#include "DsAuxOperator.h"

class DsOperator 
{
    public:
        static DsAnimationOperator* animation();
        static DsIoOperator* io();
        static DsDataOperator* data();
        static DsAuxOperator* aux();
};


#endif /*_DS_OPERATOR_H_*/


