#include <assert.h>
#include <QPainter>
#include <QtGui>
#include "DsAnimationEdit.h"
#include "DsEditView.h"
#include "model/DsData.h"
#include "operator/DsOperator.h"
#include "util/DsDebug.h"

DsAnimationEdit::DsAnimationEdit(QWidget* parent)
    :QWidget(parent)
{
    setFixedHeight(100);
    m_lastpos=QPoint(0,0);
    m_move=0;
    m_ruler_unit=8;
    m_ruler_height=22;
    m_frame_height=18;
    m_mulSelect=false;
    m_from=0;
    m_to=0;
	createPopupMenu();
}

void DsAnimationEdit::paintEvent(QPaintEvent* event)
{
    DsDebug<<"PaintEvent"<<endl;

    QPainter painter(this);
    QSize wsize=size();

    int width=wsize.width();
    int height=wsize.height();

    QRect rect(0,0,width,height);

    QPen pen;
    pen.setColor(QColor(255,255,255));
    QBrush brush(QColor(255,255,255));

    painter.setPen(pen);
    painter.setBrush(brush);
    painter.drawRect(rect);

    drawRuler(painter);
    drawKeyFrames(painter);
    drawCurSelectFrame(painter);
    drawMulSelectFrame(painter);

}

void DsAnimationEdit::drawMulSelectFrame(QPainter& painter)
{
    if(!m_mulSelect)
    {
        return;
    }
    int from_pos=(m_from<m_to?m_from:m_to)*m_ruler_unit-m_move;
    int to_pos=(m_from<m_to?m_to:m_from)*m_ruler_unit-m_move;

    QColor color(0,0,255,70);
    painter.setPen(QPen(color));
    painter.setBrush(QBrush(color));
    DsDebug<<"from:"<<m_from<<" to:"<<m_to<<endl;

    painter.drawRect(from_pos,m_ruler_height,(to_pos-from_pos+m_ruler_unit),m_frame_height);
}
void DsAnimationEdit::drawRuler(QPainter& painter)
{
    QSize wsize=size();
    int width=wsize.width();

    QColor backgnd(200,200,200);
    QColor ruler_color(100,100,100);
    QColor text_color(0,0,0);
    painter.setBrush(QBrush(backgnd));
    painter.setPen(QPen(backgnd));
    painter.drawRect(QRect(0,0,width,22));

    painter.setPen(QPen(ruler_color));
    painter.setBrush(QBrush(ruler_color));


    int begin_frame=m_move/m_ruler_unit;
    int end_frame=(m_move+width)/m_ruler_unit;

    for(int i=begin_frame;i<=end_frame;i++)
    {
        int pos=i*m_ruler_unit-m_move;
        if(i%5!=0)
        {
            painter.drawLine(pos,0,pos,2);
            painter.drawLine(pos,20,pos,40);
        }
        else
        {
            painter.drawLine(pos,0,pos,4);
            painter.drawLine(pos,18,pos,40);
            painter.setBrush(QBrush(backgnd));
            painter.drawRect(QRect(pos,22,8,18));
            painter.setBrush(QBrush(ruler_color));
        }
    }
    painter.drawLine(0,22,width,22);
    painter.drawLine(0,40,width,40);

    painter.setPen(QPen(QColor(50,50,50)));
    painter.drawLine(0,23,width,23);


    painter.setPen(QPen(text_color));


    for(int i=begin_frame;i<=end_frame;i++)
    {
        int pos=i*m_ruler_unit-m_move;
        if(i%5==0)
        {
            painter.drawText(QPoint(pos,15),QString::number(i));
        }
    }


}
void DsAnimationEdit::drawKeyFrames(QPainter& painter)
{
	DsAnimation* cur_anmation=DsData::shareData()->getCurAnimation();
	if(!cur_anmation)
    {
        DsDebug<<"Animation Not Find"<<endl;
		return;
	}
	DsAnimation::Iterator  iter=cur_anmation->begin();

    painter.setPen(QPen(QColor(50,50,50)));
    painter.setBrush(QBrush(QColor(255,255,255)));

	for(;iter!=cur_anmation->end();++iter)
    {
        int frameid = (*iter)->getFrameId();
        if((*iter)->getType()==DsFrame::FRAME_KEY)
        {
            DsDebug<<"K("<<frameid<<") " ;
            int frame_pos=frameid*m_ruler_unit;
            frame_pos-=m_move;
            painter.drawEllipse(frame_pos+1,32,m_ruler_unit-2,6);
        }
        else
        {
            DsTweenFrame* tween=(DsTweenFrame*)(*iter);
            int from_id=tween->getFromKeyFrame()->getFrameId();
            int to_id=tween->getToKeyFrame()->getFrameId();
            DsDebug<<" T("<<frameid<<"("<<from_id<<","<<to_id<<"))";

            int start_pos=(from_id+1)*m_ruler_unit-m_move;
            int end_pos=to_id*m_ruler_unit-m_move;
            painter.drawLine(start_pos,34,end_pos,34);
            painter.drawLine(end_pos-4,30,end_pos,34);
            painter.drawLine(end_pos-4,38,end_pos,34);
        }
    }
    DsDebug<<endl;
}
void DsAnimationEdit::drawCurSelectFrame(QPainter& painter)
{
    int cur_frame=DsData::shareData()->getCurFrameIndex();
    DsDebug<<"curFrame:"<<cur_frame<<endl;
    if(cur_frame==-1)
    {
        return;
    }

    int pos=cur_frame*m_ruler_unit-m_move;
    painter.setPen(QPen(QColor(255,0,0)));
    painter.setBrush(QBrush(QColor(0,0,0,0)));
    painter.drawRect(pos,0,m_ruler_unit,m_ruler_height);
    painter.drawLine(pos+m_ruler_unit/2,m_ruler_height,pos+m_ruler_unit/2,m_ruler_height+m_frame_height);

}


void DsAnimationEdit::mousePressEvent(QMouseEvent* event)
{
	m_lastpos=event->pos();
    int x=event->x();
    int select_frame=(m_move+x)/m_ruler_unit;

    if(event->buttons()&Qt::LeftButton)
    {
        if( QApplication::queryKeyboardModifiers() &Qt::ShiftModifier)
        {
            m_mulSelect=true;
            m_from=select_frame;
            DsDebug<<"M_from="<<m_from<<" SelectFrame:"<<select_frame<<endl;
            m_to=select_frame;
        }
        else
        {
            m_mulSelect=false;
        }
        DsOperator::data()->setCurFrameIndex(select_frame);

    }
    else if(event->buttons()&Qt::RightButton)
    {
        if(m_mulSelect)
        {
            if(select_frame>=m_from&&select_frame<=m_to)
            {
                showMulSelectMenu(event);
            }
            else
            {
                m_mulSelect=false;
                showPopupMenu(event);
            }

        }
        else
        {
            showPopupMenu(event);
        }
    }
    update();
}

void DsAnimationEdit::mouseMoveEvent(QMouseEvent* event)
{
    int dx=-(event->x()-m_lastpos.x());
    int select_frame=(m_move+event->x())/m_ruler_unit;
    if(select_frame<0) select_frame=0;
    if(event->buttons()&Qt::LeftButton)
    {
        if(event->y()<22)
        {
            m_move+=dx;
            if(m_move<0)
            {
                m_move=0;
            }
            DsDebug<<"move:"<<m_move<<endl;
        }
        else
        {
            DsOperator::data()->setCurFrameIndex(select_frame);
        }

        if(!( QApplication::queryKeyboardModifiers()& Qt::ShiftModifier ))
        {
            m_mulSelect=false;
        }
        else
        {
            m_to=select_frame;
        }
    }
    update();
    m_lastpos=event->pos();
}
void DsAnimationEdit::mouseReleaseEvent(QMouseEvent* event)
{
    int dx=-(event->x()-m_lastpos.x());
    int select_frame=(m_move+event->x())/m_ruler_unit;

    if(event->buttons()&Qt::LeftButton)
    {
        if( !(QApplication::queryKeyboardModifiers()&Qt::ShiftModifier))
        {
            m_mulSelect=false;
        }
        else
        {
            m_to=select_frame;
        }
    }
}

void DsAnimationEdit::showMulSelectMenu(QMouseEvent* event)
{
    for(int i=m_from;i<=m_to;i++)
    {
        m_menuMulSelect->popup(QCursor::pos());
    }
}
void DsAnimationEdit::showPopupMenu(QMouseEvent* event)
{
    int x=event->x();
    int select_frame=(m_move+x)/m_ruler_unit;
    DsOperator::data()->setCurFrameIndex(select_frame);
    DsData* data=DsData::shareData();
    DsAnimation* anim=data->getCurAnimation();
    DsFrame* frame=data->getCurFrame();
    if(frame==NULL)
    {
        if(anim!=NULL)
        {
            ma_insertKeyFrame->setEnabled(true);
            ma_insertEmptyKeyFrame->setEnabled(true);
        }
        else
        {
            ma_insertKeyFrame->setEnabled(false);
            ma_insertEmptyKeyFrame->setEnabled(false);
        }
        ma_removeFrame->setEnabled(false);
        ma_createTween->setEnabled(false);
        ma_removeTween->setEnabled(false);
        ma_tweenToKeyFrame->setEnabled(false);
    }
    else  if(frame->getType()==DsFrame::FRAME_KEY)
    {
        if(frame->getFrameId()==select_frame)
        {
            ma_insertKeyFrame->setEnabled(false);
            ma_insertEmptyKeyFrame->setEnabled(false);
            ma_removeFrame->setEnabled(true);

            ma_createTween->setEnabled(false);
            ma_removeTween->setEnabled(false);
            ma_tweenToKeyFrame->setEnabled(false);
        }
        else if(frame->getFrameId()==data->getFrameNu()-1)
        {
            ma_insertKeyFrame->setEnabled(true);
            ma_insertEmptyKeyFrame->setEnabled(true);
            ma_removeFrame->setEnabled(false);
            ma_createTween->setEnabled(false);
            ma_removeTween->setEnabled(false);
            ma_tweenToKeyFrame->setEnabled(false);
        }
        else
        {
            ma_insertKeyFrame->setEnabled(true);
            ma_insertEmptyKeyFrame->setEnabled(true);
            ma_removeFrame->setEnabled(false);
            ma_createTween->setEnabled(true);
            ma_removeTween->setEnabled(false);
            ma_tweenToKeyFrame->setEnabled(false);
        }
    }
    else
    {
        ma_insertKeyFrame->setEnabled(true);
        ma_insertEmptyKeyFrame->setEnabled(true);
        ma_removeFrame->setEnabled(false);
        ma_createTween->setEnabled(false);
        ma_removeTween->setEnabled(true);
        ma_tweenToKeyFrame->setEnabled(true);
    }

    m_menu->popup(QCursor::pos());

}

void DsAnimationEdit::createPopupMenu()
{
    /* menu */
    m_menu=new QMenu(this);
    ma_insertKeyFrame=m_menu->addAction("Insert KeyFrame");
    ma_insertEmptyKeyFrame=m_menu->addAction("Insert Empty KeyFrame");
    ma_removeFrame=m_menu->addAction("Remove Frame");
    ma_createTween=m_menu->addAction("Create Tween");
    ma_removeTween=m_menu->addAction("Remove Tween");
    ma_tweenToKeyFrame=m_menu->addAction("Tween To KeyFrame");

    connect(ma_insertKeyFrame,SIGNAL(triggered()),this,SLOT(slotInsertKeyFrame()));
    connect(ma_insertEmptyKeyFrame,SIGNAL(triggered()),this,SLOT(slotInsertEmptyKeyFrame()));
    connect(ma_removeFrame,SIGNAL(triggered()),this,SLOT(slotRemoveFrame()));
    connect(ma_createTween,SIGNAL(triggered()),this,SLOT(slotCreateTween()));
    connect(ma_removeTween,SIGNAL(triggered()),this,SLOT(slotRemoveTween()));
    connect(ma_tweenToKeyFrame,SIGNAL(triggered()),this,SLOT(slotTweenToKeyFrame()));

    /* mul select menu */
    m_menuMulSelect=new QMenu(this);
    ma_mulSelectRemoveAll=m_menuMulSelect->addAction("Remove All Frame");
    connect(ma_mulSelectRemoveAll,SIGNAL(triggered()),this,SLOT(slotRemoveMulSelect()));
}



void DsAnimationEdit::slotInsertKeyFrame()
{
    DsData* data=DsData::shareData();
    int curFrameIndex=data->getCurFrameIndex();
    assert(curFrameIndex!=-1);
    DsOperator::data()->insertKeyFrame(curFrameIndex);
}
void DsAnimationEdit::slotInsertEmptyKeyFrame()
{
    DsData* data=DsData::shareData();
    int curFrameIndex=data->getCurFrameIndex();

    DsOperator::data()->insertEmptyKeyFrame(curFrameIndex);

}
void DsAnimationEdit::slotRemoveFrame()
{
    DsData* data=DsData::shareData();
    int curFrameIndex=data->getCurFrameIndex();
    DsOperator::data()->removeKeyFrame(curFrameIndex);
}
void  DsAnimationEdit::slotCreateTween()
{
    DsData* data=DsData::shareData();
    int curFrameIndex=data->getCurFrameIndex();
    DsOperator::data()->insertTween(curFrameIndex);
}
void DsAnimationEdit::slotRemoveTween()
{
    DsData* data=DsData::shareData();
    int curFrameIndex=data->getCurFrameIndex();
    DsOperator::data()->removeTween(curFrameIndex);
}
void DsAnimationEdit::slotTweenToKeyFrame()
{
    DsData* data=DsData::shareData();
    int curFrameIndex=data->getCurFrameIndex();
    DsOperator::data()->tweenToKeyFrame(curFrameIndex);
}
void DsAnimationEdit::slotRemoveMulSelect()
{
    assert(m_mulSelect);
    if(m_from<m_to)
    {
        DsOperator::data()->removeRangeFrame(m_from,m_to);
    }
    else
    {
        DsOperator::data()->removeRangeFrame(m_to,m_from);
    }
}































