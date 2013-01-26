#ifndef  _DS_ANIMATION_H_
#define  _DS_ANIMATION_H_

#include <string>
#include <vector>

class DsFrame;
class  DsAnimation
{
	public:
		typedef std::vector<DsFrame*>::iterator Iterator;

	public:
		DsAnimation(const std::string& name);
		~DsAnimation();

	public:
		std::string getName(){return m_name;}
		void pushFrame(DsFrame* anim);
		DsFrame* getFrame(int index);
		void removeFrame(int index);
		void insertFrame(DsFrame* anim,int index);
		void swapFrame(int l,int r);
		int getFrameNu(){return m_frames.size();};

		void setFps(int fps) {m_fps=fps;}
		int getFps(){return m_fps;}

		void setDefaultFps(int fps){m_defaulFps=fps;}
		int getDefaultFps(){return m_defaulFps;}


		Iterator begin(){return m_frames.begin();}
		Iterator end(){return m_frames.end();}
	private:
		std::vector<DsFrame*> m_frames;
		std::string m_name;
		int m_fps;
        static int m_defaulFps;
};



#endif 

