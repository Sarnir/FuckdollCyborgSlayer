#ifndef __MAINMENU_SCENE_H__
#define __MAINMENU_SCENE_H__

#include "cocos2d.h"

class MainMenu : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

	// a selector callbacks
	void newGameCallback(cocos2d::Ref* pSender);
    void quitGameCallback(cocos2d::Ref* pSender);
    
	virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    // implement the "static create()" method manually
    CREATE_FUNC(MainMenu);

private:
	void selectMenuItem(cocos2d::MenuItem* selectedItem);

	cocos2d::MenuItemLabel* newGameItem;
	cocos2d::MenuItemLabel* optionsItem;
	cocos2d::MenuItemLabel* quitItem;

	cocos2d::MenuItem* selectedMenuItem;
};

#endif // __HELLOWORLD_SCENE_H__
