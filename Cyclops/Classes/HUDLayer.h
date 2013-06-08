#pragma once

#include "cocos2d.h"

USING_NS_CC;


typedef enum {
	kJoyDirectionLeft,
	kJoyDirectionRight,
	kJoyDirectionNone
} joystickDirection;

typedef enum {
	kJumpButtonOn,
	kJumpButtonOff
} jumpButtonState;

struct joyState {
	jumpButtonState jumpB;
	joystickDirection joyDirection;
};

class HUDLayer : CCLayer{
public:

	joystickDirection getJoystickDirection();
	jumpButtonState getJumpButtonState();
	void setLifeMeter(CCNotificationCenter* notes);

};