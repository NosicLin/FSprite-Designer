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
	if(event->buttons()&Qt::LeftButton)
	{
		int x=event->x();
		int select_frame=(m_move+x)/m_ruler_unit;
		DsOperator::data.setCurFrameIndex(select_frame);
	}
	else if(event->buttons()&Qt::RightButton)
	{
        int x=event->x();
        int select_frame=(m_move+x)/m_ruler_unit;
        DsOperator::data.setCurFrameIndex(select_frame);
        m_menu->popup(QCursor::pos());
	}

	update();
}

void DsAnimationEdit::createPopupMenu()
{
        m_menu=new QMenu(this);
        QAction* ma_insertFrame=m_menu->addAction("Insert KeyFrame");
        QAction* ma_insertEmptyKeyFrame=m_menu->addAction("Insert Empty KeyFrame");
        QAction* ma_removeFrame=m_menu->addAction("Remove Frame");
        QAction* ma_createTween=m_menu->addAction("Create Tween");
        QAction* ma_removeTween=m_menu->addAction("Remove Tween");
        QAction* ma_tweenToKeyFrame=m_menu->addAction("Tween To KeyFrame");

		connect(ma_insertFrame,SIGNAL(triggered()),this,SLOT(slotInsertKeyFrame()));
		connect(ma_insertEmptyKeyFrame,SIGNAL(triggered()),this,SLOT(slotInsertEmptyKeyFrame()));
		connect(ma_removeFrame,SIGNAL(triggered()),this,SLOT(slotRemoveFrame()));
		connect(ma_createTween,SIGNAL(triggered()),this,SLOT(slotCreateTween()));
		connect(ma_removeTween,SIGNAL(triggered()),this,SLOT(slotRemoveTween()));
		connect(ma_tweenToKeyFrame,SIGNAL(triggered()),this,SLOT(slotTweenToKeyFrame()));


}


void DsAnimationEdit::mouseMoveEvent(QMouseEvent* event)
{
	int dx=-(event->x()-m_lastpos.x());
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
			int select_frame=(m_move+event->x())/m_ruler_unit;
			DsOperator::data.setCurFrameIndex(select_frame);
		}
	}
	update();
	m_lastpos=event->pos();
}

void DsAnimationEdit::slotInsertKeyFrame()
{
    DsData* data=DsData::shareData();
    int curFrameIndex=data->getCurFrameIndex();
    assert(curFrameIndex!=-1);
    DsOperator::data.insertKeyFrame(curFrameIndex);
}
void DsAnimationEdit::slotInsertEmptyKeyFrame()
{

}
void DsAnimationEdit::slotRemoveFrame()
{
}
void  DsAnimationEdit::slotCreateTween()
{
}
void DsAnimationEdit::slotRemoveTween()
{
}
void DsAnimationEdit::slotTweenToKeyFrame()
{
}































