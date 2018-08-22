#include "model.hpp"
#include "src/context/game_context.h"

namespace ecs
{
Component::CompType Model::comp_id = 4;


Model::~Model()
{
	model_sprite->removeFromParent();
}

void Model::create_model(const std::string& path)
{
	model_sprite = cocos2d::Sprite::create(path);
	// add to scene
	GameContext::running_scene->addChild(model_sprite);
}
} //ecs
