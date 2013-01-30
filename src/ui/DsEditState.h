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
            DIRECTION_BOTH
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
    private:
		DsImage* image;
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
		float startx,starty;
		float newx,newy;
		int direction;
};


class DsEditStateRotate:public DsEditState 
{
	public:
		float startx,starty;
		float newx,newy;
};


class DsEditStateSelect :public DsEditState 
{
	public:
        virtual void mousePressEvent(QMouseEvent* event);
        virtual void keyPressEvent(QKeyEvent* event);
        void draw();

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

