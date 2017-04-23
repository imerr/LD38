//
// Created by iMer on 23.04.2017.
//

#include "Plant.hpp"
#include "Level.hpp"

Plant::Plant(engine::Scene* scene) : Buoyant(scene), m_cleaning(1) {

}

void Plant::OnUpdate(sf::Time interval) {
	Buoyant::OnUpdate(interval);
	static_cast<Level*>(m_scene)->AddPollution(-m_cleaning * interval.asSeconds());
}

bool Plant::initialize(Json::Value& root) {
	if (!Buoyant::initialize(root)) {
		return false;
	}
	m_cleaning = root.get("cleaning", 1).asFloat();
	return true;
}
