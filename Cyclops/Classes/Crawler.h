#ifndef CRAWLER_H
#define CRAWLER_H

#include "Enemy.h"

class Crawler : public Enemy
{
public:
	Crawler(void);
	~Crawler(void);

public:
	CCAnimation	*walkingAnim;
	CCAnimation	*dyingAnim;

public:
	virtual void			changeState( CharacterStates newState);
	virtual void	update(float dt);
	virtual void	loadAnimations();
public:
	OBJCREATE_FUNC(Crawler);
};
#endif
