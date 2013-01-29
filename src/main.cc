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
    op.setCurFrameIndex(20);

}


DsProject* createTestProject()
{
    DsSprite* sp=new DsSprite("TestSprite");

    DsAnimation* anim=new DsAnimation("jump");

    DsKeyFrame* frame1=new DsKeyFrame(0);
    DsKeyFrame* frame10=new DsKeyFrame(10);
    DsKeyFrame* frame15=new DsKeyFrame(15);
    DsKeyFrame* frame20=new DsKeyFrame(20);
    DsTweenFrame* frame21_39= new DsTweenFrame(NULL,NULL,21);
    DsKeyFrame* frame40=new DsKeyFrame(40);

    DsFrameImage* img_head=DsFrameImage::create("head.png");
    img_head->setPos(0,120);
    DsFrameImage* img_body=DsFrameImage::create("body.png");

    DsFrameImage* img_leg=DsFrameImage::create("leg.png");
    img_leg->setPos(0,-80);
    DsFrameImage* img_larm=DsFrameImage::create("larm.png");

    img_larm->setPos(-200,0);

    DsFrameImage* img_rarm=DsFrameImage::create("rarm.png");

    img_rarm->setPos(200,0);

    DsFrameImage* f20_img1=DsFrameImage::create("rarm.png");
    f20_img1->setPos(200,0);
    f20_img1->setAngle(-300);
    DsFrameImage* f40_img1=DsFrameImage::create("rarm.png");
    f40_img1->setPos(300,0);


    //frame0->pushFrameImage(img_head);
    frame10->pushFrameImage(img_body);
    frame15->pushFrameImage(img_larm);
    frame20->pushFrameImage(f20_img1);

    frame40->pushFrameImage(f40_img1);

    //anim->pushFrame(frame0);
    anim->pushFrame(frame10);
    anim->pushFrame(frame15);
    anim->pushFrame(frame20);
    anim->pushFrame(frame21_39);
    anim->pushFrame(frame40);

    sp->addAnimation(anim);

    DsProject* project=new DsProject(sp);
    return project;
}


#endif // MAIN_CC



















