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
        DsFrameImage* slerp(DsFrameImage* to,float t);
        DsFrameImage* clone();


		void getTextureArea(float* x0,float* y0, float* x1,float* y1)
		{
			*x0=m_areax0;
			*y0=m_areay0;
			*x1=m_areax1;
			*y1=m_areay1;
        }
        void getVertex(float* vx0,float* vy0,float* vx1,float* vy1);
        void transformVertexL(float* x,float* y);
        void transformVertexW(float* x,float* y);

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
        void setAlpha(float alpha)
        {
            m_alpha=alpha;
        }
        float getAlpha(){return  m_alpha;}
        void setOffset(float fx,float fy)
        {
            m_fx=fx;
            m_fy=fy;
        }
        float getOffsetX(){return m_fx;}
        float getOffsetY(){return m_fy;}



	protected:
        DsFrameImage();

	private:
        std::string m_id;
        DsImage* m_image;

		int m_width,m_height;

        /* transform */
		float m_tx,m_ty;
		float m_sx,m_sy;
		float m_angle;

        /* texture area */
		float m_areax0,m_areay0;
        float m_areax1,m_areay1;

        /* alpha */
        float m_alpha;

        /* offset */
        float m_fx,m_fy;

};
#endif /*_DS_FRAME_IMAGE_H_ */





