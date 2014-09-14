#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "cocos2d.h"

enum eCharacterRotation
{
	idle,
	rotateClockwise,
	rotateCounterClockwise
};

class Character : public cocos2d::Sprite
{
public:
    static Character* create(const std::string& filename);

	void setMovingForward(bool val) { _movingForward = val; }
	void setMovingBackward(bool val) { _movingBackward = val; }
	void setCharacterRotation(eCharacterRotation val) { _rotation = val; }

	virtual void update(float dt);

protected:
	bool _movingForward;
	bool _movingBackward;
	eCharacterRotation _rotation;
};

#endif // __HELLOWORLD_SCENE_H__
