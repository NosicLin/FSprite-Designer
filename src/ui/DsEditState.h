#ifndef _DS_EDIT_STATE_H_
#define _DS_EDIT_STATE_H_

class QMouseEvent;
class QKeyEvent;
class DsEditView;

#include "model/DsModel.h"

class DsEditState 
{
    public:
        enum
        {
            DIRECTION_X,
            DIRECTION_Y,
            DIRECTION_BOTH,
            DIRECTION_A,
            DIRECTION_B
      //      DIRECTION_NONE,
        };
	public:
		enum
		{
			ST_IDEL,
			ST_NOT_EDIT,
			ST_ADD_IMAGE,
			ST_SELECT,
			ST_SCALE,
			ST_TRANSLATE,
			ST_ROTATE,
			ST_PLAY,
			ST_MOVE_COORD
		};
	public:
		virtual void onEnter(DsEditState* prev);
		virtual void onExit(DsEditState* next);
		virtual void mouseMoveEvent(QMouseEvent* event);
		virtual void mousePressEvent(QMouseEvent* event);
		virtual void mouseReleaseEvent(QMouseEvent* event);
        virtual void wheelEvent(QMouseEvent* event);

        virtual void enterEvent(QEvent* event);
        virtual void leaveEvent(QEvent* event);


		virtual void keyPressEvent(QKeyEvent* event);
		virtual void keyReleaseEvent(QKeyEvent* event);
		virtual int getType(){return m_type;}
		virtual void draw();


		//virtual void onExit(DsEditState* next);
		void setEditView(DsEditView* view)
		{
			m_editView=view;
		}

	protected:
		int m_type;
		DsEditView* m_editView;
};
class DsEditStateNotEdit:public DsEditState 
{
	public:
		DsEditStateNotEdit();
	public:
        virtual void onEnter(DsEditState* prev);
        virtual void onExit(DsEditState* next);
        virtual void draw();
    private:
        QCursor m_prev;
};

class DsEditStateIdel:public DsEditState 
{
	public: 
		DsEditStateIdel();
		virtual void mousePressEvent(QMouseEvent* event);
		virtual void draw();
};



class DsEditStateAddImage:public DsEditState 
{
    public:
        DsEditStateAddImage();
        void setFrameImage(DsFrameImage* img){m_image=img;}

    public:
        virtual void onEnter(DsEditState* );
        virtual void mouseMoveEvent(QMouseEvent* event);
        virtual void enterEvent(QEvent* );
        virtual void leaveEvent(QEvent* );
        virtual void mousePressEvent(QMouseEvent* event);
        virtual void keyPressEvent(QKeyEvent* event);

        virtual void draw();

    private:
        DsFrameImage* m_image;
        bool m_draw;
};



class DsEditStateTranslate:public DsEditState
{
    public:
        DsEditStateTranslate();
    public:
        virtual void onEnter(DsEditState* prev);

        virtual void mouseMoveEvent(QMouseEvent* event);
        virtual void mousePressEvent(QMouseEvent* event);
        virtual void keyPressEvent(QKeyEvent* event);
        virtual void draw();

    private:
        float m_movex,m_movey;
        int m_direction;
};


class DsEditStateScale :public DsEditState
{
    public:
        DsEditStateScale();
    public:
        virtual void onEnter(DsEditState* prev);

        virtual void mouseMoveEvent(QMouseEvent* event);
        virtual void mousePressEvent(QMouseEvent* event);
        virtual void keyPressEvent(QKeyEvent* event);
        virtual void draw();
	protected:
		float getScale();
    public:
        float m_startx,m_starty;
        float m_nowx,m_nowy;
        int m_direction;
};


class DsEditStateRotate:public DsEditState 
{
public:
    DsEditStateRotate();
public:
    virtual void onEnter(DsEditState* prev);
    virtual void mouseMoveEvent(QMouseEvent* event);
    virtual void mousePressEvent(QMouseEvent* event);
    virtual void keyPressEvent(QKeyEvent* event);
    virtual void draw();
private:
    float m_angle;
};

class DsEditStateMoveOffset:public DsEditState
{
    public:
        DsEditStateMoveOffset();
    public:
        virtual void onEnter(DsEditState* prev);
        virtual void mouseMoveEvent(QMouseEvent* event);
        virtual void mousePressEvent(QMouseEvent* event);
        virtual void draw();

    private:
        float m_movex;
        float m_movey;

};


class DsEditStateSelect :public DsEditState 
{
public:
    DsEditStateSelect();
public:
    virtual void mousePressEvent(QMouseEvent* event);
    virtual void keyPressEvent(QKeyEvent* event);
    void draw();
};

class DsEditStateTextureArea:public DsEditState
{
    public:
        DsEditStateTextureArea();
    public:
        virtual void onEnter(DsEditState* prev);
        virtual void mouseMoveEvent(QMouseEvent* event);
        virtual void mousePressEvent(QMouseEvent* event);
        virtual void keyPressEvent(QKeyEvent* event);
        virtual void draw();
    private:
        float m_movevx0,m_movevy0;
        float m_movevx1,m_movevy1;
        int m_direction;
};



class DsEditStatePlay:public DsEditState
{
public:
    int curframe;
    int elapse;
};

class DSEditStateMoveCoord:public DsEditState 
{
public:
};


#endif /*_DS_EDIT_STATE_H_*/
















