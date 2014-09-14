#include "Character.h"

USING_NS_CC;

Character* Character::create(const std::string& filename)
{
    Character *character = new (std::nothrow) Character();
    if (character && character->initWithFile(filename))
    {
		character->scheduleUpdate();

        character->autorelease();
        return character;
    }
    CC_SAFE_DELETE(character);
    return nullptr;
}

void Character::update(float dt)
{
	float rotationValue = 0.0f;
	float moveValue = 0.0f;

	if(_rotation == eCharacterRotation::rotateClockwise)
		rotationValue = 1.0f;
	else if(_rotation == eCharacterRotation::rotateCounterClockwise)
		rotationValue = -1.0f;

	setRotation(getRotation() + rotationValue);

	if(_movingForward == true)
		moveValue = 2.0f;
	else if(_movingBackward == true)
		moveValue = -2.0f;

	setPositionX(_position.x + (moveValue * sinf(CC_DEGREES_TO_RADIANS(getRotation()))));
	setPositionY(_position.y + (moveValue * cosf(CC_DEGREES_TO_RADIANS(getRotation()))));
	//a = c sin
}