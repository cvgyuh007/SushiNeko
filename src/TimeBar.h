#pragma once
#include "cocos2d.h"
#include "ui\CocosGUI.h"

class TimeBar final:public cocos2d::Node
{
private:
	TimeBar() :
		Node(),
		m_bar(nullptr),
		m_bg(nullptr)
	{}
public:
	CREATE_FUNC(TimeBar);
	virtual bool init() override;

	void setPercent(float percent) { m_bar->setPercent(percent); }
private:
	cocos2d::ui::LoadingBar* m_bar;
	cocos2d::Sprite* m_bg;
};