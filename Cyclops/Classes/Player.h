#pragma once 

#include "cocos2d.h"
#include "Character.h"

#define kPlayerWidth 30
#define kPlayerHeight 34
#define kWalkingSpeed 1600
#define kDamping 0.85
#define kMaxSpeed 250
#define kJumpCutoff 150
#define kJumpOut 360
#define kWallSlideSpeed -30

class Player : public Character {

public:
	
	Player();
	~Player();

	void bounce();
	void coolDownFinished();
	void endGame();
	//////////////////////////////////////////////////////////////////////////
	//
	////////////////////////////////////////////////////////////////////////
	virtual void	loadAnimations();

	virtual void	changeState( CharacterStates newState);
	virtual	void			tookHit(Character	* character);
	CCRect		collisionBoundingBox();

	virtual void	update(float dt);
	virtual bool initWithSpriteFrameName(const char *pszSpriteFrameNam);

	CC_SYNTHESIZE(bool , m_canDoubleJump, CanDoubleJump);
	CC_SYNTHESIZE(bool , m_canWallSlide, CanWallSlide);

	BOOL jumpReset;
	CCAnimation *walkingAnim;
	CCAnimation *jumpUpAnim;
	CCAnimation *wallSlideAnim;
	CCAnimation *dyingAnim;

};