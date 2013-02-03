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
		void animationPlay();
		void animationStop();
	public slots:
		void slotTimerTigger();

	protected:
        void scheduledTimer();
	private:
		bool m_playing;
		QTimer* m_timer;
		DsData* m_data;
};

#endif /*_DS_ANIMATION_OPERATOR_H_*/



