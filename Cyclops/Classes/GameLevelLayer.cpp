#include "GameLevelLayer.h"


GameLevelLayer::GameLevelLayer(void)
{
}


GameLevelLayer::~GameLevelLayer(void)
{
}

CCScene	*	GameLevelLayer::sceneWithLevel(int level) {
	CCScene	*scene = CCScene::create();
	GameLevelLayer	*layer = GameLevelLayer::create();
	layer->initWithLevel(level);

	HUDLayer	*hudLayer = HUDLayer::create();

	scene->addChild(hudLayer, 1, 25);
	scene->addChild(layer);


	return scene;
}

CCScene	*	GameLevelLayer::scene() {
	CCScene*	scene = CCScene::create();
	GameLevelLayer	*layer = GameLevelLayer::create();

	HUDLayer	*hudLayer = HUDLayer::create();

	scene->addChild(hudLayer, 1, 25);
	scene->addChild(layer);
}


bool		GameLevelLayer::init() {
	return this->initWithLevel(1);
}

bool		GameLevelLayer::initWithLevel(int level) {
	bool bRet = CCLayer::init();
	if( bRet == true) {
		this->currentLevel = level;
		char	levelName[10];

		CCDictionary	*levelsDict = CCDictionary::createWithContentsOfFile("levels.plist");

		memset(levelName, 0, sizeof(levelName) );
		sprintf(levelName, "level%d", level);

		//当前地图关卡的背景数据//
		CCDictionary	*lvlDict = (CCDictionary *) levelsDict->objectForKey(levelName);
		//背景音乐//
		const char*	bgMusic = lvlDict->valueForKey("music")->getCString();

	
		SimpleAudioEngine::sharedEngine()->playBackgroundMusic(bgMusic, true);
		SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.25f);

		CCParallaxNode	*pNode = CCParallaxNode::create();
		CCArray	*backGroundArray = (CCArray	*) lvlDict->objectForKey("background");
		CCObject	*group1 = NULL;
		CCObject	*group2 = NULL;
		CCARRAY_FOREACH( backGroundArray, group1) {
			CCArray	*nodeArray = (CCArray	*)group1;
			CCARRAY_FOREACH(nodeArray, group2) {
				CCString* fileName = (CCString	*)group2;
				CCSprite	*bgNodeSprite = CCSprite::create(fileName->getCString());
				bgNodeSprite->setAnchorPoint( ccp(0.0f, 0.0f) );

				int index = nodeArray->indexOfObject(group2);

				float	index2 = (float) backGroundArray->indexOfObject(group1) + 1.0f;
				float	ratio = ( ( 4.0f - index2) / 8.0f);
				if(index2 == 4.0f)
					ratio = 0.0f;

				pNode->addChild(bgNodeSprite, index2 * -1, ccp(ratio, 0.6f), ccp(index * 2048, 30));


			
			}
		
		}//foreach over

		this->addChild(pNode);

		const char* lvlString = lvlDict->valueForKey("level")->getCString();

		this->map = PCTMXTiledMap::tiledMapWithTMXFile(lvlString);
		this->addChild(map);

		this->walls = map->layerNamed("walls");

		CCSpriteFrameCache *spriteFrameCache = CCSpriteFrameCache::sharedSpriteFrameCache();

		spriteFrameCache->addSpriteFramesWithFile("PlayerImages.plist");

		player = Player:create();
		player->initWithSpriteFrameName("Player1.png");

		this->addChild(player);

		CCTMXObjectGroup	*og = map->objectGroupNamed("objects");
		CCDictionary	*playerObj = og->objectNamed("player");
		player->setPosition(ccp(playerObj->valueForKey("x")->floatValue(),
			playerObj->valueForKey("y")->floatValue()));

		player.canDoubleJump = lvlDict->valueForKey("doubleJump")->boolValue();
		player.canWallSlide = lvlDict->valueForKey("wallSlide")->boolValue();

		this->loadEnemies();
		this->loadPowerUps();

		CCDictionary	*exit = og->objectNamed("exit");
		this->exitPoint = ccp(exit->valueForKey("x")->floatValue() + exit->valueForKey("width")->floatValue() / 2.0f,
			exit->valueForKey("y")->floatValue() + exit->valueForKey("height")->floatValue() / 2.0f);

		this->scheduleUpdate();

		return true;
	}
	return false;
}

void		GameLevelLayer::loadEnemies() {

	CCTMXObjectGroup *enemies = map->objectGroupNamed("enemies");
	this->enemiesArray = CCArray::create();

	CCArray*	enemyTypes = CCArray::create();
	CCArray*	enemyBatchNodes = CCArray::create();

	char	framesFileName[30];
	char	firstFrameName[20];
	CCObject	*o;
	CCARRAY_FOREACH(enemies->getObjects(), o){
		CCDictionary*		enemy = (CCDictionary*)o;
		const CCString	*	enemyType = enemy->valueForKey("type");
		if( !enemyTypes->containsObject(enemyType) ) {
			memset(framesFileName, 0, sizeof(frameFileName));
			sprintf(framesFileName, "%sImages.plist", enemyType->getCString());
			CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile( frameFileName);
			memset(framesFileName, 0, sizeof(frameFileName));
			sprintf(framesFileName, "%sImages.png", enemyType->getCString());

			CCSpriteBatchNode	*enemyBatchNode = CCSpriteBatchNode::create(framesFileName);

			this->addChild(enemyBatchNode);

			enemyTypes->addObject(enemyType);
			enemyBatchNodes->addObject(enemyBatchNode);
		}
		memset(firstFrameName, 0, sizeof(firstFrameName));
		sprintf(firstFrameName, "%s1.png", enemyType->getCString());
		Enemy	*enemyInstance = Enemy::getEnemyByString(enemyType->m_sString, firstFrameName);
		enemyInstance->setPosition( ccp( enemy->valueForKey("x")->floatValue(), 
																enemy->valueForKey("y")->floatValue() );
		enemyInstance->player = this->player;
		enemyInstance->map = this->map;

		int enemyIndx = enemyTypes->indexOfObject(enemyType);
		CCSpriteBatchNode *node = enemyBatchNodes->objectAtIndex(enemyIndx);
		node->addChild( enemyInstance);
		enemiesArray->addObject(enemyInstance);
	}
}

void		GameLevelLayer::loadPowerUps() {
	CCTMXObjectGroup	*powerUps = map->objectGroupNamed("powerups");
	this->powerUpsArray = CCArray::create();
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("PowerUpsImages.plist");
	CCObject*	o;
	char	frameName[20];
	CCARRAY_FOREACH(powerUps->getObjects(), o){
		CCDictionary*	powerUp = (CCDictionary*)o;
		const CCString*	powerUpType = powerUp->valueForKey("type");
		memset(frameName, 0, sizeof(frameName));
		sprintf(frameName, "%s.png", powerUpType->getCString());
		PowerUp	*pu = PowerUp::create();
		pu->initWithSpriteFrameName(frameName);
		pu->setPosition( ccp( powerUp->valueForKey("x")->floatValue(), 
											powerUp->valueForKey("y")->floatValue() );
		pu.powerUpType = powerUpType;

		this->powerUpsArray->addObject(pu);
		this->addChild(pu);	
	}


}
void		GameLevelLayer::setViewpointCenter(CCPoint position) {
	CCSize	winSize = CCDirector::sharedDirector()->getWinSize();
	CCSize	mapSize = map->getMapSize();
	CCSize	tileSize = map->getTileSize();
	CCPoint	position = this->getPosition();
	float x = 0;
	float y = 0;
	 x = MAX(position.x, winSize.width / 2.0f);
	 y = MAX(position.y, winSize.height / 2.0f);

	 x = MIN(x, (mapSize.width * tileSize.width) - (winSize.width / 2.0f));
	 y = MIN(y, (mapSize.height * tileSize.height ) - (winSize.height / 2.0f));

	 CCPoint	actualPosition = ccp(x, y);
	 CCPoint	centerOfView = ccp(winSize.width / 2.0f, winSize.height / 2.0f);
	 CCPoint	viewPoint = ccpSub(centerOfView, actualPosition);
	 this->setPosition(viewPoint);

}
void		GameLevelLayer::checkForAndResolveCollisions(Character	* c){

	/*
		4	1	5
		2		3
		6	0	7
	*/

	CCArray*	tiles = map->getSurroundingTilesAtPosition(c->getPosition(), this->walls);
	c->onGround = false;
	c->onWall = false;
	CCObject*	o;
	CCSize tileSize = map->getTileSize();
	CCARRAY_FOREACH( tiles, o) {
		CCDictionary*	dic = (CCDictionary*)o;
		CCRect		pRect = c->collisionBoundingBox();
		int gid = dic->valueForKey("gid")->intValue();
		if(gid != 0){
			
			float x = dic->valueForKey("x")->floatValue();
			float y = dic->valueForKey("y")->floatValue();
			CCRect tileRect = CCRectMake(x, y, tileSize.width, tileSize.height);
			if( CCRect::intersectsRect( pRect, tileRect) ) {
				CCRect		intersection = ToolFunc::CCRectIntersection(pRect, tileRect);
				if ( intersection.size.width == 0.0f && intersection.size.height == 0.0f ) {
					continue;
				}
				int tileIndex = tiles->indexOfObject(o);

				if( tileIndex == 0) {
					//角色碰撞到下面,需要向上修正//
					c->desiredPosition = ccp(c->desiredPosition.x, c->desiredPosition.y + intersection.size.height);
					c->velocity = ccp(c->velocity.x , 0.0f);
					c->onGround = true;

				
				} else if (tileIndex == 1 ) {
					//角色碰撞到上面,需要向下修正//
					c->desiredPosition = ccp(c->desiredPosition.x, c->desiredPosition.y - intersection.size.height);
					c->velocity = ccp(c->velocity.x , 0.0f);

				
				} else if (tileIndex == 2 ) {
					//角色碰撞到左边,需要向右修正//
					c->desiredPosition = ccp(c->desiredPosition.x + intersection.size.width, c->desiredPosition.y);
					c->onWall = true;
					c->velocity = ccp(0.0f , c->velocity.y);

				
				} else if (tileIndex == 3 ) {
					//角色碰撞到右边,需要向左修正
					c->desiredPosition = ccp(c->desiredPosition.x - intersection.size.width, c->desiredPosition.y);
					c->onWall = true;
					c->velocity = ccp(0.0f , c->velocity.y);				
				} else {
					/*
						4	1	5
						2		3
						6	0	7
					*/
					//下面是除了以上的4个方向外其他4个角度的处理//
					if ( intersection.size.width > intersection.size.height ) {
						c->velocity = ccp(c->velocity.x, 0.0f);
						float resolutionHeight;
						if(tileIndex > 5) {
							resolutionHeight = intersection.size.height;
							c->onGround = true;
						} else {
							resolutionHeight = -intersection.size.height;
						}
						c->desiredPosition = ccp ( c->desiredPosition.x, c->desiredPosition.y + resolutionHeight);
					
					
					} else {
					/*
						4	1	5
						2		3
						6	0	7
					*/
						float resolutionWidth;
						if(tileIndex == 6 || tileIndex == 4) {
							resolutionWidth = intersection.size.width;
						} else {
							resolutionWidth = -intersection.size.width;
						}
						c->desiredPosition = ccp ( c->desiredPosition.x + resolutionWidth, c->desiredPosition.y);

						if(tileIndex == 6 || tileIndex == 7){
							c->onWall = true;
						}
						c->velocity = ccp(0.0f, c->velocity.y);					
					}// end if intersection.size.width > intersection.size.height
				
				
				
				}// end if tileIndex == 0

			}// end CCRect::intersectsRect

		}	//end gid != 0
	
	
	} //end foreach
	c->setPosition(c->desiredPosition);



}
void		GameLevelLayer::checkForEnemyCollisions(Enemy *e) {
	if ( e->isActive && this->player->isActive) {
		//玩家和敌人的碰撞
		if ( CCRect::intersectsRect(player->collisionBoundingBox(), e->collisionBoundingBox()) ) {
			CCPoint playerPos = player->getPosition();

			
			CCPoint	playerFootPoint = ccp(playerPos.x, playerPos.y - player->collisionBoundingBox().size.height/ 2.0f);
			//玩家踩到敌人头上//
			if(player.velocity.y < 0 && playerFootPoint.y > e.getPosition().y) {
				player->bounce();
				e->tookHit(player);
			
			} else {
				//玩家受伤//
				player->tookHit(e);		
			}
		}
	}



}
void		GameLevelLayer::checkForPowerUpsCollisions() {
	CCArray	*removeArray = CCArray::create();
	CCObject*	o = NULL;
	CCARRAY_FOREACH( this->powerUpsArray, o) {
		PowerUp*	p = (PowerUp*) o;
		if ( CCRect::intersectsRect(player->collisionBoundingBox(), p->boundingBox()) ) {
			
			if ( p->powerUpType.compare("DoubleJump") ) {
				this->player->canDoubleJump = true;		
			} else {
				this->player->canDoubleJump = false;
			}
			removeArray->addObject(p);		
		}
	
	}//foreach

	// remove obj

	CCARRAY_FOREACH(removeArray, o) {
		PowerUp	*p = (PowerUp*) o;
		this->powerUpsArray->removeObject(p);
		p->removeFromParentAndCleanup(true);
	}
	removeArray->removeAllObjects();
}
void		GameLevelLayer::checkForExit(){
	float	distanceToExit = ccpDistance(player->getPosition(), this->exitPoint);
	if ( distanceToExit < 100 ) {
		
		if(currentLevel < 3 ) {
			int nextLevel = currentLevel + 1;
			CCDirector::sharedDirector()->replaceScene(GameLevelLayer::sceneWithLevel(nextLevel) );
				 
		} else {
			CCLabelTTF *win = CCLabelTTF::create("You Win", "Marker Felt", 60);
			win->setPosition( ccp(240 - this->getPosition().x, 160 - this->getPosition().y) );
			this->addChild(win);

		}
	
	}


}

void		GameLevelLayer::restart() {
	CCNotificationCenter::sharedNotificationCenter()->postNotification("restart",NULL);
}
void		GameLevelLayer::update(float dt) {
	player->update(dt);
	this->checkForAndResolveCollisions(player);

	CCArray*	enemiesThatNeedDeleting = CCArray::create();
	CCObject* o;
	CCARRAY_FOREACH( this->enemiesArray, o) {
		Enemy	*e = (Enemy*) o;
		e->update(dt);
		this->checkForAndResolveCollisions(e);
		this->checkForEnemyCollisions(e);

		if ( !e->isActive && e->characterState == kStateDead ) {
			enemiesThatNeedDeleting->addObject(e);	
		}
	
	}//foreach over


	CCARRAY_FOREACH( enemiesThatNeedDeleting, o) {
		Enemy* e = (Enemy*)o;
		enemiesArray->removeObject(e);
		e->removeFromParentAndCleanup(true);
	}

	this->checkForPowerUpsCollisions();
	this->checkForExit();
	this->setViewpointCenter(this->player->getPosition());

}
void		GameLevelLayer::gameEnded(){
	CCLabelTTF	*gameOver = CCLabelTTF::create("You Lose","Marker Felt",60);
	CCPoint position = this->getPosition();
	gameOver->setPosition( ccp(240 - position.x, 160 - position.y);

	this->addChild(gameOver);

}