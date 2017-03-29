#include "MainScene.h"

USING_NS_CC;
using namespace ui;

Scene* MainScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	float centerX = visibleSize.width / 2.0f;
	float centerY = visibleSize.height / 2.0f;

	//加载背景
	Sprite* bg = Sprite::create(IMAGES_PATH"background.png");
	bg->setPosition(centerX, centerY);
	this->addChild(bg);
	//加载图集
	SpriteFrameCache* cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile(IMAGES_PATH"neko.plist");
	cache->addSpriteFramesWithFile(IMAGES_PATH"sushi.plist");
	cache->addSpriteFramesWithFile(IMAGES_PATH"ui.plist");
	//创建场景物体
	float groundHeight = 50.0f;

	m_neko = Neko::create();
	m_neko->setPosition(centerX - m_neko->getContentSize().width / 2.0f, groundHeight);
	this->addChild(m_neko);

	m_sushiTower = SushiTower::create();
	m_sushiTower->setPosition(centerX, groundHeight + 20.0f/*offset*/);
	this->addChild(m_sushiTower);

	//创建UI
	m_uiManager = UIManager::create();
	this->addChild(m_uiManager);

	//绑定事件监听
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(MainScene::gameReady), "gameReady", nullptr);

	//绑定输入处理
	EventListenerMouse* mouseListener = EventListenerMouse::create();
	mouseListener->onMouseDown = CC_CALLBACK_1(MainScene::handleInput, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

    return true;
}

void MainScene::onEnter()
{
	Layer::onEnter();
	openMenu();
}

void MainScene::update(float delta)
{
	if (m_gameState == GameStateEnum::ePlaying)
	{
		m_restTime -= delta;
		m_uiManager->updateTimePercent((m_restTime / m_totalTime) * 100.0f);
		if (m_restTime <= 0.0f)
		{
			gameOver();
		}
	}
}

void MainScene::openMenu()
{
	m_uiManager->updateUIOnState(GameStateEnum::eMenu);
}

void MainScene::gameReady(Ref*)
{
	m_uiManager->updateUIOnState(GameStateEnum::eReady);
	resetScoreAndTime();
	m_gameState = GameStateEnum::eReady;
	this->scheduleUpdate();
}

void MainScene::gameStart()
{
	m_uiManager->updateUIOnState(GameStateEnum::ePlaying);
	m_gameState = GameStateEnum::ePlaying;
}

void MainScene::gameOver()
{
	m_uiManager->updateUIOnState(GameStateEnum::eGameOver);
	m_gameState = GameStateEnum::eGameOver;
	this->unscheduleUpdate();
}

void MainScene::handleInput(EventMouse* e)
{
	switch (m_gameState)
	{
	case GameStateEnum::eReady:
		if (e->getMouseButton() == 0)
		{
			m_neko->setSide(Side::eLeft);
		}
		else if (e->getMouseButton() == 1)
		{
			m_neko->setSide(Side::eRight);
		}

		if (m_neko->getSide() == m_sushiTower->getBottomSide())
		{
			gameOver();
			break;
		}

		m_neko->chop();
		if (m_neko->getSide() == Side::eLeft)
		{
			m_sushiTower->step(Side::eRight);
		}
		else if (m_neko->getSide() == Side::eRight)
		{
			m_sushiTower->step(Side::eLeft);
		}
		m_score++;
		m_uiManager->updateScore(m_score);

		if (m_neko->getSide() == m_sushiTower->getBottomSide())
		{
			gameOver();
			break;
		}

		gameStart();
		break;
	case GameStateEnum::ePlaying:
		if (e->getMouseButton() == 0)
		{
			m_neko->setSide(Side::eLeft);
		}
		else if (e->getMouseButton() == 1)
		{
			m_neko->setSide(Side::eRight);
		}

		if (m_neko->getSide() == m_sushiTower->getBottomSide())
		{
			gameOver();
			break;
		}

		m_neko->chop();
		if (m_neko->getSide() == Side::eLeft)
		{
			m_sushiTower->step(Side::eRight);
		}
		else if (m_neko->getSide() == Side::eRight)
		{
			m_sushiTower->step(Side::eLeft);
		}
		m_score++;
		m_restTime = m_totalTime;
		m_uiManager->updateScore(m_score);

		if (m_neko->getSide() == m_sushiTower->getBottomSide())
		{
			gameOver();
			break;
		}
		break;
	case GameStateEnum::eMenu:
	case GameStateEnum::eGameOver:
		break;
	}
}

void MainScene::resetScoreAndTime()
{
	m_score = 0;
	m_restTime = m_totalTime;
	m_uiManager->updateScore(m_score);
	m_uiManager->updateTimePercent((m_restTime / m_totalTime) * 100.0f);
}