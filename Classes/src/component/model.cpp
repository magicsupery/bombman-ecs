#include "model.hpp"

Component::CompType Model::comp_id = 4;


Model::~Model()
{
	model_sprite->removeFromParent();
}

void Model::create_model(const std::string& path)
{
	auto sprite = cocos2d::Sprite::create(path);
	model_sprite = std::shared_ptr<cocos2d::Sprite>(sprite);

	// add to scene
	CCLOG("add p1 to the scene");
	cocos2d::Director::getInstance()->getRunningScene()->addChild(model_sprite.get());

	CCLOG("2 add p1 to the scene");
}

