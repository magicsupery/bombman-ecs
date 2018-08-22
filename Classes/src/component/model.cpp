#include "model.hpp"
#include "../context/game_context.h"
#include "../helper/const.hpp"
namespace ecs
{
Component::CompType Model::comp_id = COMPONENT_ID_MODEL;


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
