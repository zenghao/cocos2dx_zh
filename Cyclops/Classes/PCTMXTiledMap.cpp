#include "PCTMXTiledMap.h"

PCTMXTiledMap::PCTMXTiledMap(){


}

PCTMXTiledMap::~PCTMXTiledMap(){


}

CCPoint PCTMXTiledMap::tileCoordForPosition(CCPoint position){


	float x = floor(position.x / this->getTileSize().width);
	float levelHeightInPixels = this->getMapSize().height * this->getTileSize().height;
	float y = floor((levelHeightInPixels - position.y) / this->getTileSize().height);
	return ccp(x, y);

}

CCRect PCTMXTiledMap::tileRectFromTileCoords(CCPoint tileCoords){

	float levelHeightInPixels = this->getMapSize().height * this->getTileSize().height;
	CCPoint origin = ccp(tileCoords.x * self.tileSize.width, levelHeightInPixels - ((tileCoords.y + 1) * this->getTileSize().height));
	return CCRectMake(origin.x, origin.y, this->getMapSize().width, this->getTileSize().height);
}

bool PCTMXTiledMap::isWallAtTileCoord(CCPoint tileCoord){

	CCTMXLayer *layer = this->layerNamed("walls");
	int tgid =layer->tileGIDAt(tileCoord);
	if (tgid) {
		return true;
	} else {
		return false;
	}

}

CCArray* PCTMXTiledMap::getSurroundingTilesAtPosition(CCPoint position,CCTMXLayer* layer){

	CCPoint plPos = this->tileCoordForPosition(position);
	//2
	CCArray *gids = CCArray::create();
	//3
	for (int i = 0; i < 9; i++) {
		int c = i % 3;
		int r = (int)(i / 3);
		CCPoint tilePos = ccp(plPos.x + (c - 1), plPos.y + (r - 1));
		//4
		int tgid = layer->tileGIDAt(tilePos);

		CCInteger *tgidI=CCInteger::create(tgid);
		//5
		CCRect tileRect = this->tileRectFromTileCoords(tilePos);

		CCString *pStr=CCString::createWithFormat("{%f,%f}",tilePos.x,tilePos.y);
		//6
		CCDictionary *tileDict = CCDictionary::create();

		tileDict->setObject(tgidI,"tgid");
		tileDict->setObject(CCInteger::create(tileRect.origin.x),"x");
		tileDict->setObject(CCInteger::create(tileRect.origin.y),"y");
		tileDict->setObject(pStr,"tilePos");

		gids->addObject(tileDict);

		gids->removeObjectAtIndex(4);
		gids->insertObject(gids->objectAtIndex(2),6);
		gids->removeObjectAtIndex(2);
		gids->exchangeObjectAtIndex(4,6);
		gids->exchangeObjectAtIndex(0,4);
		
		return gids;



	}
}