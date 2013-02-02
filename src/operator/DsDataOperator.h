#ifndef _DS_DATA_OPERATOR_H_
#define _DS_DATA_OPERATOR_H_

#include <string>
#include "model/DsModel.h"

class DsDataOperator
{
	public:
        DsDataOperator();
	
	public:
        /* project */
        void addProject(DsProject* project);
        void removeProject(const std::string& name);
        void renameProject(const std::string& name,const std::string& target);
        void setCurProject(const std::string& name);

        /* sprite */
        void setCurAnimation(const std::string& anim);
        void dropCurAnimation();
        void renameAnimation(const std::string& proj_name,const std::string& anim_name,const std::string& target_name);
        void addAnimation(const std::string& anim);
        void removeAnimation(const std::string& anim);


        /* animation */
        void setCurFrameIndex(int frame);
        void dropCurFrameIndex();

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

        void setCurFrameImage(const std::string& anim);
        void addFrameImage(DsFrameImage* image);
        void dropCurFrameImage();


		/* frameImage operator */
        void setCurFrameImagePos(float tx,float ty);
        void setCurFrameImageScale(float sx,float sy);
        void setCurFrameImageAngle(float angle);
		void setArea(float x0,float y0,float x1,float y1);
	private:
		DsData* m_data;

};
#endif /*_DS_DATA_OPERATOR_H_*/




