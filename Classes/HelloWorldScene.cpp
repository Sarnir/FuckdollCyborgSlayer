#include "HelloWorldScene.h"
#include "MainMenuScene.h"

USING_NS_CC;

#define FADE_TIME 1.0f

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItem::create(CC_CALLBACK_1(HelloWorld::MouseClickCallback, this));
	closeItem->setContentSize(visibleSize);
    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(menu, 1);

	auto label = LabelTTF::create("Press any key to continue...", "Arial", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height * 0.2f));
    
	label->setOpacity(0);
	label->setTag(1);

	// add the label as a child to this layer
    this->addChild(label, 1);

	auto fadeIn = FadeIn::create(FADE_TIME);
	auto fadeOut = FadeTo::create(FADE_TIME, 64);
	
	Sequence *pulseSequence = Sequence::createWithTwoActions(fadeIn, fadeOut);
	RepeatForever *repeat = RepeatForever::create(pulseSequence);
    
	label->runAction(repeat);
	
    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

	sprite->setTag(0);

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

	sprite->setOpacity(0);
	
	sprite->runAction(Sequence::create(FadeIn::create(FADE_TIME), 
		CallFunc::create([this]()
			{ 
				auto listener = EventListenerKeyboard::create();
				listener->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
				_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
			}
		),  nullptr )
	);

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);

    return true;
}

void HelloWorld::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{	
	auto newScene = MainMenu::createScene();
	auto transition = TransitionFade::create(FADE_TIME, newScene); 
	Director::getInstance()->replaceScene(transition);
}

void HelloWorld::MouseClickCallback(Ref* pSender)
{
	onKeyPressed(EventKeyboard::KeyCode::KEY_ENTER, nullptr);
}
