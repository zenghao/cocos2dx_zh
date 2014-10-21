#include "Character.h"
Character::Character(void)
{
}


Character::~Character(void)
{
}


void		Character::update( float dt) {


}

CCRect		Character::collisionBoundingBox() {
	CCPoint diff = ccpSub(this->desiredPosition, this->getPosition());
	CCRect rect = this->boundingBox();
	return ToolFunc::CCRectInset(rect, diff.x, diff.y);
/*	rect.origin.x += diff.x;
	rect.origin.y += diff.y;
	return rect*/;
}

void		Character::changeState( CharacterStates newState) {


}

void		Character::tookHit( Character * character ) {

	printf("\n	Took hit %s, %s", character, this);

}