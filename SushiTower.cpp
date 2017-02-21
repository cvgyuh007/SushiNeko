#include "SushiTower.h"

USING_NS_CC;

bool SushiTower::init()
{
	if (!Node::init()) { return false; }
	//最底层要确保不能达成gameover
	Sushi* sushi = Sushi::create();
	sushi->setPosition(this->getPositionX(), this->getPositionY());
	sushi->setSide(Side::eNone);
	this->addChild(sushi);
	m_sushies.push_back(sushi);

	for (unsigned int i = 1; i < height; i++)
	{
		Sushi* sushi = Sushi::create();
		sushi->setPosition(this->getPositionX(), sushi->getContentSize().height/2.0f * i + this->getPositionY());
		sushi->setSide(getRandomSide());
		this->addChild(sushi);
		m_sushies.push_back(sushi);
	}
	return true;
}

void SushiTower::step(Side side)
{
	//打飞一节
	Sushi* sushi = Sushi::create();
	sushi->setPosition(m_sushies[0]->getPosition());
	this->addChild(sushi);
	sushi->chopOut(side);
	//所有寿司向下移动一节
	for (unsigned int i = 0; i < height - 1; i++)
	{
		m_sushies[i]->setSide(m_sushies[i + 1]->getSide());
	}
	//顶层再加一节
	m_sushies[height - 1]->setSide(getRandomSide());
}

Side SushiTower::getRandomSide()
{
	Side side;

	switch (m_lastSide)
	{
	case Side::eNone:
	{
		// generate a random number between 0.0f and 1.0f
		float random = CCRANDOM_0_1();

		// if there wasn't an obstacle in the last piece
		// then there's a 45% chance of there being one on the left
		// 45% chance of there being one on the right
		// and 10% chance of there being no obstacle
		if (random < 0.45f)
		{
			side = Side::eLeft;
		}
		else if (random < 0.9f)
		{
			side = Side::eRight;
		}
		else
		{
			side = Side::eNone;
		}
	}
	break;

	// if there was an obstacle in the last piece, then there isn't one for this piece
	case Side::eLeft:
	case Side::eRight:
		side = Side::eNone;
		break;
	}

	this->m_lastSide = side;
	return side;
}
