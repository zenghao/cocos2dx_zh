#ifndef CHARACTER_H
#define CHARACTER_H

#include "GameObject.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

typedef enum {
	kStateJumping,
	kStateDoubleJumping,
	kStateWalking,
	kStateStanding,
	kStateDying,
	kStateFalling,
	kStateDead,
	kStateWallSliding,
	kStateAttacking,
	kStateSeeking,
	kStateHiding
} CharacterStates;
class Character : public GameObject
{
public:
	Character(void);
	~Character(void);

	
public:
	//member//
	CCPoint	desiredPosition;
	bool			onGround;	
	bool			onWall;
	bool			isActive;
	int			life;
	CharacterStates	characterState;

public:
	//method//
	virtual void			changeState( CharacterStates newState);
	virtual void			update(float dt);
	CCRect		collisionBoundingBox();
	virtual	void			tookHit(Character	* character);
};
#endif

