//
// Created by iMer on 22.04.2017.
//

#include "Drop.hpp"
#include "Level.hpp"
#include <Engine/Game.hpp>

Drop::Drop(engine::Scene* scene) : Buoyant(scene) {
	m_clickHandler.reset(m_scene->GetGame()->OnMouseClick.MakeHandler(
			[this](const sf::Mouse::Button& button, const sf::Vector2f& pos, bool down) {
				for (int x = -4; x < 5; x += 2) {
					for (int y = -4; y < 5; y += 2) {
						if (IsIn(pos.x + x, pos.y + y)) {
							return true;
						}
					}
				}
				return false;
			}, [this](const sf::Mouse::Button& button, const sf::Vector2f& pos, bool down) {
				PickUp();
				return true;
			}, this));
}

Drop::~Drop() {
	m_scene->GetGame()->OnMouseClick.RemoveHandler(m_clickHandler.get());
}

void Drop::PickUp() {
	if (m_value) {
		static_cast<Level*>(m_scene)->AddMoney(m_value);
	}
	Delete();
}

bool Drop::initialize(Json::Value& root) {
	if (!Buoyant::initialize(root)) {
		return false;
	}
	auto d = root["drop"];
	m_value = d.get("value", 0).asInt();
	m_pollution = d.get("pollution", 0).asFloat();
	return true;
}

void Drop::OnUpdate(sf::Time interval) {
	Buoyant::OnUpdate(interval);
	if (m_inWater) {
		auto level = static_cast<Level*>(m_scene);
		level->AddPollution(m_pollution * interval.asSeconds());
	}
}

