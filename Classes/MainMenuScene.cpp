#include "MainMenuScene.h"
#include "IngameScene.h"

USING_NS_CC;

#define FADE_TIME 1.0f

enum eMainMenuItems
{
	newGame,
	options,
	quitGame
};

Scene* MainMenu::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainMenu::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainMenu::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
	scheduleUpdate();

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto label = LabelTTF::create("Main Menu", "Arial", 36);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height * 0.8f));

	// add the label as a child to this layer
    this->addChild(label, 1);

	/*auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
										   
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));*/
    
	auto newGameLabel = LabelTTF::create("New Game", "Arial", 24);
	auto optionsLabel = LabelTTF::create("Options", "Arial", 24);
	auto quitLabel = LabelTTF::create("Quit", "Arial", 24);

	newGameItem = MenuItemLabel::create(newGameLabel, CC_CALLBACK_1(MainMenu::newGameCallback, this));
	optionsItem = MenuItemLabel::create(optionsLabel);
	quitItem = MenuItemLabel::create(quitLabel, CC_CALLBACK_1(MainMenu::quitGameCallback, this));

	newGameItem->setTag(eMainMenuItems::newGame);
	optionsItem->setTag(eMainMenuItems::options);
	quitItem->setTag(eMainMenuItems::quitGame);

	selectedMenuItem = nullptr;
	selectMenuItem(newGameItem);

    // create menu, it's an autorelease object
	auto menu = Menu::create(newGameItem, optionsItem, quitItem, NULL);
	menu->alignItemsVerticallyWithPadding(10.0f);
    menu->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height * 0.5f));
    this->addChild(menu, 1);

	auto listener = EventListenerKeyboard::create();
				listener->onKeyReleased = CC_CALLBACK_2(MainMenu::onKeyReleased, this);
				_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

void MainMenu::newGameCallback(Ref* pSender)
{
	selectMenuItem(newGameItem);
	onKeyReleased(EventKeyboard::KeyCode::KEY_ENTER, nullptr);
}

void MainMenu::quitGameCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void MainMenu::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{	
	if(keyCode == EventKeyboard::KeyCode::KEY_ENTER || keyCode == EventKeyboard::KeyCode::KEY_KP_ENTER)
	{
		Scene* newScene = nullptr;
	
		switch (selectedMenuItem->getTag())
		{
		case eMainMenuItems::newGame:
			newScene = IngameScene::createScene();
			break;
		case eMainMenuItems::options:
			break;
		case eMainMenuItems::quitGame:
			quitGameCallback(this);
			return;
		default:
			break;
		}

		auto transition = TransitionFade::create(FADE_TIME, newScene); 
		Director::getInstance()->replaceScene(transition);
	}
	else if(keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW)
	{
		if(selectedMenuItem->getTag() == eMainMenuItems::options)
			selectMenuItem(newGameItem);
		else if(selectedMenuItem->getTag() == eMainMenuItems::quitGame)
			selectMenuItem(optionsItem);
	}
	else if(keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW)
	{
		if(selectedMenuItem->getTag() == eMainMenuItems::newGame)
			selectMenuItem(optionsItem);
		else if(selectedMenuItem->getTag() == eMainMenuItems::options)
			selectMenuItem(quitItem);
	}
}

void MainMenu::selectMenuItem(MenuItem* selectedItem)
{
	if(selectedMenuItem != nullptr)
		selectedMenuItem->setColor(Color3B(255, 255, 255));

	selectedMenuItem = selectedItem;
	selectedMenuItem->setColor(Color3B(255, 255, 0));
}