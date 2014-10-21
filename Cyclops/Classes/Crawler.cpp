#include "Crawler.h"


Crawler::Crawler(void)
{
}


Crawler::~Crawler(void)
{
}

void	Crawler::loadAnimations(){
	this->walkingAnim = this->loadAnimationFromPlist("walkingAnim", "Crawler");
	this->dyingAnim = this->loadAnimationFromPlist("dyingAnim", "Crawler");

}

void Crawler::update(float dt) {
	CCPoint position = this->getPosition();
	if(this->characterState == kStateDead) {
		this->desiredPosition = position;
		return;
	}

	float	distance = ccpDistance(position, this->player.getPosition() );

	if(distance > 1000) {
		this->desiredPosition = position;
		this->isActive = false;
		return;	
	} else {
		this->isActive = true;
	}
	//1 
	if( this->onGround ) {
		this->changeState(kStateWalking);
		//2
		if(this->isFlipX){
			this->velocity = ccp(-kMovementSpeed, 0);
		} else {
			this->velocity = ccp(kMovementSpeed, 0);
		}
		// 3
	} else {
		this->changeState(kStateFalling);
		this->velocity = ccp(this->velocity.x * 0.98f, this->velocity.y);
	
	}

	// 4
	if(this->onWall){
		this->velocity = ccp(-this->velocity.x , this->velocity.y);
		//5

		if(this->velocity.x > 0){
			this->setFlipX(false);
		} else {
			this->setFlipX(true);
		}
	
	}


	CCPoint gravity = ccp(0.0f, -450.0f);
	CCPoint gravityStep = ccpMult(gravity, dt);
	this->velocity = ccpAdd(this->velocity, gravityStep);
	this->desiredPosition = ccpAdd(position, ccpMult(this->velocity, dt));

}

void	Crawler::changeState(CharacterStates newState) {
	if(newState == this->characterState ) {
		return;
	}

	this->stopAllActions();
	this->characterState = newState;

	CCAction* action = NULL:
	switch(newState) {
		case kStateWalking:
			action = CCRepeatForever::create( CCAnimate::create( this->walkingAnim) );
			break;
		case kStateFalling:
			this->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Crawler1.png"));
			break;
		case kStateDead:
			SimpleAudioEngine::sharedEngine()->playEffect("crawler_die.wav");
			action = CCSequence::create(CCAnimate::create(this->dyingAnim), 
				CCCallFunc::create(this, callfunc_selector(Crawler::removeSelf)), NULL);

			break;
		default:
			break;
	
	}
	if(action != NULL)
		this->runAction(action);
}