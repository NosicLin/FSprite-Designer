#include <assert.h>

#include "util/DsDebug.h"
#include "DsProject.h"
#include "DsSprite.h"
#include "DsAnimation.h"
#include "DsFrame.h"
#include "DsFrameImage.h"


DsProject::DsSpriteInfo::DsSpriteInfo(DsSprite* sprite)
{
    DsSpriteState* state=new DsSpriteState(sprite,NULL,NULL,-1);
    m_queue.push(state);
	m_copyFrameImage=NULL;
    m_copyFrame=NULL;
    m_curStateIndex=0;
}

DsProject::DsSpriteInfo::~DsSpriteInfo()
{
    delete m_copyFrameImage;
    delete m_copyFrame;
}

void DsProject::DsSpriteInfo::setCurAnimation(const std::string& id)
{
    DsSpriteState* state=m_queue.get(m_curStateIndex);

    state->m_curAnimation=state->m_sprite->getAnimation(id);
    assert(state->m_curAnimation);

    if(state->m_curAnimation->getFrameNu()>0)
    {
        state->m_curFrameIndex=0;
    }
    else
    {
        state->m_curFrameIndex=-1;
    }
    state->m_curFrameImage=NULL;
}


void DsProject::DsSpriteInfo::setCurFrameIndex(int frame)
{
    DsSpriteState* state=m_queue.get(m_curStateIndex);
    if(!state->m_curAnimation)
    {
        return;
    }

    state->m_curFrameIndex=frame;
    state->m_curFrameImage=NULL;
}

void DsProject::DsSpriteInfo::setCurFrameImage(const std::string& id)
{
    DsSpriteState* state=m_queue.get(m_curStateIndex);
    if(state->m_curFrameIndex==-1)
    {
        return;
    }
    DsFrame* frame=state->m_curAnimation->getFrame(state->m_curFrameIndex);

    assert(frame);
    assert(frame->getType()==DsFrame::FRAME_KEY);
    state->m_curFrameImage=((DsKeyFrame*)frame)->getFrameImage(id);
    assert(state->m_curFrameImage);
}


void DsProject::DsSpriteInfo::dropCurAnimation()
{
    DsSpriteState* state=m_queue.get(m_curStateIndex);
    state->m_curAnimation=NULL;
    state->m_curFrameIndex=-1;
    state->m_curFrameImage=NULL;
}



void DsProject::DsSpriteInfo::dropCurFrameIndex()
{
    DsSpriteState* state=m_queue.get(m_curStateIndex);
    state->m_curFrameIndex=-1;
    state->m_curFrameImage=NULL;
}

void DsProject::DsSpriteInfo::dropCurFrameImage()
{
    DsSpriteState* state=m_queue.get(m_curStateIndex);
    state->m_curFrameImage=NULL;
}

DsFrame* DsProject::DsSpriteInfo::getCurFrame()
{
    DsSpriteState* state=m_queue.get(m_curStateIndex);
    if(!state->m_curAnimation)
    {
        return NULL;
    }
    if(state->m_curFrameIndex==-1)
    {
        return NULL;
    }
    return state->m_curAnimation->getFrame(state->m_curFrameIndex);
}

DsAnimation* DsProject::DsSpriteInfo::getCurAnimation()
{
    DsSpriteState* state=m_queue.get(m_curStateIndex);
    return state->m_curAnimation;
}

DsFrameImage* DsProject::DsSpriteInfo::getCurFrameImage()
{
    DsSpriteState* state=m_queue.get(m_curStateIndex);
    return state->m_curFrameImage;
}

int DsProject::DsSpriteInfo::getCurFrameIndex()
{
    DsSpriteState* state=m_queue.get(m_curStateIndex);
    return state->m_curFrameIndex;
}

void DsProject::DsSpriteInfo::setCopyFrameImage(DsFrameImage* image)
{
    if(m_copyFrameImage)
    {
        delete m_copyFrameImage;
    }
    m_copyFrameImage=image;
}
void DsProject::DsSpriteInfo::setCopyFrame(DsKeyFrame* frame)
{
    if(m_copyFrame)
    {
        delete m_copyFrame;
    }
    m_copyFrame=frame;
}




DsProject::DsProject()
{
    m_curSprite=NULL;
}

DsProject::~DsProject()
{
    for(int i=0;i<m_sprites.size();i++)
    {
        delete m_sprites[i];
    }
    m_sprites.clear();
}

DsSprite* DsProject::getCurSprite()
{
    if(m_curSprite)
    {
        return m_curSprite->getSprite();
    }
    return NULL;
}


void DsProject::setCurSprite(const std::string& id)
{
    for(int i=0;i<m_sprites.size();i++)
    {
        if(m_sprites[i]->getSprite()->getID()==id)
        {
            m_curSprite=m_sprites[i];
            return;
        }
    }
    assert(0); /*never reach here */
}

DsAnimation* DsProject::getCurAnimation()
{
    if(m_curSprite)
    {
        return m_curSprite->getCurAnimation();
    }
    return NULL;
}

void DsProject::setCurAnimation(const std::string& id)
{
    if(m_curSprite)
    {
        m_curSprite->setCurAnimation(id);
    }
}
void DsProject::dropCurAnimation()
{
    if(m_curSprite)
    {
        m_curSprite->dropCurAnimation();
    }
}

DsFrame* DsProject::getCurFrame()
{
    if(m_curSprite)
    {
        return m_curSprite->getCurFrame();
    }
    return NULL;
}

int DsProject::getCurFrameIndex()
{
    if(m_curSprite)
    {
        return m_curSprite->getCurFrameIndex();
    }
    return -1;
}
void DsProject::setCurFrameIndex(int index)
{
    if(m_curSprite)
    {
        m_curSprite->setCurFrameIndex(index);
    }
}
void DsProject::dropCurFrameIndex()
{
    if(m_curSprite)
    {
        m_curSprite->dropCurFrameIndex();
    }
}


DsFrameImage* DsProject::getCurFrameImage()
{
    if(m_curSprite)
    {
        return m_curSprite->getCurFrameImage();
    }
    return NULL;
}

void DsProject::setCurFrameImage(const std::string& id)
{
    if(m_curSprite)
    {
        return m_curSprite->setCurFrameImage(id);
    }
}

void DsProject::dropCurFrameImage()
{
    if(m_curSprite)
    {
        m_curSprite->dropCurFrameImage();
    }
}


DsSprite* DsProject::getSprite(int index)
{
    assert(index>=0&&index<m_sprites.size());
    return m_sprites[index]->getSprite();
}

DsSprite* DsProject::getSprite(const std::string& id)
{
    for(unsigned int i=0;i<m_sprites.size();i++)
    {
        if(m_sprites[i]->getSprite()->getID()==id)
        {
            return m_sprites[i]->getSprite();
        }
    }
    assert(0); /*never reach here */
    return NULL;
}
void DsProject::removeSprite(const std::string& id)
{
    std::vector<DsSpriteInfo*>::iterator iter;
    for(iter=m_sprites.begin();iter!=m_sprites.end();++iter)
    {
        if((*iter)->getSprite()->getID()==id)
        {
            if(m_curSprite==*iter)
            {
                m_curSprite=NULL;
            }
            m_sprites.erase(iter);
            return;
        }
    }
    assert(0); /*never reach here */
}


void DsProject::addSprite(DsSprite* sprite)
{
    m_sprites.push_back(new DsSpriteInfo(sprite));
}

bool DsProject::hasSpriteWithName(const std::string& name)
{
    for(unsigned int i=0;i<m_sprites.size();i++)
    {
        if(m_sprites[i]->getSprite()->getName()==name)
        {
            return true;
        }
    }
    return false;
}


DsProject::DsSpriteState::DsSpriteState(DsSprite* sprite,
                                        DsAnimation* cur_animation,
                                        DsFrameImage* cur_frameimg,
                                        int frame_index)
{
    m_sprite=sprite;
    m_curAnimation=cur_animation;
    m_curFrameImage=cur_frameimg;
    m_curFrameIndex=frame_index;
}
DsProject::DsSpriteState::~DsSpriteState()
{
    delete m_sprite;
}

void DsProject::DsSpriteInfo::pushState()
{
    DsDebug<<"pushState"<<endl;
    DsSpriteState* state=m_queue.get(m_curStateIndex);

    DsSprite* sprite=state->m_sprite->clone(true);

    int frame_index=state->m_curFrameIndex;

    DsSpriteState* save=new DsSpriteState(sprite,NULL,NULL,-1);

    if(m_curStateIndex<m_queue.size()-1)
    {
        m_queue.dropTail(m_queue.size()-m_curStateIndex-1);
    }

    m_queue.pushFrontTail(save);
    m_curStateIndex++;
    if(state->m_curAnimation)
    {
        save->m_curAnimation=save->m_sprite->getAnimation(state->m_curAnimation->getID());
    }
    state->m_curFrameIndex=frame_index;
    if(state->m_curFrameImage)
    {
        DsFrame* frame=save->m_curAnimation->getFrame(frame_index);
        assert(frame);
        save->m_curFrameImage=((DsKeyFrame*)frame)->getFrameImage(
                    state->m_curFrameImage->getID());
    }

}

void DsProject::DsSpriteInfo::redo()
{
    if(m_curStateIndex<m_queue.size()-1)
    {
        m_curStateIndex++;
    }
}
void DsProject::DsSpriteInfo::undo()
{
    if(m_curStateIndex>0)
    {
        m_curStateIndex--;
    }
}





DsProject::CircleQueue::CircleQueue()
{
    for(int i=0;i<DS_DEFAULT_UNDO_SIZE;i++)
    {
       m_queue[i]=NULL;
    }
    m_used=0;
    m_begin=0;
}
DsProject::CircleQueue::~CircleQueue()
{
    for(int i=0;i<m_used;i++)
    {
        int pos=(i+m_begin)%DS_DEFAULT_UNDO_SIZE;
        delete m_queue[pos];
    }
}
void DsProject::CircleQueue::push(DsSpriteState* state)
{
    if(m_used==DS_DEFAULT_UNDO_SIZE)
    {
        delete m_queue[m_begin];
        m_queue[m_begin]=state;

        m_begin=(m_begin+1)%DS_DEFAULT_UNDO_SIZE;
    }
    else
    {
        int pos=(m_begin+m_used)%DS_DEFAULT_UNDO_SIZE;
        m_queue[pos]=state;
        m_used++;
    }
}
void DsProject::CircleQueue::pushFrontTail(DsSpriteState* state)
{
    if(m_used==DS_DEFAULT_UNDO_SIZE)
    {
        int insert_pos=(m_begin-1)%DS_DEFAULT_UNDO_SIZE;
        delete m_queue[m_begin];
        m_queue[m_begin]=m_queue[insert_pos];
        m_queue[insert_pos]=state;
        m_begin=(m_begin+1)%DS_DEFAULT_UNDO_SIZE;
    }
    else if(m_used==0)
    {
        m_queue[m_begin%DS_DEFAULT_UNDO_SIZE]=state;
        m_used++;
    }
    else
    {
        int tail_pos=(m_begin+m_used)%DS_DEFAULT_UNDO_SIZE;
        int insert_pos=(m_begin+m_used-1)%DS_DEFAULT_UNDO_SIZE;

        m_queue[tail_pos]=m_queue[insert_pos];
        m_queue[insert_pos]=state;
        m_used++;
    }
}

DsProject::DsSpriteState* DsProject::CircleQueue::get(int i)
{
    DsDebug<<"index:"<<i<<endl;
    assert((i>=0)&&(i<m_used));
    int pos=(m_begin+i)%DS_DEFAULT_UNDO_SIZE;
    return m_queue[pos];
}

int DsProject::CircleQueue::size()
{
    return m_used;
}
bool DsProject::CircleQueue::full()
{
    return m_used==DS_DEFAULT_UNDO_SIZE;
}

bool DsProject::CircleQueue::empty()
{
    return m_used==0;
}

void DsProject::CircleQueue::dropTail(int nu)
{
    while(nu--)
    {
        int pos=(m_begin+m_used-1)%DS_DEFAULT_UNDO_SIZE;
        delete m_queue[pos];
        m_used--;
    }
}
DsSprite* DsProject::DsSpriteInfo::getSprite()
{
    DsSpriteState* state=m_queue.get(m_curStateIndex);
    return state->m_sprite;
}























































































