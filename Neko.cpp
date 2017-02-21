#include "Neko.h"

USING_NS_CC;

bool Neko::init()
{
	if (!Entity::init()) { return false; }

	//加载动画
	SpriteFrameCache* cache = SpriteFrameCache::getInstance();
	SpriteFrame* frame1 = cache->getSpriteFrameByName("neko_1.png");
	SpriteFrame* frame2 = cache->getSpriteFrameByName("neko_2.png");
	SpriteFrame* frame3 = cache->getSpriteFrameByName("neko_3.png");
	Animation* chopAnimation = Animation::createWithSpriteFrames({ frame1,frame2,frame3 }, 0.1f);
	chopAnimation->setRestoreOriginalFrame(true);
	m_chopAnimate = Animate::create(chopAnimation);
	m_chopAnimate->retain();
	//设置初始精灵
	setSprite(Sprite::createWithSpriteFrame(frame1));

	return true;
}

void Neko::chop()
{
	getSprite()->stopAllActions();
	getSprite()->runAction(m_chopAnimate->clone());
}

void Neko::setSide(Side side)
{
	assert(side != Side::eNone);
	if (getSide() == side) { return; }
	Entity::setSide(side);
	//沿X轴反转坐标和图像
	float centerX = Director::getInstance()->getVisibleSize().width / 2.0f;
	this->setPositionX(2 * centerX - this->getPositionX());
	this->setScaleX(-1 * this->getScaleX());
}
