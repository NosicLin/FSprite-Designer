#ifndef _DS_PROJECT_H_ 
#define _DS_PROJECT_H_
#include <vector>

class DsSprite;
class DsAnimation;
class DsFrameImage;
class DsFrame;

class DsProject 
{
	public:
		class DsSpriteInfo
		{
			public:
				DsSprite* m_sprite;
				int m_curFrameIndex;
				DsAnimation* m_curAnimation;
				DsFrameImage* m_curFrameImage;

				/* copy FrameImage */
				DsFrameImage* m_copyFrameImage;
				
				/* DsFrame*/
				DsFrame* m_copyFrame;

			public:
                void setCurAnimation(const std::string& id);
				void setCurFrameIndex(int index);
                void setCurFrameImage(const std::string& id);

				void dropCurAnimation();
				void dropCurFrameIndex();
                void dropCurFrameImage();

				DsAnimation* getCurAnimation();
				DsFrameImage* getCurFrameImage();
				DsFrame* getCurFrame();
				int getCurFrameIndex();
				
                /* copy and past */

                /* frame image */
                DsFrameImage* getCopyFrameImage(){return m_copyFrameImage;}
                void setCopyFrameImage(DsFrameImage* image);

                /* frame */
				void setCopyFrame(DsFrame* frame);
				DsFrame* getCopyFrame();


				DsSpriteInfo(DsSprite* sprite);
				~DsSpriteInfo();
		};

	public:
		static DsProject* loadFromFile(const std::string& filename);

	public:
		DsProject();
        ~DsProject();
    public:
        std::string getDirName(){return m_dirName;}
        std::string getFileName(){return m_fileName;}
        void setDirName(const std::string& name){m_dirName=name;}
        void setFileName(const std::string& name){m_fileName=name;}

	public:
        /* animation */
        void addSprite(DsSprite* sprite);
        void removeSprite(const std::string& id);
        bool hasSpriteWithName(const std::string& name);

        DsSprite* getCurSprite();
        DsSpriteInfo* getCurSpriteInfo(){return m_curSprite;}
        void setCurSprite(const std::string& id);


		/* animation*/
		DsAnimation* getCurAnimation();
        void setCurAnimation(const std::string& id);
		void dropCurAnimation();

		/* frame */
		DsFrame* getCurFrame();
		int getCurFrameIndex();
		void setCurFrameIndex(int framenu);
		void dropCurFrameIndex();

		/* frame image */
		DsFrameImage* getCurFrameImage();
        void setCurFrameImage(const std::string& name);
		void dropCurFrameImage();
	public:
		DsSprite* getSprite(int index);
        int getSpriteNu(){return m_sprites.size();}

        DsSprite* getSprite(const std::string& id);

	private:
		DsSpriteInfo* m_curSprite;
		std::vector<DsSpriteInfo*> m_sprites;

        std::string m_dirName;
        std::string m_fileName;
};

#endif /*_DS_PROJECT_H_*/
























