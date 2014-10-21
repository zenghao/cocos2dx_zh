#include "GameObject.h"

GameObject::GameObject(void)
{
}
GameObject::~GameObject(void)
{
}

bool GameObject::initWithSpriteFrameName(const char * spriteFrameName){
	bool	bRet = CCSprite::initWithSpriteFrameName(spriteFrameName);
	if(true == bRet){
		this->loadAnimations();
	}
	return bRet;

}


CCAnimation * GameObject::loadAnimationFromPlist(const char * animationName, const char *className){

	//目前设定是32个长度的,如果超过再处理～
	char	tmpName[32];
	memset(tmpName,0,sizeof(tmpName));
	sprintf(tmpName, "%s.plist", className);

	//加载路径//
	std::string path = CCFileUtils::sharedFileUtils()->fullPathForFilename(tmpName);


	CCDictionary	*plistDictionary = CCDictionary::createWithContentsOfFile(path.c_str());
	
	CCDictionary	*animationSettings = (CCDictionary *)plistDictionary->objectForKey(animationName);
	

	CCAnimation *animation = CCAnimation::create();
	CCSpriteFrameCache *spriteFrameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
	//这里需要从键值对中获得动画的帧数,延迟数//

	//解析得到xml文件的动画帧数
	vector<string> framesNumber;
	ToolFunc::split(animationSettings->valueForKey("animationFrames")->m_sString, ",", framesNumber);
	//延迟时间
	float delay = animationSettings->valueForKey("delay")->floatValue();
	animation->setDelayPerUnit(delay);

	//添加帧并返回
	
	for (unsigned i = 0; i < framesNumber.size(); i++) {
		memset(tmpName, 0, sizeof(tmpName));
		sprintf(tmpName, "%s%s.png", className, framesNumber[i]);
		animation->addSpriteFrame( spriteFrameCache->spriteFrameByName(tmpName) );	
	}
	return animation;
}

void	GameObject::loadAnimations(){

}
