#pragma once
#include "cocos2d.h"
#include "Side.h"
#include "Entity.h"

class Neko final:public Entity
{
private:
	Neko() :
		Entity(Side::eLeft),
		m_chopAnimate(nullptr)
	{}
	virtual ~Neko()
	{
		m_chopAnimate->release();
	}
public:
	CREATE_FUNC(Neko);
	virtual bool init() override;

	void chop();
	virtual void setSide(Side side) override;
private:
	cocos2d::Animate* m_chopAnimate;//¿³µÄ¶¯»­
};