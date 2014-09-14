#include "IngameScene.h"

USING_NS_CC;

#define FADE_TIME 1.0f

Scene* IngameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = IngameScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool IngameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	hero = Character::create("CloseNormal.png");

    // position the sprite on the center of the screen
    hero->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(hero, 0);

	auto listener = EventListenerKeyboard::create();
				listener->onKeyPressed = CC_CALLBACK_2(IngameScene::onKeyPressed, this);
				listener->onKeyReleased = CC_CALLBACK_2(IngameScene::onKeyReleased, this);
				_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}


void IngameScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{	
	if(keyCode == EventKeyboard::KeyCode::KEY_W)
	{
		hero->setMovingForward(true);
	}
	else if(keyCode == EventKeyboard::KeyCode::KEY_S)
	{
		hero->setMovingBackward(true);
	}
	else if(keyCode == EventKeyboard::KeyCode::KEY_A)
	{
		hero->setCharacterRotation(eCharacterRotation::rotateCounterClockwise);
	}
	else if(keyCode == EventKeyboard::KeyCode::KEY_D)
	{
		hero->setCharacterRotation(eCharacterRotation::rotateClockwise);
	}
}

void IngameScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	if(keyCode == EventKeyboard::KeyCode::KEY_W)
	{
		hero->setMovingForward(false);
	}
	else if(keyCode == EventKeyboard::KeyCode::KEY_S)
	{
		hero->setMovingBackward(false);
	}
	else if(keyCode == EventKeyboard::KeyCode::KEY_A)
	{
		hero->setCharacterRotation(eCharacterRotation::idle);
	}
	else if(keyCode == EventKeyboard::KeyCode::KEY_D)
	{
		hero->setCharacterRotation(eCharacterRotation::idle);
	}
}