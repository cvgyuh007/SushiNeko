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
	��˾�� �Ľӿڣ�
	1.��ȡ�ײ���˾������
	2.����һ����˾��
	*/
	Side getBottomSide() const { return m_sushies[0]->getSide(); }
	void step(Side side);
private:
	static constexpr unsigned int height = 10;//��˾���߶�
	std::vector<Sushi*> m_sushies;
	Side m_lastSide;
	Side getRandomSide();
};