#include "Transform.h"

using namespace Phoenix;

Transform::Transform() :
	Component(),
	Position(FVector3D(0, 0, 0)),
	Rotation(FVector3D(0, 0, 0)),
	Scale(FVector3D(1, 1, 1)),
	Angle(0)
{
}

Transform::~Transform()
{
}

void Transform::Init()
{
}

void Transform::SetPosition(const FVector3D& InPosition)
{
	Position = InPosition;
}
