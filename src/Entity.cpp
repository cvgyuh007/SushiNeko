#include "Entity.h"

void Entity::setSprite(cocos2d::Sprite* sprite)
{
	assert(sprite != nullptr);
	m_sprite = sprite;
	m_sprite->setPosition(this->getPosition());
	this->setContentSize(m_sprite->getContentSize());
	this->addChild(m_sprite);
}
