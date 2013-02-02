#ifndef MAIN_CC
#define MAIN_CC
#include <QApplication>
#include "ui/DsMainFrame.h"
#include "ui/DsQrcMacros.h"

#include "model/DsModel.h"
#include "operator/DsOperator.h"

#include <QDesktopWidget>


void initProject();
void createProjectDog();
void createProjectCat();

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWidget window;

    DsMainFrame main_frame;

    int x = 0;
    int y = 0;
    int screenWidth = 1;
    int screenHeight = 1;
    QDesktopWidget *desktop = QApplication::desktop();
    screenWidth = desktop->width();
    screenHeight = desktop->height();
    x = (screenWidth - 1024) / 2;
    y = (screenHeight - 800) / 2;

    main_frame.resize(1024,800);
    main_frame.move(x, y); // center the main_frame
    main_frame.setWindowTitle("FSprite Designer");
    main_frame.setWindowIcon(QIcon(DS_MS_WINDOW_ICON));
    main_frame.show();

    initProject();

    return app.exec();
}

void initProject()
{
    createProjectDog();
    createProjectCat();

    DsDataOperator& op=DsOperator::data;
    DsData::shareData()->emitSignal(DsData::SG_DATA_PROPERTY_CHANGE);

    op.setCurProject("cat");
    //op.setCurProject("Dog");
    op.setCurAnimation("jump");
    op.setCurFrameIndex(20);

}


void createProjectDog()
{
    DsSprite* sp=new DsSprite();

    DsAnimation* anim=new DsAnimation("jump");

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
    DsFrameImage* img_rarm1=DsFrameImage::create("rarm.png");
    img_rarm1->setPos(-200,0);

    img_rarm->setPos(200,0);

    DsFrameImage* f20_img1=DsFrameImage::create("rarm.png");
    f20_img1->setPos(200,0);
    f20_img1->setAngle(-300);

    DsFrameImage* f40_img1=DsFrameImage::create("rarm.png");
    f40_img1->setPos(300,0);


    frame10->pushFrameImage(img_body);
    frame10->pushFrameImage(img_rarm1);
    frame10->pushFrameImage(img_rarm);

    frame15->pushFrameImage(img_larm);
    frame20->pushFrameImage(f20_img1);

    frame40->pushFrameImage(f40_img1);

    anim->pushFrame(frame10);
    anim->pushFrame(frame15);
    anim->pushFrame(frame20);
    anim->pushFrame(frame21_39);
    anim->pushFrame(frame40);

    sp->addAnimation(anim);

    DsProject* project=new DsProject(sp,"Dog");
    DsData::shareData()->addProject(project);
}

void createProjectCat()
{
    DsSprite* sp=new DsSprite();
    DsAnimation* anim_jump=new DsAnimation("jump");
    DsAnimation* anim_run=new DsAnimation("run");
    DsAnimation* anim_dead=new DsAnimation("dead");
    sp->addAnimation(anim_jump);
    sp->addAnimation(anim_run);
    sp->addAnimation(anim_dead);

    DsProject* project=new DsProject(sp,"cat");
    DsData::shareData()->addProject(project);
}




#endif // MAIN_CC



















