#pragma once
#include "cocos2d.h"
#include "Side.h"

class Entity :public cocos2d::Node
{
protected:
	Entity(Side side) :
		Node(),
		m_sprite(nullptr),
		m_side(side)
	{}
public:
	virtual ~Entity() {}
	virtual void setSide(Side side) { m_side = side; }
	Side getSide() const { return m_side; }

protected:
	void setSprite(cocos2d::Sprite* sprite);
	cocos2d::Sprite* getSprite() { return m_sprite; }
	const cocos2d::Sprite* getSprite() const { return m_sprite; }

private:
	cocos2d::Sprite* m_sprite;//我的精灵
	Side m_side;	//当前所在左右
};