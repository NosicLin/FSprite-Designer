#ifndef _DS_DATA_OPERATOR_H_
#define _DS_DATA_OPERATOR_H_

#include <string>
#include "model/DsModel.h"

class DsDataOperator
{
	public:
        DsDataOperator();
	
	public:
		/* change cur information */
		void setCurProject(DsProject* proj);
        void setCurAnimation(const std::string& anim);
        void dropCurAnimation();

        void setCurFrameIndex(int frame);
        void dropCurFrameIndex();

        void setCurFrameImage(const std::string& anim);
        void dropCurFrameImage();

		/* sprite operator */
		void addAnimation(const std::string& anim);
		void removeAnimation(const std::string& anim);

		/* animation operator */
		void setAnimationFps(int fps);
        void removeKeyFrame(int index);
        void removeRangeFrame(int from,int to);

        void insertKeyFrame(int index);
        void insertEmptyKeyFrame(int index);
        void tweenToKeyFrame(int index);

        void insertTween(int index);
        void removeTween(int index);

		/* frame operator */
		void upFrameImage(const std::string& name);
		void downFrameImage(const std::string& name);
		void frameImageToFront(const std::string& name);
		void frameImageToTail(const std::string& name);
        void duplicateFrameImage(const std::string& src_name,const std::string& dst_name);



		/* frameImage operator */
        void setCurFrameImagePos(float tx,float ty);
        void setCurFrameImageScale(float sx,float sy);
        void setCurFrameImageAngle(float angle);
		void setArea(float x0,float y0,float x1,float y1);
	private:
		DsData* m_data;

};
#endif /*_DS_DATA_OPERATOR_H_*/




