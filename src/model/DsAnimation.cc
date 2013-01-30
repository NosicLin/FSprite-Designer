
#include <assert.h>


#include "DsAnimation.h"
#include "DsFrame.h"
#include "util/DsDebug.h"
int DsAnimation::m_defaulFps=10;

DsAnimation::DsAnimation(const std::string& name)
{
	m_name=name;
	m_fps=m_defaulFps;
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
	insertFrameTypeKey(index,false);
}
void DsAnimation::insertEmptyKeyFrame(int index)
{
	insertFrameTypeKey(index,true);
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

void DsAnimation::insertFrameTypeKey(int index,bool empty)
{
	int keypos=toKeyFramePos(index);
	if(keypos==-1)
	{
		DsFrame* insert_frame=new DsKeyFrame(index);
		rawInsertFrame(insert_frame);
		return;
	}

	DsFrame* orign=m_keyFrames[keypos];
    if(orign->getType()==DsFrame::FRAME_KEY)
	{
		DsKeyFrame* insert_frame=NULL;

		/*     _          */
		/* ... K _ _  K   */
		if(orign->getFrameId()==index)
		{
			insert_frame=(DsKeyFrame*)orign;
			if(empty)
			{
                insert_frame->clearFrameImage();
			}
			else 
			{
				/* nothing */
			}
		}
		else   /*        _       */
		{      /* ...K _ _ _ K   */ 
			if(empty)
			{
				insert_frame=new DsKeyFrame(index);
			}
			else 
			{
                insert_frame=((DsKeyFrame*)orign)->clone();
				insert_frame->setFrameId(index);
			}
            rawInsertFrame(insert_frame);
		}

	}
	else 
	{
		DsTweenFrame* ftween=(DsTweenFrame*)orign;
        DsKeyFrame* prev=ftween->getFromKeyFrame();
        DsKeyFrame* next=ftween->getToKeyFrame();
		DsKeyFrame* insert_frame=NULL;

        if(ftween->getFrameId()==index)
		{
			/*   _       */
			/* K T K _ _ */
			if(next->getFrameId()==index+1)
			{
				if(empty)
				{
					insert_frame=new DsKeyFrame(index);
				}
				else 
				{
					insert_frame=ftween->slerpToKeyFrame(index);
				}
				rawInsertFrame(insert_frame);
			} 
			/*   _           */
			/* K T _ _ K _ _ */
			else 
			{
				if(empty)
				{
					insert_frame=new DsKeyFrame(index);
				}
				else 
				{
					insert_frame=ftween->slerpToKeyFrame(index);
				}
				ftween->setFrameId(index+1);
				ftween->setFromKeyFrame(insert_frame);
				rawInsertFrame(insert_frame);
			}
		}
		else  
		{    
            DsFrame* next_insert=getFrame(index+1);
			assert(next_insert);
			if(empty)
			{
				insert_frame=new DsKeyFrame(index);
			}
			else 
			{
				insert_frame=ftween->slerpToKeyFrame(index);
			}

			/*       _     */
			/* K T _ _ _ K */
			if(next_insert==ftween)
            {

                DsDebug<<"next_insert"<<endl;
                DsTweenFrame* next_tween=new DsTweenFrame(
                            insert_frame,
                            ftween->getToKeyFrame(),
                            index+1
                            );

				next_tween->setFrameId(index+1);
				rawInsertFrame(next_tween);

				ftween->setToKeyFrame(insert_frame);
				rawInsertFrame(insert_frame);
			}

			/*         _   */
			/* K T _ _ _ K */
			else 
			{
				ftween->setToKeyFrame(insert_frame);
				rawInsertFrame(insert_frame);
			}

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
	return m_keyFrames[m_keyFrames.size()-1]->getFrameId()+1;
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





















