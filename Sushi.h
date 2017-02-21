#pragma once
#include "cocos2d.h"
#include "Side.h"
#include "Entity.h"

class Sushi final : public Entity
{
private:
	Sushi() :
		Entity(Side::eNone),
		m_leftChopStick(nullptr),
		m_rightChopStick(nullptr)
	{}
public:
	CREATE_FUNC(Sushi);
	virtual bool init() override;

	virtual void setSide(Side side) override;
	void chopOut(Side side);
private:
	cocos2d::Sprite* m_leftChopStick;//×ó¿ê×Ó
	cocos2d::Sprite* m_rightChopStick;//ÓÒ¿ê×Ó
};