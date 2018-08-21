#ifndef _HPP_MODEL_HPP_
#define _HPP_MODEL_HPP_

#include "../ecs/component.h"

#include "cocos2d.h"

using SpritePtr=
	std::shared_ptr<cocos2d::Sprite>;

class Model: public Component
{
public:
	virtual std::string name() {return "Model";}
	~Model();
public:
	virtual Component::CompType getCompId() {return Model::comp_id;}
	static Component::CompType comp_id;

public:
	void create_model(const std::string& path);

public:
	SpritePtr model_sprite;
};
#endif
