#ifndef _DS_PROJECT_H_
#define _DS_PROJECT_H_

#include <string>

#include "DsSprite.h"
#include "DsAnimation.h"
#include "DsFrame.h"
#include "DsFrameImage.h"

class DsProject
{
	public:
		DsProject(DsSprite* sprite,std::string name)
		{
			m_name=name;
			m_sprite=sprite;
			m_curAnimation=NULL;
            m_curFrameIndex=-1;
			m_curFrameImage=NULL;
		}
		DsProject(DsSprite* sprite)
		{
			m_name=sprite->getName();
			m_sprite=sprite;
		}
	public:
        DsSprite* getSprite(){return m_sprite;}
		std::string getName(){return m_name;}

		/* animation */
        DsAnimation* getCurAniamtion(){return m_curAnimation;}
        void setCurAnimation(const std::string& anim);
		void dropCurAnimation();

		/* Frame */
        DsFrame* getCurFrame();
		int getCurFrameIndex(){return m_curFrameIndex;}
		void setCurFrameIndex(int framenu);
		void dropCurFrameIndex();
		
		/* Frame image */
		DsFrameImage* getCurFrameImage(){return m_curFrameImage;}
        void setCurFrameImage(const std::string& name);
		void dropCurFrameImage();

	private:
		std::string m_name;
		DsSprite* m_sprite;
		int m_curFrameIndex;

		DsAnimation* m_curAnimation;
		DsFrameImage* m_curFrameImage;
};

#endif /*_DS_PROJECT_H_*/




















