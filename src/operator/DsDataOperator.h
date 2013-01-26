#ifndef _DS_DATA_OPERATOR_H_
#define _DS_DATA_OPERATOR_H_

#include <string>
#include "model/DsData.h"
#include "model/DsSprite.h"
#include "model/DsAnimation.h"
#include "model/DsFrame.h"
#include "model/DsFrameImage.h"

class DataOperator
{
	public:
		DataOperator();
	
	public:
		/* change cur information */
		void setCurProject(DsProject* proj);
		void setCurAnimation(const std::string& anim);
		void setCurFrame(int frame);
		void setCurFrameImage(const std::string& anim);

		/* sprite operator */
		void addAnimation(const std::string& anim);
		void removeAnimation(const std::string& anim);

		/* animation operator */
		void setAnimationFps(int fps);
		void pushFrame();
		void removeFrame(int index);
		void insertFrame(int index);
		void copyFrame(int src,int dst);
		void swapFrame(int l,int r);

		/* frame operator */
		void upFrameImage(const std::string& name);
		void downFrameImage(const std::string& name);
		void frameImageToFront(const std::string& name);
		void frameImageToTail(const std::string& name);
		void duplicateFrameImage(const std::string& src_name,const std::string& dst_name);

		/* frameImage operator */
		void setPostion(float tx,float ty);
		void setScale(float sx,float sy);
		void setAngle(float angle);
		void setArea(float x0,float y0,float x1,float y1);
	private:
		DsData* m_data;

};
#endif /*_DS_DATA_OPERATOR_H_*/




