#ifndef MAIN_CC
#define MAIN_CC
#include <QApplication>
#include "ui/DsMainFrame.h"
#include "ui/DsQrcMacros.h"

#include "model/DsModel.h"
#include "operator/DsOperator.h"


void initProject(DsProject* proj);
DsProject* createTestProject();

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWidget window;

    DsMainFrame main_frame;


    main_frame.resize(1024,800);
    main_frame.setWindowTitle("FSprite Designer");
    main_frame.setWindowIcon(QIcon(DS_MS_WINDOW_ICON));
    main_frame.show();

    DsProject* proj=createTestProject();
    initProject(proj);

    return app.exec();
}

void initProject(DsProject* proj)
{
    DsDataOperator& op=DsOperator::data;
    op.setCurProject(proj);
    op.setCurAnimation("jump");
    op.setCurFrame(0);
}


DsProject* createTestProject()
{
    DsSprite* sp=new DsSprite("TestSprite");

    DsAnimation* anim=new DsAnimation("jump");

    DsFrame* frame1=new DsFrame(0);

    DsFrame* frame10=new DsFrame(10);
    DsFrame* frame15=new DsFrame(15);
    DsFrame* frame20=new DsFrame(20);

    DsFrameImage* img_head=DsFrameImage::create("head.png");
    img_head->setPos(0,120);
    DsFrameImage* img_body=DsFrameImage::create("body.png");

    DsFrameImage* img_leg=DsFrameImage::create("leg.png");
    img_leg->setPos(0,-80);
    DsFrameImage* img_larm=DsFrameImage::create("larm.png");

    img_larm->setPos(-200,0);

    DsFrameImage* img_rarm=DsFrameImage::create("rarm.png");
    img_rarm->setPos(200,0);

    frame1->pushFrameImage(img_head);
    frame10->pushFrameImage(img_body);
    frame15->pushFrameImage(img_larm);
    frame20->pushFrameImage(img_rarm);

    anim->insertFrame(frame1);
    anim->insertFrame(frame15);
    anim->insertFrame(frame10);
    anim->insertFrame(frame20);


    sp->addAnimation(anim);
    DsProject* project=new DsProject(sp);
    return project;
}


#endif // MAIN_CC



















