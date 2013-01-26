#ifndef _DS_FRAME_H_
#define _DS_FRAME_H_
#include <vector>

class DsFrameImage;

class DsFrame 
{
	public:
		typedef std::vector<DsFrameImage*>::iterator Iterator;
	public:
		DsFrame(const std::string& name);
		DsFrame();
		~DsFrame();
	public:

		std::string getName(){return m_name;}
		void pushFrameImage(DsFrameImage* image);

		DsFrameImage* getFrameImage(const std::string& name);
		void removeFrameImage(const std::string& name);

		void upFrameImage(const std::string& name);
		void downFrameImage(const std::string& name);
		void frameImageToFront(const std::string& name);
		void frameImageToTail(const std::string& name);
		void duplicateFrameImage(const std::string& src_name,const std::string& dst_name);

		Iterator begin(){return m_images.begin();}
		Iterator end(){return m_images.end();}

	private:
		std::vector<DsFrameImage*> m_images;
		std::string m_name;
};

#endif 


