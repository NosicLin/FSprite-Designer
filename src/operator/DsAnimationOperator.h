#ifndef _DS_ANIMATION_OPERATOR_H_
#define _DS_ANIMATION_OPERATOR_H_
#include <QTimer>
#include <QObject>
#include <model/DsData.h>


class DsAnimationOperator :public QObject
{
    Q_OBJECT
	public:
		DsAnimationOperator();
    public:
        bool isAnimationPlay(){return m_playing;}
		void animationPlay();
		void animationStop();
	public slots:
        void slotTimerTigger();
        void slotSpriteChange();

	protected:
        void scheduledTimer();
	private:
		bool m_playing;
		QTimer* m_timer;
		DsData* m_data;
};

#endif /*_DS_ANIMATION_OPERATOR_H_*/



