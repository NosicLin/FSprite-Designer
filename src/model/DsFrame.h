#ifndef _DS_FRAME_H_
#define _DS_FRAME_H_
#include <vector>

class DsFrameImage;

class DsKeyFrame;
class DsFrame 
{
	public:
		enum 
		{
			FRAME_KEY,
			FRAME_TWEEN,
		};

    public:
		DsFrame(int frameid){m_frameid=frameid;}
		virtual ~DsFrame(){};
		virtual int getType()=0;
		int getFrameId(){return m_frameid;}
        void setFrameId(int frame){m_frameid=frame;}
	protected:
		int m_frameid;
};

class DsTweenFrame:public DsFrame 
{
    public:
		DsTweenFrame(DsKeyFrame* from,DsKeyFrame* to,int id);
		virtual int getType()
		{
			return FRAME_TWEEN;
		}
		DsKeyFrame* slerpToKeyFrame(int index);

		void setFromKeyFrame(DsKeyFrame* frame);
        void setToKeyFrame(DsKeyFrame* frame);
        DsKeyFrame* getFromKeyFrame(){return m_from;}
        DsKeyFrame* getToKeyFrame(){return m_to;}
	private:
		DsKeyFrame* m_from;
		DsKeyFrame* m_to;
};



class DsKeyFrame:public DsFrame 
{
	public:
		typedef std::vector<DsFrameImage*>::iterator Iterator;
	public:
        DsKeyFrame(int id);
        ~DsKeyFrame();
		virtual int getType()
		{
			return FRAME_KEY;
		}
	public:

        void pushFrameImage(DsFrameImage* image);
        void insertFrameImage(DsFrameImage* image,int pos);

		void removeFrameImage(const std::string& name);

		void upFrameImage(const std::string& name);
		void downFrameImage(const std::string& name);

		void frameImageToFront(const std::string& name);
        void frameImageToEnd(const std::string& name);

		void duplicateFrameImage(const std::string& src_name,const std::string& dst_name);

        int getFrameImageNu(){return m_images.size();}
        DsFrameImage* getFrameImage(const std::string& id);
        DsFrameImage* getFrameImage(int index);
        int getFrameImagePos(const std::string& name);

        void clearFrameImage(){m_images.clear();}

		Iterator begin(){return m_images.begin();}
		Iterator end(){return m_images.end();}

		DsKeyFrame* clone();
	private:
		std::vector<DsFrameImage*> m_images;
};

#endif 



