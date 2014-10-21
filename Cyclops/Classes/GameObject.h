#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "cocos2d.h"
#include "ToolFunc.h"
USING_NS_CC;
class GameObject : public CCSprite
{
public:
	virtual bool initWithSpriteFrameName(const char* spriteFrameName);

	CCPoint	velocity;
	CCAnimation*	loadAnimationFromPlist(const char* animationName, const char *className);
	//this method must be override
	virtual void	loadAnimations();
	//构造和析构方法
	GameObject(void);
	~GameObject(void);
};
#endif

