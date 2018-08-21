#include "model.hpp"
#include "src/context/game_context.h"
Component::CompType Model::comp_id = 4;


Model::~Model()
{
	model_sprite->removeFromParent();
	delete model_sprite;
}

void Model::create_model(const std::string& path)
{
	model_sprite = cocos2d::Sprite::create(path);
	// add to scene
	GameContext::running_scene->addChild(model_sprite);
}

