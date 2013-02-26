#include "DsOperator.h"





static DsDataOperator* s_data=NULL;
static DsAnimationOperator* s_animation=NULL;
static DsIoOperator* s_io=NULL;
static DsAuxOperator* s_aux=NULL;


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
DsDataOperator* DsOperator::data()
{
    if(s_data==NULL)
    {
        s_data=new DsDataOperator;
    }
    return s_data;
}
DsAuxOperator* DsOperator::aux()
{
    if(s_aux==NULL)
    {
        s_aux=new DsAuxOperator;
    }
    return  s_aux;
}


