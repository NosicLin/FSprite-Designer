#include "DsOperator.h"

DsDataOperator DsOperator::data;
static DsAnimationOperator* s_animation=NULL;
static DsIoOperator* s_io=NULL;


DsAnimationOperator* DsOperator::animation()
{
    if(s_animation==NULL)
    {
        s_animation=new DsAnimationOperator();
    }
    return s_animation;
}
DsIoOperator* DsOperator::io()
{
    if(s_io==NULL)
    {
        s_io=new DsIoOperator;
    }
    return s_io;
}


