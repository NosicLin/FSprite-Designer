
#include <assert.h>
#include "util/DsUtil.h"
#include "DsAnimation.h"
#include "DsFrame.h"
#include "util/DsDebug.h"

int DsAnimation::m_defaulFps=30;
DsAnimation::DsAnimation(const std::string& name)
{
    m_id=DsUtil::uniqueStringID();
    m_name=name;
    m_fps=m_defaulFps;
}

DsAnimation* DsAnimation::createWithFirstFrame(const std::string& name)
{
    DsAnimation* ret=new DsAnimation(name);
    DsKeyFrame* zero=new DsKeyFrame(0);
    ret->pushFrame(zero);
    return ret;
}


DsAnimation::~DsAnimation()
{
    Iterator iter;
    for(iter=m_keyFrames.begin();iter!=m_keyFrames.end();++iter)
    {
        delete *iter;
    }
    m_keyFrames.clear();
}

DsFrame* DsAnimation::getFrame(int index)
{
    int keyid=toKeyFramePos(index);
    if(keyid==-1)
    {
        return NULL;
    }
    assert(keyid>=0&&keyid<m_keyFrames.size());
    return m_keyFrames[keyid];
}

void DsAnimation::pushFrame(DsFrame* frame)
{

    if(m_keyFrames.size()!=0)
    {
        /*      _ */
        /* .. k t */
        DsFrame* last_frame=m_keyFrames[m_keyFrames.size()-1];
        if(frame->getType()==DsFrame::FRAME_TWEEN)
        {
            assert(last_frame->getType()==DsFrame::FRAME_KEY);
            ((DsTweenFrame*)frame)->setFromKeyFrame((DsKeyFrame*)last_frame);
        }
        /*      _ */
        /* .. t k */
        else
        {
            if(last_frame->getType()==DsFrame::FRAME_TWEEN)
            {
                ((DsTweenFrame*)last_frame)->setToKeyFrame((DsKeyFrame*)frame);
            }
        }
    }
    m_keyFrames.push_back(frame);
}

void DsAnimation::insertKeyFrame(int index)
{
    int keypos=toKeyFramePos(index);
    DsKeyFrame* insert=NULL;
    if(keypos==-1)
    {
        insert=new DsKeyFrame(index);
    }
    else
    {
        DsFrame* origin=m_keyFrames[keypos];
        if(origin->getType()==DsFrame::FRAME_KEY)
        {
            insert=((DsKeyFrame*)origin)->clone();
        }
        else
        {
            insert=((DsTweenFrame*)origin)->slerpToKeyFrame(index);
        }
    }
    rawInsertKeyFrame(index,insert);

}
void DsAnimation::insertEmptyKeyFrame(int index)
{
    DsKeyFrame* keyframe=new DsKeyFrame(index);
    rawInsertKeyFrame(index,keyframe);
}

void DsAnimation::insertTween(int index)
{
    int keyid=toKeyFramePos(index);

    assert(keyid>=0);
    assert(m_keyFrames[keyid]->getFrameId()<index);
    assert(keyid<m_keyFrames.size()-1);
    assert(m_keyFrames[keyid+1]->getType()==DsFrame::FRAME_KEY);
    assert(m_keyFrames[keyid]->getType()==DsFrame::FRAME_KEY);

    DsTweenFrame* tween=new DsTweenFrame(
                (DsKeyFrame*)m_keyFrames[keyid],
                (DsKeyFrame*)m_keyFrames[keyid+1],
                m_keyFrames[keyid]->getFrameId()+1
                );
    rawInsertFrame(tween);
}
void DsAnimation::removeTween(int index)
{
    int keyid=toKeyFramePos(index);
    assert(keyid>0);
    assert(m_keyFrames[keyid]->getType()==DsFrame::FRAME_TWEEN);
    assert(keyid<m_keyFrames.size()-1);
    assert(m_keyFrames[keyid+1]->getType()==DsFrame::FRAME_KEY);
    assert(m_keyFrames[keyid-1]->getType()==DsFrame::FRAME_KEY);
    rawRemoveFrame(m_keyFrames[keyid]);
}

void DsAnimation::removeKeyFrame(int index)
{
    int keyid=toKeyFramePos(index);

    assert(keyid!=-1); /* no frame to remove */
    assert(m_keyFrames[keyid]->getFrameId()==index);

    DsFrame* remove_frame=NULL;

    /* _ */
    /* k */
    if(m_keyFrames.size()==1)
    {
        remove_frame=m_keyFrames[0];
        rawRemoveFrame(remove_frame);
    }
    /* _           */
    /* k (t|k) ... */
    else  if(keyid==0)
    {
        remove_frame=m_keyFrames[0];
        DsFrame* next=m_keyFrames[1];

        assert(remove_frame->getType()==DsFrame::FRAME_KEY);
        /* _       */
        /* k t ... */
        if(next->getType()==DsFrame::FRAME_TWEEN)
        {
            rawRemoveFrame(remove_frame);
            rawRemoveFrame(next);
        }
        /* _       */
        /* k k ... */
        else
        {
            rawRemoveFrame(remove_frame);
        }
    }

    /*           _  */
    /* ... (t|k) k  */
    else if(keyid==m_keyFrames.size()-1)
    {
        remove_frame=m_keyFrames[keyid];
        DsFrame* prev_frame=m_keyFrames[keyid-1];
        assert(remove_frame->getType()==DsFrame::FRAME_KEY);

        /*       _  */
        /* ... t k  */
        if(prev_frame->getType()==DsFrame::FRAME_TWEEN)
        {
            rawRemoveFrame(remove_frame);
            rawRemoveFrame(prev_frame);
        }

        /*       _ */
        /* ... k k */
        else
        {
            rawRemoveFrame(remove_frame);
        }
    }
    /*            _           */
    /* ...(t|k) (t|k)  (t|k)  */
    else
    {
        remove_frame=m_keyFrames[keyid];
        /*          _        */
        /* ...(t|k) k (t|k)  */
        if(remove_frame->getType()==DsFrame::FRAME_KEY)
        {
            DsFrame* prev=m_keyFrames[keyid-1];
            DsFrame* next=m_keyFrames[keyid+1];

            /*        _    */
            /* ...k t k k  */
            if((prev->getType()==DsFrame::FRAME_TWEEN)
                    &&(next->getType()==DsFrame::FRAME_KEY))
            {
                rawRemoveFrame(remove_frame);
                rawRemoveFrame(prev);
            }

            /*      _      */
            /* ...k k t k  */
            else if((prev->getType()==DsFrame::FRAME_KEY)
                    &&(next->getType()==DsFrame::FRAME_TWEEN))
            {
                DsDebug<<"Heresss"<<endl;
                rawRemoveFrame(remove_frame);
                rawRemoveFrame(next);
            }
            /*        _      */
            /* ...k t k t k  */
            else if((prev->getType()==DsFrame::FRAME_TWEEN)
                    &&(next->getType()==DsFrame::FRAME_TWEEN))
            {
                ((DsTweenFrame*)prev)->setToKeyFrame(
                            ((DsTweenFrame*)next)->getToKeyFrame());
                rawRemoveFrame(remove_frame);
                rawRemoveFrame(next);
            }
            /*      _    */
            /* ...k k k  */
            else
            {
                rawRemoveFrame(remove_frame);
            }
        }
        /*      _    */
        /* ...k t k  */
        else
        {
            rawRemoveFrame(remove_frame);
        }
    }

}


int DsAnimation::toKeyFramePos(int index)
{
    int pos=-1;
    for(int i=0;i<m_keyFrames.size();i++)
    {
        int frameid=m_keyFrames[i]->getFrameId();
        if(frameid==index)
        {
            return i;
        }
        if(frameid>index)
        {
            return pos;
        }
        pos=i;
    }
    return pos;
}

int DsAnimation::getFrameNu()
{
    if(m_keyFrames.size()==0)
    {
        return 0;
    }
    else
    {
        return m_keyFrames[m_keyFrames.size()-1]->getFrameId()+1;
    }
}

void DsAnimation::rawInsertFrame(DsFrame* frame)
{
    int keypos=toKeyFramePos(frame->getFrameId());
    if(keypos==-1)
    {
        m_keyFrames.insert(m_keyFrames.begin(),frame);
    }
    else if(m_keyFrames[keypos]->getFrameId()==frame->getFrameId())
    {
        delete m_keyFrames[keypos];
        m_keyFrames[keypos]=frame;
    }
    else
    {
        m_keyFrames.insert(m_keyFrames.begin()+keypos+1,frame);
    }
}

void DsAnimation::rawRemoveFrame(DsFrame* frame)
{
    Iterator iter=m_keyFrames.begin();
    for(;iter!=m_keyFrames.end();++iter)
    {
        if(*iter==frame)
        {
            delete *iter;
            m_keyFrames.erase(iter);
            return;
        }
    }
    assert(0);
}

void DsAnimation::rawInsertKeyFrame(int index,DsKeyFrame* keyframe)
{
    keyframe->setFrameId(index);
    int keypos=toKeyFramePos(index);

    if(keypos==-1)
    {
        rawInsertFrame(keyframe);
        return ;
    }

    /* _ */
    /* K */
    if(m_keyFrames.size()==1)
    {
        rawInsertFrame(keyframe);
        return;
    }

    /* _            */
    /* k (t|k) ...  */
    else if(keypos==0)
    {
        assert(m_keyFrames[keypos]->getType()==DsFrame::FRAME_KEY);
        DsFrame* next=m_keyFrames[1];

        if(next->getType()==DsFrame::FRAME_TWEEN)
        {
            ((DsTweenFrame*) next)->setFromKeyFrame(keyframe);
        }
        rawInsertFrame(keyframe);
    }

    /*           _ */
    /* ... (t|k) k */
    else if(keypos==m_keyFrames.size()-1)
    {
        /*           _ */
        /* ... (t|k) k */
        if(m_keyFrames[keypos]->getFrameId()==index)
        {
            assert(m_keyFrames[keypos]->getType()==DsFrame::FRAME_KEY);
            DsFrame* prev_frame=m_keyFrames[keypos-1];
            if(prev_frame->getType()==DsFrame::FRAME_TWEEN)
            {
                ((DsTweenFrame*)prev_frame)->setToKeyFrame(keyframe);
            }
        }
        rawInsertFrame(keyframe);

    }

    /*               _              */
    /*  ... (t|k)  (t|k)  (t|k)     */

    else
    {
        DsFrame* origin=m_keyFrames[keypos];
        DsFrame* prev=m_keyFrames[keypos-1];
        DsFrame* next=m_keyFrames[keypos+1];
        if(origin->getFrameId()==index)
        {
            /*             _             */
            /*  ... (t|k)  k   (t|k)   */
            if(origin->getType()==DsFrame::FRAME_KEY)
            {
                if(prev->getType()==DsFrame::FRAME_TWEEN)
                {
                    ((DsTweenFrame*)prev)->setToKeyFrame(keyframe);
                }
                if(next->getType()==DsFrame::FRAME_TWEEN)
                {
                    ((DsTweenFrame*)next)->setFromKeyFrame(keyframe);
                }
                rawInsertFrame(keyframe);
            }

            /*              _   */
            /*  ... k t _ _ k   */
            else
            {
                /*       _     */
                /* ... k t k   */
                if(next->getFrameId()==index+1)
                {
                    rawInsertFrame(keyframe);
                }
                /*       _       */
                /* ... k t _ _ k */
                else
                {
                    origin->setFrameId(index+1);
                    ((DsTweenFrame*)origin)->setFromKeyFrame(keyframe);
                    rawInsertFrame(keyframe);
                }
            }
        }
        else
        {
            /*                _           */
            /*  ... (t|k)  k  _ _ _ k     */
            if(origin->getType()==DsFrame::FRAME_KEY)
            {
                rawInsertFrame(keyframe);
            }
            /*                 _           */
            /*  ... (t|k)  t _ _ _ _ k     */
            else
            {
                DsTweenFrame* ftween=(DsTweenFrame*)origin;
                DsKeyFrame* tween_to=ftween->getToKeyFrame();
                /*                     _       */
                /*  ... (t|k)  t _ _ _ _ k     */
                if(tween_to->getFrameId()==index+1)
                {
                    ftween->setToKeyFrame(keyframe);
                    rawInsertFrame(keyframe);
                }
                /*                   _         */
                /*  ... (t|k)  t _ _ _ _ k     */
                else
                {
                    ftween->setToKeyFrame(keyframe);
                    DsTweenFrame* next_tween=new DsTweenFrame(
                                keyframe,
                                tween_to,
                                index+1);
                    rawInsertFrame(keyframe);
                    rawInsertFrame(next_tween);
                }
            }
        }
    }
}

void DsAnimation::insertKeyFrame(int index,DsKeyFrame* frame)
{
    rawInsertKeyFrame(index,frame);
}




































