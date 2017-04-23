//
// Created by iMer on 22.04.2017.
//

#ifndef LD38_BUOYANT_HPP
#define LD38_BUOYANT_HPP


#include <Engine/SpriteNode.hpp>

class Buoyant: public engine::SpriteNode {
protected:
	float m_buoyancy;
	bool m_inWater;
	float m_outOfWater;
public:
	Buoyant(engine::Scene* scene);

	virtual bool initialize(Json::Value& root);

protected:
	virtual void OnUpdate(sf::Time interval);

};


#endif //LD38_BUOYANT_HPP
