#ifndef _DS_PROJECT_H_
#define _DS_PROJECT_H_

#include <string>

#include "DsSprite.h"
#include "DsAnimation.h"
#include "DsFrame.h"
#include "DsFrameImage.h"



/* Note: DsProjectState Is Used For Undo and Redo, Every Time Project Property Change,
         Opeartor will save the state of the project, this method is so easy, but will
         used too many memory
*/

class DsProjectState
{
    DsSprite* m_sprite;
    int m_curFrameIndex;
    std::string m_curAnimation;
    std::string m_curFrameImage;
};

class DsProject
{
	public:
        DsProject(DsSprite* sprite,std::string name);
	public:
        DsSprite* getSprite(){return m_sprite;}
        std::string getName(){return m_name;}
        std::string getRealName(){return m_realName;}
        void setName(const std::string& name){m_name=name;}

        /* path */
        std::string getFileName(){return m_fileName;}
        void setFileName(const std::string& filename){m_fileName=filename;}


		/* animation */
        DsAnimation* getCurAnimation(){return m_curAnimation;}
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

        /* undo/ redo */
        int curStateIndex();
        int saveStateNu();
        void pushState();
        void popState();

	private:
        std::string m_name;
        std::string m_realName;
        std::string m_fileName;

		DsSprite* m_sprite;
		int m_curFrameIndex;
		DsAnimation* m_curAnimation;
        DsFrameImage* m_curFrameImage;

        /* used for undo/redo */
        std::vector<DsProjectState*> m_savedState;
        int m_curStateIndex;
};

#endif /*_DS_PROJECT_H_*/




















