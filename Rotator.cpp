#include "Rotator.h"



Rotator::Rotator()
{
}


Rotator::~Rotator()
{
}

void Rotator::update(float deltaTime)
{
	gameObject->rotation += rotation * deltaTime;
}
