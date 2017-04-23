//
// Created by iMer on 23.04.2017.
//

#include "SpeedButton.hpp"
#include <Engine/Game.hpp>
#include <sstream>

SpeedButton::SpeedButton(engine::Scene* scene) : SpriteNode(scene), m_currentSpeed(0), m_speeds{1} {
	m_clickHandler.reset(m_scene->GetGame()->OnMouseClick.MakeHandler(
			[this](const sf::Mouse::Button& button, const sf::Vector2f& pos, bool down) {
				return !down && IsIn(pos.x, pos.y);
			}, [this](const sf::Mouse::Button& button, const sf::Vector2f& pos, bool down) {
				switch (button) {
					case sf::Mouse::Left: {
						IncreaseSpeed();
						break;
					}
					case sf::Mouse::Right: {
						DecreaseSpeed();
						break;
					}
				}
				return true;
			}, this));
}

bool SpeedButton::initialize(Json::Value& root) {
	if (!engine::SpriteNode::initialize(root)) {
		return false;
	}
	m_speeds.clear();
	if (root["speeds"].isArray()) {
		for (auto& speed: root["speeds"]) {
			m_speeds.push_back(speed.asFloat());
		}
	} else {
		std::cerr << "Speeds isn't an array - cant set speeds for speed button" << std::endl;
	}
	if (m_speeds.size() == 0) {
		m_speeds.push_back(1);
	}
	UpdateSpeed();
	return true;
}

void SpeedButton::IncreaseSpeed() {
	m_currentSpeed++;
	if (m_currentSpeed == m_speeds.size()) {
		m_currentSpeed = 0;
	}
	UpdateSpeed();
}

void SpeedButton::UpdateSpeed() {
	if (m_currentSpeed > m_speeds.size()) {
		m_currentSpeed = m_currentSpeed % m_speeds.size();
	}
	m_scene->GetGame()->SetTimeScale(m_speeds[m_currentSpeed]);
	if (m_currentSpeed == 0) {
		PlayAnimation("default");
	} else {
		std::ostringstream ss;
		ss << m_speeds[m_currentSpeed];
		PlayAnimation(ss.str() + "x");
	}
}

void SpeedButton::DecreaseSpeed() {
	if (m_currentSpeed == 0) {
		m_currentSpeed = m_speeds.size();
	}
	m_currentSpeed--;
	UpdateSpeed();
}
