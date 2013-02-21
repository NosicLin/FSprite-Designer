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
	public:  
		std::string getID(){return m_id;}
        std::string getName(){return m_name;}
        void setName(const std::string& name){m_name=name;}

    public:
        void addAnimation(DsAnimation* anim);
		void removeAnimation(const std::string& name);

        DsAnimation* getAnimationByID(const std::string& id);
        DsAnimation* getAnimation(const std::string& name);
		DsAnimation* getAnimation(int index);

        int getAnimationNu(){return m_animations.size();}
        bool hasAnimation(const std::string& name);

		Iterator begin(){return m_animations.begin();}
        Iterator end(){return m_animations.end();}

	private:
        std::string m_name;
		std::string m_id;
		std::vector<DsAnimation*> m_animations;
};

#endif /*_DS_SPRITE_H_*/




















