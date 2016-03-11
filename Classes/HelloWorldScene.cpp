#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
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
    /**  you can create scene with following comment code instead of using csb file.
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
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    **/
    
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
	auto edgeNode = Node::create();
	edgeNode->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	edgeNode->setPhysicsBody(edgeBody);
	addChild(edgeNode);
    
	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithFixedPriority(keyboardListener, -11);
	_keyboardListener = keyboardListener;

	m_pListener = EventListenerTouchOneByOne::create();
	m_pListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	m_pListener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	m_pListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(m_pListener, -10);

    auto rootNode = CSLoader::createNode("MainScene.csb");

    addChild(rootNode);

	cowSprite = Sprite::create("cow.png");
	cowSprite->setScale(0.2f);
	cowSprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	auto spriteBody = PhysicsBody::createCircle(cowSprite->getContentSize().width / 2, PHYSICSBODY_MATERIAL_DEFAULT);
	cowSprite->setPhysicsBody(spriteBody);
	cowSprite->setTag(1);
	addChild(cowSprite);

	//auto action = MoveBy::create(3, Point(100, 100));

	//sprite->runAction(action);

    return true;
}

void HelloWorld::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
	CC_UNUSED_PARAM(keyCode);

	CC_UNUSED_PARAM(event);

}

void HelloWorld::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
	if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE) {
		Director::getInstance()->end();
	}
}

bool HelloWorld::onTouchBegan(Touch * touch, Event * event)
{
	/*cowSprite->setPosition(touch->getLocation().x, touch->getLocation().y);*/
	//cowSprite->stopAllActions();
	//auto action = MoveTo::create(2, Point(touch->getLocation().x, touch->getLocation().y));
	//cowSprite->runAction(action);

	if (spriteVector.size() < MAX_SPRITE_NUM) {
		auto newSprite = Sprite::create("cow.png");
		newSprite->setScale(0.2f);
		newSprite->setPosition(touch->getLocation());
		auto physicsbody = PhysicsBody::createCircle(newSprite->getContentSize().width / 2, PHYSICSBODY_MATERIAL_DEFAULT);
		//auto physicsbody = PhysicsBody::createBox(newSprite->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
		newSprite->setPhysicsBody(physicsbody);

		this->addChild(newSprite);
		//spriteVector.pushBack(sprite);
	}

	return false;
}

void HelloWorld::onTouchMoved(Touch * touch, Event * event)
{
}

void HelloWorld::onTouchEnded(Touch * touch, Event * event)
{
}
