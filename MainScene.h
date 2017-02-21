#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "GameState.h"
#include "Side.h"
#include "Neko.h"
#include "Sushi.h"
#include "SushiTower.h"
#include "UIManager.h"

#define IMAGES_PATH "images/"

class MainScene final: public cocos2d::Layer
{
private:
	MainScene() :
		Layer(),
		m_gameState(GameStateEnum::eMenu),
		m_neko(nullptr),
		m_uiManager(nullptr),
		m_score(0),
		m_totalTime(1.0f),
		m_restTime(m_totalTime)
	{}
public:
    static cocos2d::Scene* createScene();

    virtual bool init() override;
    
    // implement the "static create()" method manually
    CREATE_FUNC(MainScene);

private:
	virtual void onEnter() override;
	virtual void update(float delta) override;

	GameStateEnum m_gameState;//��Ϸ״̬

	void openMenu();
	void gameReady(cocos2d::Ref*);
	void gameStart();
	void gameOver();

	void handleInput(cocos2d::EventMouse *e);

	//��Ϸ����
	Neko* m_neko;				//è
	SushiTower* m_sushiTower;	//��˾��

	//UI
	UIManager* m_uiManager;

	//��Ϸ����
	unsigned int m_score;//����
	const float m_totalTime;
	float m_restTime;//ʣ��ʱ��
	void resetScoreAndTime();
};

#endif // __HELLOWORLD_SCENE_H__