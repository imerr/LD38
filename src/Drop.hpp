//
// Created by iMer on 22.04.2017.
//

#ifndef LD38_DROP_HPP
#define LD38_DROP_HPP

#include <SFML/Window/Mouse.hpp>
#include "Buoyant.hpp"

class Drop: public Buoyant {
protected:
	std::unique_ptr<engine::BaseEventHandler>  m_clickHandler;
	int32_t m_value;
	float m_pollution;
public:
	Drop(engine::Scene* scene);
	virtual ~Drop();

protected:
	virtual void OnUpdate(sf::Time interval);

public:
	void PickUp();

	virtual bool initialize(Json::Value& root);

};


#endif //LD38_DROP_HPP
