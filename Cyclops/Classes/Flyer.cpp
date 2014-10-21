#include "Flyer.h"


Flyer::Flyer(void)
{
}


Flyer::~Flyer(void)
{
}

void	Flyer::loadAnimations(){
	this->seekingAnim = loadAnimationFromPlist("seekingAnim", "Flyer");
	this->attackingAnim = loadAnimationFromPlist("attackingAnim", "Flyer");
	this->dyingAnim = loadAnimationFromPlist("dyingAnim", "Flyer");

}

void Flyer::update(float dt) {
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
	//2
	float speed;
	//3
	if(distance < 100) {
		this->changeState(kStateAttacking);
		speed = 10;
	//4
	} else if ( ( !this->player->isFlipX && this->player->getPosition().x < position.x ) ||
		(this->player->isFlipX && this->player.getPosition().x > position.x ) ) {
			this->changeState(kStateHiding);
			speed = 0;
	//5
	} else {
		this->changeState(kStateSeeking);
		speed = 60;
	
	}

	//6
	CCPoint v = ccpNormalize(ccpSub(this->player->getPosition(), position) );
	this->velocity = ccpMult(v, speed);

	//7
	if( position.x < this->player.getPosition().x){
		this->setFlipX(false);
	} else {
		this->setFlipX(true);
	}

	//8

	CCPoint stepVelocity = ccpMult(this->velocity, dt);
	this->desiredPosition = ccpAdd(position, stepVelocity);

}

void	Flyer::changeState(CharacterStates newState) {
	if(newState == this->characterState ) {
		return;
	}

	CCAction* action = NULL;
	switch(newState) {
		case kStateSeeking:
			action = CCRepeatForever::create( CCAnimate::create( this->seekingAnim) );
			break;
		case kStateHiding:
			SimpleAudioEngine::sharedEngine()->playEffect("flyercloseeye.wav");
			this->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Flyer4.png"));
			break;
		case kStateAttacking:
			SimpleAudioEngine::sharedEngine()->playEffect("flyerattack.wav");
			action = CCRepeatForever::create( CCAnimate::create( this->attackingAnim) );



			break;
		case kStateDead:
			SimpleAudioEngine::sharedEngine()->playEffect("flyerdie.wav");
			action = CCSequence::create(CCAnimate::create(this->dyingAnim), 
				CCCallFunc::create(this, callfunc_selector(Flyer::removeSelf)), NULL);
			break;
		default:
			break;
	
	}
	if(action != NULL){
		this->stopAllActions();
		this->runAction(action);
	}
	this->characterState = newState;
}