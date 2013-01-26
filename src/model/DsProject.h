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
			m_curFrame=NULL;
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

		/* Frame */
		DsFrame* getCurFrame(){return m_curFrame;}
		void setCurFrame(int framenu);
		
		/* Frame image */
		DsFrameImage* getCurFrameImage(){return m_curFrameImage;}
		void setCurFrameImage(const std::string& name);

	private:
		std::string m_name;
		DsSprite* m_sprite;

		DsAnimation* m_curAnimation;
		DsFrame* m_curFrame;
		DsFrameImage* m_curFrameImage;
};

#endif /*_DS_PROJECT_H_*/




















