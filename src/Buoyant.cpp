//
// Created by iMer on 22.04.2017.
//

#include "Buoyant.hpp"
#include "Level.hpp"

Buoyant::Buoyant(engine::Scene* scene) : SpriteNode(scene), m_buoyancy(0), m_inWater(true) {

}

void Buoyant::OnUpdate(sf::Time interval) {
	auto level = static_cast<Level*>(m_scene);
	bool inWater = level->InWater(m_scene->MeterToPixel(m_body->GetWorldCenter()));
	if (m_body && inWater) {
		m_body->ApplyForceToCenter(-m_buoyancy * m_body->GetMass() * m_scene->GetWorld()->GetGravity(), true);
	}
	if (inWater != m_inWater) {
		if (!m_inWater) {
			// TODO: Play sound
		}
		m_inWater = inWater;
	}
}

bool Buoyant::initialize(Json::Value& root) {
	if (!engine::SpriteNode::initialize(root)) {
		return false;
	}
	m_buoyancy = root.get("buoyancy", 0.0).asFloat();
	return true;
}
