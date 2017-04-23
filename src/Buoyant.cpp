//
// Created by iMer on 22.04.2017.
//

#include <Engine/ResourceManager.hpp>
#include "Buoyant.hpp"
#include "Level.hpp"

Buoyant::Buoyant(engine::Scene* scene) : SpriteNode(scene), m_buoyancy(0), m_inWater(true), m_outOfWater(0) {
	m_splashSound.reset(engine::ResourceManager::instance()->MakeSound("assets/sounds/splash.ogg"));
}

void Buoyant::OnUpdate(sf::Time interval) {
	auto level = static_cast<Level*>(m_scene);
	bool inWater = level->InWater(m_scene->MeterToPixel(m_body->GetWorldCenter()));
	if (m_body && inWater) {
		m_body->ApplyForceToCenter(
				-m_buoyancy * m_body->GetMass() * m_body->GetGravityScale() * m_scene->GetWorld()->GetGravity(), true);
	}
	if (!inWater) {
		m_outOfWater += interval.asSeconds();
		if (m_outOfWater > 20) {
			Delete();
		}
	}
	if (inWater != m_inWater) {
		if (!m_inWater && m_outOfWater > 0.5f && m_splashSound.get()) {
			m_splashSound->play();
		}
		m_inWater = inWater;
	}
	if (inWater) {
		m_outOfWater = 0;
	}
}

bool Buoyant::initialize(Json::Value& root) {
	if (!engine::SpriteNode::initialize(root)) {
		return false;
	}
	m_buoyancy = root.get("buoyancy", 0.0).asFloat();
	return true;
}
