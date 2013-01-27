#include <QPainter>
#include <QtGui>
#include "DsAnimationEdit.h"
#include "DsEditView.h"

DsAnimationEdit::DsAnimationEdit(QWidget* parent)
    :QWidget(parent)
{
    setFixedHeight(100);
    m_lastpos=QPoint(0,0);
    m_move=0;
    m_ruler_unit=8;
    m_ruler_height=8;
}

void DsAnimationEdit::paintEvent(QPaintEvent* event)
{
    out<<"PaintEvent"<<endl;

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

}

void DsAnimationEdit::drawRuler(QPainter& painter)
{
    QSize wsize=size();
    int width=wsize.width();
    int height=wsize.height();

    QColor backgnd(200,200,200);
    QColor ruler_color(100,100,100);
    QColor text_color(0,0,0);
    painter.setBrush(QBrush(backgnd));
    painter.setPen(QPen(backgnd));
    painter.drawRect(QRect(0,0,width,22));

    painter.setPen(QPen(ruler_color));
    painter.setBrush(QBrush(ruler_color));


    int begin_pos=m_move%m_ruler_unit;
    int begin_value=(m_move+m_ruler_unit-1)/m_ruler_unit;

    int value=begin_value;
    for(int i=begin_pos;i<width;i+=m_ruler_unit)
    {
        if(value%5!=0)
        {
            painter.drawLine(i,0,i,2);
            painter.drawLine(i,20,i,40);
        }
        else
        {
            painter.drawLine(i,0,i,4);
            painter.drawLine(i,18,i,40);
            painter.setBrush(QBrush(backgnd));
            painter.drawRect(QRect(i,22,8,18));
            painter.setBrush(QBrush(ruler_color));
        }
        value++;
    }
    painter.drawLine(0,22,width,22);
    painter.drawLine(0,40,width,40);

    painter.setPen(QPen(QColor(50,50,50)));
    painter.drawLine(0,23,width,23);



    painter.setPen(QPen(text_color));


    for(int i=begin_pos;i<width;i+=m_ruler_unit)
    {
        if(begin_value%5==0)
        {
            painter.drawText(QPoint(i,15),QString::number(begin_value));
        }
        begin_value++;
    }


}
void DsAnimationEdit::drawKeyFrame(QPainter& painter)
{
}

void DsAnimationEdit::mousePressEvent(QMouseEvent* event)
{
    m_lastpos=event->pos();
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
            out<<"move:"<<m_move<<endl;
        }
    }
    update();
    m_lastpos=event->pos();
}





























