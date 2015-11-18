#ifndef PHOENIX_STATIC_OBJECT_H
#define PHOENIX_STATIC_OBJECT_H

#define F_AddStaticObjectToClass(Class)		\
public:										\
	static Class& GetStaticObject()			\
	{										\
		static Class StaticObject;			\
		return StaticObject;				\
	}										\
private:

#endif
