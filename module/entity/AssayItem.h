#ifndef AssayItem_h
#define AssayItem_h
#include <QQmlEngine>

class AssayItem
{
	public:
		
		//主键
        int Itemid;
		
		//归属的测试项目(外键）
        int Assayid;
		
		//子项目名称
        QString ItemName;
		
		//单位
        QString ResultUnit;
		
        //正常范围最小值
        int RefValueMin;
		
		//正常范围最大值
        int RefValueMax;
};

#endif
