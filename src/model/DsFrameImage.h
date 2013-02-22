#ifndef _DS_FRAME_IMAGE_H_
#define _DS_FRAME_IMAGE_H_

#include <string>

class DsImage;
class DsFrameImage
{
	public:
		static DsFrameImage* create(const std::string& img_name);
		~DsFrameImage();

    public:
        std::string getID(){return m_id;}
        DsImage* getImage(){return m_image;}
		void setImage(DsImage* img);

		float getPosX(){return m_tx;}
		float getPosY(){return m_ty;}

		int getWidth(){return m_width;}
		int getHeight(){return m_height;}

		float getAngle(){return m_angle;}
		float getScaleX(){return m_sx;}
        float getScaleY(){return m_sy;}

        bool hit(float x,float y);
		DsFrameImage* clone();

		void getTextureArea(float* x0,float* y0, float* x1,float* y1)
		{
			*x0=m_areax0;
			*y0=m_areay0;
			*x1=m_areax1;
			*y1=m_areay1;
		}

		void setPos(float x,float y)
		{
			m_tx=x;
			m_ty=y;
		}

		void setAngle(float angle)
		{
			m_angle=angle;
		}

		void setScale(float sx,float sy)
		{
			m_sx=sx;
			m_sy=sy;
        }
        void setTextureArea(float x0,float y0,float x1,float y1)
        {
            m_areax0=x0;
            m_areay0=y0;
            m_areax1=x1;
            m_areay1=y1;
        }


	protected:
        DsFrameImage();

	private:
        std::string m_id;
        DsImage* m_image;

		int m_width,m_height;

		float m_tx,m_ty;
		float m_sx,m_sy;
		float m_angle;

		float m_areax0,m_areay0;
		float m_areax1,m_areay1;
};

#endif /*_DS_FRAME_IMAGE_H_ */

