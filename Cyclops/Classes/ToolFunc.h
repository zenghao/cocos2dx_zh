#ifndef TOOLFUNC_H
#define TOOLFUNC_H

#include <vector>
#include<string.h>
#include "cocos2d.h"

#define OBJCREATE_FUNC(__TYPE__) \
static __TYPE__* createGameObj() \
{ \
    __TYPE__ *pRet = new __TYPE__(); \
    if (pRet) \
    { \
        pRet->autorelease(); \
        return pRet; \
    } \
    else \
    { \
        delete pRet; \
        pRet = NULL; \
        return NULL; \
    } \
}

using namespace std;
USING_NS_CC;
class ToolFunc
{
public:
	ToolFunc(void);
	~ToolFunc(void);
public:
	//�ַ����ָ�,�ɹ�����1�����򷵻�0
	static int split(string str, const char* sep, vector<string>& ret);
	//���ذ���dx ,dy ���ź�ľ���
	static CCRect CCRectInset( CCRect& rect , float dx , float dy );
	//�������������ཻ�ľ�������
	static CCRect CCRectIntersection( const CCRect& rectA , const CCRect& rectB);

};
#endif
