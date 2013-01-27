#ifndef _DS_FRAME_H_
#define _DS_FRAME_H_
#include <vector>

class DsFrameImage;

class DsFrame 
{
	public:
		typedef std::vector<DsFrameImage*>::iterator Iterator;
	public:
        DsFrame(int id);
		DsFrame();
		~DsFrame();
	public:

		std::string getName(){return m_name;}
		DsFrameImage* getFrameImage(const std::string& name);

		void pushFrameImage(DsFrameImage* image);
		void removeFrameImage(const std::string& name);

		void upFrameImage(const std::string& name);
		void downFrameImage(const std::string& name);

		void frameImageToFront(const std::string& name);
		void frameImageToTail(const std::string& name);

		void duplicateFrameImage(const std::string& src_name,const std::string& dst_name);

        int getFrameImageNu(){return m_images.size();}
		DsFrameImage* getFrameImage(int index);

		Iterator begin(){return m_images.begin();}
		Iterator end(){return m_images.end();}

		DsFrame* clone();
		void setFrameId(int id){m_frameId=id;}
		int getFrameId(){return m_frameId;}

	private:
		std::vector<DsFrameImage*> m_images;
		std::string m_name;
		int m_frameId;
};

#endif 



