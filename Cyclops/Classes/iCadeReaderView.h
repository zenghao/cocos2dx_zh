#pragma once

#include "cocos2d.h"

#include "iCadeState.h"

USING_NS_CC;

class iCadeEventDelegate{
public:

	virtual void stateChanged( iCadeState state );
	virtual void buttonDown ( iCadeState button  );
	virtual void buttonUp ( iCadeState button );
};

class iCadeReaderView{

public:

	iCadeState              _iCadeState;

	struct {
		bool stateChanged:1;
		bool buttonDown:1;
		bool buttonUp:1;
	} _delegateFlags;

	CC_SYNTHESIZE(iCadeState , m_iCadeState,ICadeState );


};