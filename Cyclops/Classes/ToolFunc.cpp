#include "ToolFunc.h"


ToolFunc::ToolFunc(void)
{
}


ToolFunc::~ToolFunc(void)
{
}

int ToolFunc::split(string str, const char* sep, vector<string>& ret){
	if(str.empty())
		return 0;

	while (str.find(sep) != string::npos) {
		unsigned index = str.find(sep);
		ret .push_back(str.substr(0,index));
		str = str.substr(index + 1, str.length());
	
	}
	if (str.length() > 0) {
		ret.push_back(str);
	}
	return 1;
} 
CCRect ToolFunc::CCRectInset( CCRect& rect , float dx , float dy ) {
	rect.origin.x += dx;
	rect.origin.y += dy;
	rect.size.width -= 2 * dx;
	rect.size.height -= 2 * dy;

	return rect;
} 

CCRect ToolFunc::CCRectIntersection ( const CCRect& rectA , const CCRect& rectB) {
	//获取2个矩形相交部门的面积
	float x = MAX( CCRect::CCRectGetMinX( rectA ) , CCRect::CCRectGetMinX( rectB ) );
	float y = MAX( CCRect::CCRectGetMinY( rectA ) , CCRect::CCRectGetMinY( rectB ) );
	
	float width = MIN( CCRect::CCRectGetMaxX( rectA ),CCRect::CCRectGetMaxX( rectB ) ) - x;
	float height = MIN( CCRect::CCRectGetMaxY( rectA ),CCRect::CCRectGetMaxY( rectB ) ) - y;

	CCRect returnRect = CCRectMake( x , y , width , height );
	return returnRect;

}