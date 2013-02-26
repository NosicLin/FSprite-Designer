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
        void newSprite();
        void removeSprite(const std::string& id);
        bool renameSprite(const std::string& id,const std::string& name);
        void setCurSprite(const std::string& id);

        /* sprite */
		void newAnimation();
        void setCurAnimation(const std::string& id);
        void dropCurAnimation();

        void renameAnimation(
				const std::string& anim_name,
				const std::string& target_name);

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
        void frameImageMoveUp();
        void frameImageMoveDown();
        void frameImageMoveEnd();
        void frameImageMoveFront();

        void duplicateFrameImage(const std::string& src_name,const std::string& dst_name);

        void setCurFrameImage(const std::string& id);
        void addFrameImage(DsFrameImage* image);
        void removeFrameImage(const std::string& name);
        void removeCurFrameImage(); /* it will remove current */
        void dropCurFrameImage();


		/* frameImage operator */
        void setCurFrameImagePos(float tx,float ty);
        void setCurFrameImageScale(float sx,float sy);
        void setCurFrameImageAngle(float angle);
        void setCurFrameImageOffset(float fx,float fy);
        void setCurFrameImageTextureArea(float x0,float y0,float x1,float y1);
        void setCurFrameImageAlpha(float alpha);
    private:
		DsData* m_data;

};
#endif /*_DS_DATA_OPERATOR_H_*/
















