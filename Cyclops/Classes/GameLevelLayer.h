#ifndef		GAMELEVELLAYER_H
#define	GAMELEVELLAYER_H

#include "cocos2d.h"
#include "HUDLayer.h"
#include "SimpleAudioEngine.h"
#include "PCTMXTiledMap.h"
#include "Player.h"
#include "Crawler.h"
#include "Flyer.h"
#include "PowerUp.h"
USING_NS_CC;
class GameLevelLayer : public CCLayer
{
public:
	GameLevelLayer(void);
	~GameLevelLayer(void);
public:
	int	currentLevel;
	PCTMXTiledMap	*map;
	Player	*player;
	CCTMXLayer	*walls;
	CCPoint		exitPoint;
	CCArray	*enemiesArray;
	CCArray	*powerUpsArray;
	
public:
	bool		init();
	bool		initWithLevel(int level);
	void		loadEnemies();
	void		loadPowerUps();
	void		setViewpointCenter(CCPoint position);
	void		checkForAndResolveCollisions(Character	* c);
	void		checkForEnemyCollisions(Enemy *e);
	void		checkForPowerUpsCollisions();
	void		checkForExit();

	void		restart();
	void		update(float dt);	
	void		gameEnded();
	//static function
public:
	static	CCScene*		sceneWithLevel(int level);
	static	CCScene*		scene();
	CREATE_FUNC(GameLevelLayer);
};
#endif
