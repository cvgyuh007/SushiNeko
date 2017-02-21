#include "TimeBar.h"

using namespace cocos2d;
using namespace ui;

#define BACK_Z  0
#define FRONT_Z 1

bool TimeBar::init()
{
	m_bg = Sprite::createWithSpriteFrameName("life_bg.png");
	m_bg->setPosition(this->getPosition());
	this->setContentSize(m_bg->getContentSize());
	this->addChild(m_bg, BACK_Z);

	m_bar = LoadingBar::create("life.png", Widget::TextureResType::PLIST, 100.0f);
	m_bar->setPosition(this->getPosition());
	this->addChild(m_bar, FRONT_Z);

	return true;
}
