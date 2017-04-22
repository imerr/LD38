//
// Created by iMer on 22.04.2017.
//

#ifndef LD38_DROP_HPP
#define LD38_DROP_HPP


#include <Engine/SpriteNode.hpp>

class Drop: public engine::SpriteNode {
protected:
	engine::BaseEventHandler* m_clickHandler;
	int32_t m_value;
public:
	Drop(engine::Scene* scene);
	virtual ~Drop();

	bool IsIn(float x, float y);

	void PickUp();

	virtual bool initialize(Json::Value& root);

};


#endif //LD38_DROP_HPP
