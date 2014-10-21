#include "Player.h"

#define kJumpForce 400
#define kKnockback 100
#define kCoolDown 1.5

Player::Player():
m_canWallSlide(false) ,
m_canDoubleJump(false)
{


}

Player::~Player(){


}

bool Player::initWithSpriteFrameName(const char *pszSpriteFrameNam){

	bool bRet=false;

	do {

		CC_BREAK_IF(!CCSprite::initWithSpriteFrameName(pszSpriteFrameNam));
		this->velocity= ccp(0.0, 0.0);
		this->isActive = true;
		jumpReset = true;
		this->life = 500;


	} while(0) ;

}


void Player::loadAnimations(){

	wallSlideAnim = this->loadAnimationFromPlist("","");
	walkingAnim = this->loadAnimationFromPlist("","");
	jumpUpAnim = this->loadAnimationFromPlist("","");
	dyingAnim = this->loadAnimationFromPlist("","");
}

void Player::coolDownFinished(){

	this->setOpacity(255);
	this->isActive = true;
}

void Player::endGame(){



}

void Player::bounce(){


}

void Player::update(float dt){



}

CCRect Player::collisionBoundingBox(){


}

void Player::tookHit(Character * character){

	//1
	this->life = this->life - 100;
	if (this->life < 0) {
		this->life = 0;
	}
	//2
	//[[NSNotificationCenter defaultCenter] postNotificationName:@"LifeUpdate" object:self userInfo:@{@"life" : @((float)self.life / 500.0)}];
	CCNotificationCenter::sharedNotificationCenter()->postNotification("");
	//3
	if (self.life <= 0) {
		//4
		[self changeState:kStateDead];
	} else {
		//5
		self.opacity = 122;
		self.isActive = NO;
		//6
		if (self.position.x < character.position.x) {
			self.velocity = ccp(-kKnockback / 2, kKnockback);
		} else {
			self.velocity = ccp(kKnockback / 2, kKnockback);
		}
		//7
		[self performSelector:@selector(coolDownFinished) withObject:nil afterDelay:kCoolDown];
	}
}

void Player::changeState(CharacterStates newState){



}
