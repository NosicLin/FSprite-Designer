#ifndef  _DS_ANIMATION_H_
#define  _DS_ANIMATION_H_

#include <string>
#include <vector>

class DsFrame;
class DsKeyFrame;
class  DsAnimation
{
	public:
		typedef std::vector<DsFrame*>::iterator Iterator;
		static void setDefaultFps(int fps){m_defaulFps=fps;}
		static int getDefaultFps(){return m_defaulFps;}
	public:
		DsAnimation(const std::string& name);
        ~DsAnimation();
        static DsAnimation* createWithFirstFrame(const std::string& name);

	public:
        std::string getID(){return m_id;}
        void setID(const std::string& id){m_id=id;}
		std::string getName(){return m_name;}
		void setName(const std::string& name){m_name=name;}

		/* used to init the animtion frames */
		void pushFrame(DsFrame* frame);

		/* normal frame */
		DsFrame* getFrame(int index);
		int getFrameNu();

		/* key frame function */
		void removeKeyFrame(int index);
        void insertKeyFrame(int index);
        void insertKeyFrame(int index,DsKeyFrame* frame);
        void insertEmptyKeyFrame(int index);


        void insertTween(int index);
        void removeTween(int index);
        int getKeyFrameNu(){return m_keyFrames.size();}

		void setFps(int fps) {m_fps=fps;}
		int getFps(){return m_fps;}

        Iterator begin(){return m_keyFrames.begin();}
        Iterator end(){return m_keyFrames.end();}

        DsAnimation* clone(int clone_id=false);
	protected:
        int toKeyFramePos(int index);

		/* if frame id already exist, it will replace orign*/
		void rawInsertFrame(DsFrame* frame);
		void rawRemoveFrame(DsFrame* frame);
        void rawInsertKeyFrame(int index,DsKeyFrame* frame);

	private:
		std::vector<DsFrame*> m_keyFrames;
		std::string m_name;
		std::string m_id;

		int m_fps;
        static int m_defaulFps;
};

#endif 
















