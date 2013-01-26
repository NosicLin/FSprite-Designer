#ifndef _DS_FRAME_IMAGE_H_
#define _DS_FRAME_IMAGE_H_

#include <string>
#include <QPixmap>

class DsFrameImage
{
	public:
		static DsFrameImage* create(const std::string& img_name);

		~DsFrameImage();
	protected:
		DsFrameImage(const  std::string& name);

	private:
		std::string m_name;
		QPixmap* m_image;
		int m_texture;

		float m_tx,m_ty;
		float m_sx,m_sy;
		float m_angle;

		float m_areax0,m_areay0;
		float m_areax1,m_areay1;
};

#endif /*_DS_FRAME_IMAGE_H_ */

