#ifndef ENEMY_H
#define ENEMY_H

#include "Character.h"
#include "Player.h"
#include "PCTMXTiledMap.h"
class Enemy : public Character
{
public:
	Enemy(void);
	~Enemy(void);

public:
	Player						*player;
	PCTMXTiledMap		*map;

public:	
	void		removeSelf();
	virtual bool initWithSpriteFrameName(const char* spriteFrameName);
	virtual	void			tookHit(Character	* character);

public:
	static	Enemy	*	getEnemyByString(const string	className, const char*	frameName);

	
};
#endif
