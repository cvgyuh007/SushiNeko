#pragma once
#include "cocos2d.h"
#include "ui\CocosGUI.h"
#include "GameState.h"
#include "TimeBar.h"

class UIManager final :public cocos2d::Node
{
private:
	UIManager() :
		Node()
	{}
public:
	CREATE_FUNC(UIManager);
	virtual bool init() override;

	void updateUIOnState(GameStateEnum state);

	void updateScore(unsigned int score) { m_scoreText->setText(cocos2d::Value(score).asString()); }
	void updateTimePercent(float percent) { m_timeBar->setPercent(percent); }
private:
	cocos2d::Sprite* m_gameMenuImage;	//游戏标题图片
	cocos2d::Sprite* m_gameOverImage;	//游戏结束图片
	cocos2d::Sprite* m_leftTapImage;
	cocos2d::Sprite* m_rightTapImage;
	cocos2d::Sprite* m_gameOverPanel;	//游戏结束背景图片
	cocos2d::ui::Button* m_startButton;	//开始按钮
	cocos2d::ui::Text* m_scoreText;		//分数文本
	TimeBar* m_timeBar;	//时间条

	void onMenu();
	void onReady();
	void onPlaying();
	void onGameOver();
};