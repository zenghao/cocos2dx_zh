#ifndef	 FLYER_H
#define FLYER_H
#include "Enemy.h"
class Flyer : public Enemy
{
public:
	Flyer(void);
	~Flyer(void);
public:
	CCAnimation	*seekingAnim;
	CCAnimation	*attackingAnim;
	CCAnimation	*dyingAnim;

public:
	virtual void			changeState( CharacterStates newState);
	virtual void	update(float dt);
	virtual void	loadAnimations();
public:
	OBJCREATE_FUNC(Flyer);
};
#endif

