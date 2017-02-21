#include "Sushi.h"

USING_NS_CC;

bool Sushi::init()
{
	if (!Entity::init()) { return false; }
	//我的精灵
	setSprite(Sprite::createWithSpriteFrameName("roll.png"));
	float sushiWidth = this->getContentSize().width;
	//左边筷子精灵
	m_leftChopStick = Sprite::createWithSpriteFrameName("chopstick.png");
	float chopStickWidth = m_leftChopStick->getContentSize().width;
	m_leftChopStick->setPosition(this->getPositionX() - (sushiWidth + chopStickWidth) / 2.0f, this->getPositionY());
	m_leftChopStick->setVisible(false);
	this->addChild(m_leftChopStick);
	//右边筷子精灵
	m_rightChopStick = Sprite::createWithSpriteFrameName("chopstick.png");
	m_rightChopStick->setScaleX(-1.0f);
	m_rightChopStick->setPosition(this->getPositionX() + (sushiWidth + chopStickWidth) / 2.0f, this->getPositionY());
	m_rightChopStick->setVisible(false);
	this->addChild(m_rightChopStick);

	return true;
}

void Sushi::setSide(Side side)
{
	if (getSide() == side) { return; }
	switch (side)
	{
	case Side::eLeft:
		m_leftChopStick->setVisible(true);
		m_rightChopStick->setVisible(false);
		break;
	case Side::eRight:
		m_leftChopStick->setVisible(false);
		m_rightChopStick->setVisible(true);
		break;
	default:
		m_leftChopStick->setVisible(false);
		m_rightChopStick->setVisible(false);
		break;
	}
	Entity::setSide(side);
}

void Sushi::chopOut(Side side)
{
	assert(side != Side::eNone);

	float direction = 0.0f;
	if (side == Side::eLeft)
	{
		direction = -1.0f;
	}
	else if (side == Side::eRight)
	{
		direction = 1.0f;
	}
	MoveBy* moveBy = MoveBy::create(0.5f, Vec2(direction * 100.0f, 20.0f));
	FadeOut* fadeOut = FadeOut::create(0.5f);
	Spawn* spawn = Spawn::createWithTwoActions(moveBy, fadeOut);
	CallFunc* callback = CallFunc::create([this] {this->removeFromParentAndCleanup(true); });
	Sequence* action = Sequence::createWithTwoActions(spawn, callback);
	getSprite()->runAction(action);
}
