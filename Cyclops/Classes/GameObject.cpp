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

	//Ŀǰ�趨��32�����ȵ�,��������ٴ���
	char	tmpName[32];
	memset(tmpName,0,sizeof(tmpName));
	sprintf(tmpName, "%s.plist", className);

	//����·��//
	std::string path = CCFileUtils::sharedFileUtils()->fullPathForFilename(tmpName);


	CCDictionary	*plistDictionary = CCDictionary::createWithContentsOfFile(path.c_str());
	
	CCDictionary	*animationSettings = (CCDictionary *)plistDictionary->objectForKey(animationName);
	

	CCAnimation *animation = CCAnimation::create();
	CCSpriteFrameCache *spriteFrameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
	//������Ҫ�Ӽ�ֵ���л�ö�����֡��,�ӳ���//

	//�����õ�xml�ļ��Ķ���֡��
	vector<string> framesNumber;
	ToolFunc::split(animationSettings->valueForKey("animationFrames")->m_sString, ",", framesNumber);
	//�ӳ�ʱ��
	float delay = animationSettings->valueForKey("delay")->floatValue();
	animation->setDelayPerUnit(delay);

	//���֡������
	
	for (unsigned i = 0; i < framesNumber.size(); i++) {
		memset(tmpName, 0, sizeof(tmpName));
		sprintf(tmpName, "%s%s.png", className, framesNumber[i]);
		animation->addSpriteFrame( spriteFrameCache->spriteFrameByName(tmpName) );	
	}
	return animation;
}

void	GameObject::loadAnimations(){

}
