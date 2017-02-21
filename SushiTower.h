#pragma once
#include <vector>
#include "cocos2d.h"
#include "Sushi.h"
#include "Side.h"

class SushiTower final :public cocos2d::Node
{
private:
	SushiTower() :Node(), m_lastSide(Side::eNone) {}
public:
	CREATE_FUNC(SushiTower);
	virtual bool init() override;

	/*
	寿司塔 的接口：
	1.获取底层寿司的左右
	2.更新一次寿司塔
	*/
	Side getBottomSide() const { return m_sushies[0]->getSide(); }
	void step(Side side);
private:
	static constexpr unsigned int height = 10;//寿司塔高度
	std::vector<Sushi*> m_sushies;
	Side m_lastSide;
	Side getRandomSide();
};