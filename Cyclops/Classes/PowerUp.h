#pragma once

#include "cocos2d.h"
#include "GameObject.h"

USING_NS_CC;

class PowerUp : public GameObject{

public:

	PowerUp();
	~PowerUp();


	CC_SYNTHESIZE_RETAIN(CCString* , m_powerUpType , PowerUpType);

}; 