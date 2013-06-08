#include "Enemy.h"

#include "Crawler.h"
#include "Flyer.h"

Enemy::Enemy(void)
{
}


Enemy::~Enemy(void)
{
}
Enemy	*	Enemy::getEnemyByString(string	className, const char*	frameName){
	Enemy	*	result = NULL;
	if( className.compare("Crawler") == 0){
		result = Crawler::createGameObj();		
	} else if (className.compare("Flyer") == 0){
		result = Flyer::createGameObj();	
	} 
	result->initWithSpriteFrameName(frameName);
	return result;
}


bool Enemy::initWithSpriteFrameName(const char * spriteFrameName){
	bool	bRet = Character::initWithSpriteFrameName(spriteFrameName);
	if(true == bRet){
		this->life = 100;
	}
	return bRet;

}

void	Enemy::tookHit(Character * character){
	this->life -= 100;
	if(this->life <= 0) {
		this->changeState(kStateDead);
	}

}

void	Enemy::removeSelf(){
	this->isActive = false;
}