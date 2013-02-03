#include "util/DsDebug.h"
#include "DsAnimationOperator.h"
#include "operator/DsOperator.h"

DsAnimationOperator::DsAnimationOperator()
{
    m_timer=new QTimer;
    m_data=DsData::shareData();
	m_playing=false;
    connect(m_timer,SIGNAL(timeout()),this,SLOT(slotTimerTigger()));
}

void DsAnimationOperator::animationPlay()
{
	m_playing=true;
	scheduledTimer();
}

void DsAnimationOperator::animationStop()
{
	m_playing=false;
}

void DsAnimationOperator::scheduledTimer()
{
    DsDebug<<"ScheduledTimer"<<endl;
	if(m_playing)
	{
		DsAnimation* anim=m_data->getCurAnimation();
		if(!anim)
		{
			return;
		}

		int fps=anim->getFps();
		if(fps==0) fps=1;

		int total_frames=anim->getFrameNu();

		int cur_frame=m_data->getCurFrameIndex();

		cur_frame+=1;
        if(cur_frame>=total_frames)
		{
			cur_frame=0;
		}

        DsOperator::data.setCurFrameIndex(cur_frame);
		m_timer->start(1000/fps);
	}
}

void DsAnimationOperator::slotTimerTigger()
{
	if(m_playing)
	{
		scheduledTimer();
	}
}







