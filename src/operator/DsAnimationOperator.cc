#include "util/DsDebug.h"
#include "DsAnimationOperator.h"
#include "operator/DsOperator.h"

DsAnimationOperator::DsAnimationOperator()
{
    m_timer=new QTimer;
    m_data=DsData::shareData();
    m_playing=false;
    connect(m_timer,SIGNAL(timeout()),this,SLOT(slotTimerTigger()));

    connect(m_data,SIGNAL(signalCurProjectChange()),this,SLOT(slotSpriteChange()));
    connect(m_data,SIGNAL(signalCurSpriteChange()),this,SLOT(slotSpriteChange()));
    connect(m_data,SIGNAL(signalCurAnimationChange()),this,SLOT(slotSpriteChange()));
    connect(m_data,SIGNAL(signalProjectPropertyChange()),this,SLOT(slotSpriteChange()));
    connect(m_data,SIGNAL(signalAnimationPropertyChange()),this,SLOT(slotSpriteChange()));
}

void DsAnimationOperator::animationPlay()
{
	m_playing=true;
    scheduledTimer();
    m_data->emitSignal(DsData::SG_ANIMATION_PLAY_STATE_CHANGE);
}

void DsAnimationOperator::animationStop()
{
    m_playing=false;
    m_data->emitSignal(DsData::SG_ANIMATION_PLAY_STATE_CHANGE);
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

        DsOperator::data()->setCurFrameIndex(cur_frame);
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
void DsAnimationOperator::slotSpriteChange()
{
    if(!m_playing)
    {
        return ;
    }
    DsAnimation* anim=m_data->getCurAnimation();
    if(anim==NULL)
    {
        m_playing=false;
        m_data->emitSignal(DsData::SG_ANIMATION_PLAY_STATE_CHANGE);
    }
    else if(anim->getFrameNu()==0)
    {
        m_playing=false;
        m_data->emitSignal(DsData::SG_ANIMATION_PLAY_STATE_CHANGE);
    }
}












