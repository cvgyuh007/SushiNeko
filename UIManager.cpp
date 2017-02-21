#include "UIManager.h"

USING_NS_CC;
using namespace ui;

bool UIManager::init()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	float centerX = visibleSize.width / 2.0f;
	float centerY = visibleSize.height / 2.0f;

	m_gameOverPanel = Sprite::createWithSpriteFrameName("mat.png");
	m_gameOverPanel->setAnchorPoint(Vec2(0.5f, 1.0f));
	m_gameOverPanel->setPosition(centerX, visibleSize.height);
	this->addChild(m_gameOverPanel);
	m_gameOverPanel->setVisible(false);

	m_gameMenuImage = Sprite::createWithSpriteFrameName("title.png");
	m_gameMenuImage->setPosition(centerX, centerY + m_gameMenuImage->getContentSize().height);
	this->addChild(m_gameMenuImage);
	m_gameMenuImage->setVisible(false);

	m_gameOverImage = Sprite::createWithSpriteFrameName("gameOver.png");
	m_gameOverImage->setPosition(centerX, centerY + m_gameMenuImage->getContentSize().height);
	this->addChild(m_gameOverImage);
	m_gameOverImage->setVisible(false);

	m_leftTapImage = Sprite::createWithSpriteFrameName("tap_left.png");
	m_leftTapImage->setPosition(centerX - m_leftTapImage->getContentSize().width, m_leftTapImage->getContentSize().height);
	this->addChild(m_leftTapImage);
	m_leftTapImage->setVisible(false);

	m_rightTapImage = Sprite::createWithSpriteFrameName("tap_right.png");
	m_rightTapImage->setPosition(centerX + m_rightTapImage->getContentSize().width, m_rightTapImage->getContentSize().height);
	this->addChild(m_rightTapImage);
	m_rightTapImage->setVisible(false);

	m_startButton = Button::create("button.png", "buttonPressed.png", "", Widget::TextureResType::PLIST);
	m_startButton->setPosition(Vec2(centerX, centerY - m_startButton->getContentSize().height));
	m_startButton->addClickEventListener([](Ref* sender) {	NotificationCenter::getInstance()->postNotification("gameReady"); });
	this->addChild(m_startButton);
	m_startButton->setEnabled(false);
	m_startButton->setVisible(false);

	m_scoreText = Text::create("50", "fonts/Game of Three.ttf", 100);
	m_scoreText->setPosition(Vec2(centerX, centerY));
	this->addChild(m_scoreText);
	m_scoreText->setVisible(false);

	m_timeBar = TimeBar::create();
	m_timeBar->setAnchorPoint(Vec2(0, 1.0f));
	m_timeBar->setPosition(Vec2(centerX, visibleSize.height));
	this->addChild(m_timeBar);
	m_timeBar->setVisible(false);

	return true;
}

void UIManager::updateUIOnState(GameStateEnum state)
{
	switch (state)
	{
	case GameStateEnum::eMenu:
		onMenu();
		break;
	case GameStateEnum::eReady:
		onReady();
		break;
	case GameStateEnum::ePlaying:
		onPlaying();
		break;
	case GameStateEnum::eGameOver:
		onGameOver();
		break;
	}
}

void UIManager::onMenu()
{
	m_gameMenuImage->setVisible(true);
	m_gameOverImage->setVisible(false);
	m_leftTapImage->setVisible(false);
	m_rightTapImage->setVisible(false);
	m_gameOverPanel->setVisible(false);
	m_startButton->setVisible(true);
	m_startButton->setEnabled(true);
	m_scoreText->setVisible(false);
	m_timeBar->setVisible(false);
}

void UIManager::onReady()
{
	m_gameMenuImage->setVisible(false);
	m_gameOverImage->setVisible(false);
	m_leftTapImage->setVisible(true);
	m_rightTapImage->setVisible(true);
	m_gameOverPanel->setVisible(false);
	m_startButton->setVisible(false);
	m_startButton->setEnabled(false);
	m_scoreText->setVisible(true);
	m_timeBar->setVisible(true);
}

void UIManager::onPlaying()
{
	m_gameMenuImage->setVisible(false);
	m_gameOverImage->setVisible(false);
	m_leftTapImage->setVisible(false);
	m_rightTapImage->setVisible(false);
	m_gameOverPanel->setVisible(false);
	m_startButton->setVisible(false);
	m_startButton->setEnabled(false);
	m_scoreText->setVisible(true);
	m_timeBar->setVisible(true);
}

void UIManager::onGameOver()
{
	m_gameOverPanel->setVisible(true);
	MoveTo* fall = MoveTo::create(0.5f, m_gameOverPanel->getPosition());
	m_gameOverPanel->setPosition(m_gameOverPanel->getPositionX(), m_gameOverPanel->getPositionY() + m_gameOverPanel->getContentSize().height);
	CallFunc* callback = CallFunc::create([this] {
		m_gameMenuImage->setVisible(false);
		m_gameOverImage->setVisible(true);
		m_leftTapImage->setVisible(false);
		m_rightTapImage->setVisible(false);
		m_startButton->setVisible(true);
		m_startButton->setEnabled(true);
		m_scoreText->setVisible(true);
		m_timeBar->setVisible(true);
	});
	m_gameOverPanel->runAction(Sequence::createWithTwoActions(fall, callback));
}
