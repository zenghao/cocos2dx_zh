#pragma once

#include "cocos2d.h"
USING_NS_CC;

class PCTMXTiledMap : CCTMXTiledMap
{
public:

	PCTMXTiledMap();
	~PCTMXTiledMap();

	CCPoint tileCoordForPosition(CCPoint position);

	CCRect tileRectFromTileCoords(CCPoint tileCoords);
	
	CCArray* getSurroundingTilesAtPosition(CCPoint position,CCTMXLayer* layer);

	bool isWallAtTileCoord(CCPoint tileCoord);
	

};
