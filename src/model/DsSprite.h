#ifndef _DS_SPRITE_H_
#define _DS_SPRITE_H_ 

#include <string>
#include <vector>

class DsAnimation;
class DsSprite 
{
	public:
		typedef std::vector<DsAnimation*>::iterator Iterator;


	public:
		DsSprite(const std::string& name);
		~DsSprite();
	public:
		std::string getName(){return m_name;}
		void addAnimation(DsAnimation* anim);
		void removeAnimation(const std::string& name);
		DsAnimation* getAnimation(const std::string& name);
		int getAnimationNu(){return m_animations.size();}

		Iterator begin(){return m_animations.begin();}
        Iterator end(){return m_animations.end();}


	private:
		std::string m_name;
		std::vector<DsAnimation*> m_animations;
};




#endif /*_DS_SPRITE_H_*/


