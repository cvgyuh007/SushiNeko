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
	cocos2d::Sprite* m_gameMenuImage;	//��Ϸ����ͼƬ
	cocos2d::Sprite* m_gameOverImage;	//��Ϸ����ͼƬ
	cocos2d::Sprite* m_leftTapImage;
	cocos2d::Sprite* m_rightTapImage;
	cocos2d::Sprite* m_gameOverPanel;	//��Ϸ��������ͼƬ
	cocos2d::ui::Button* m_startButton;	//��ʼ��ť
	cocos2d::ui::Text* m_scoreText;		//�����ı�
	TimeBar* m_timeBar;	//ʱ����

	void onMenu();
	void onReady();
	void onPlaying();
	void onGameOver();
};