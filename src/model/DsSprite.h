#ifndef _DS_SPRITE_H_
#define _DS_SPRITE_H_

#include <string>


#include "DsFrame.h"
#include "DsFrameImage.h"

class DsAnimation;

class DsSprite
{
	public:
		typedef std::vector<DsAnimation*>::iterator Iterator;

    public:
        DsSprite();
        DsSprite(const std::string& name);
	public:  
        std::string getID(){return m_id;}
        void setID(const std::string& id){m_id=id;}
        std::string getName(){return m_name;}
        void setName(const std::string& name){m_name=name;}

    public:
        void addAnimation(DsAnimation* anim);
		void removeAnimation(const std::string& name);

        DsAnimation* getAnimation(const std::string& id);
        DsAnimation* getAnimationWithName(const std::string& name);
        DsAnimation* getAnimation(int index);

        int getAnimationNu(){return m_animations.size();}
        bool hasAnimationWithName(const std::string& name);

		Iterator begin(){return m_animations.begin();}
        Iterator end(){return m_animations.end();}
        DsSprite* clone(int clone_id=false);
	private:
        std::string m_name;
		std::string m_id;
		std::vector<DsAnimation*> m_animations;
};

#endif /*_DS_SPRITE_H_*/




















