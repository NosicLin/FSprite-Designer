#ifndef _DS_EDIT_STATE_H_
#define _DS_EDIT_STATE_H_

class QMouseEvent;
class QKeyEvent;
class DsEditView;

#include "model/DsModel.h"

class DsEditState 
{
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
		DsImage* image;
};

class DsEditStateTranslate:public DsEditState
{
	public:
		float startx,starty;
		float newx,newy;
		int direction;
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
        void mousePressEvent(QMouseEvent* event);
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

