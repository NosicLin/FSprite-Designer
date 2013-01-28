#ifndef  _DS_ANIMATION_H_
#define  _DS_ANIMATION_H_

#include <string>
#include <vector>

class DsFrame;
class  DsAnimation
{
	public:
		typedef std::vector<DsFrame*>::iterator Iterator;
		static void setDefaultFps(int fps){m_defaulFps=fps;}
		static int getDefaultFps(){return m_defaulFps;}


	public:
		DsAnimation(const std::string& name);
		~DsAnimation();

	public:
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
		void insertEmptyKeyFrame(int index);
		void insertTweenFrame(int index);
		int getKeyFrameNu(){return m_keyFrames.size();};

		void setFps(int fps) {m_fps=fps;}
		int getFps(){return m_fps;}

        Iterator begin(){return m_keyFrames.begin();}
        Iterator end(){return m_keyFrames.end();}
	protected:
        int toKeyFramePos(int index);

		/* if frame id already exist, it will replace orign*/
		void rawInsertFrame(DsFrame* frame);
		void rawRemoveFrame(DsFrame* frame);

		/* frame type is key frame */
        void insertFrameTypeKey(int index,bool empty);

	private:
		std::vector<DsFrame*> m_keyFrames;
		std::string m_name;
		int m_fps;
        static int m_defaulFps;
};

#endif 
















