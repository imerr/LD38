//
// Created by iMer on 23.04.2017.
//

#ifndef LD38_PLANT_HPP
#define LD38_PLANT_HPP


#include "Buoyant.hpp"

class Plant: public Buoyant {
protected:
	float m_cleaning;
public:
	Plant(engine::Scene* scene);

	virtual bool initialize(Json::Value& root);

protected:
	virtual void OnUpdate(sf::Time interval);
};


#endif //LD38_PLANT_HPP
