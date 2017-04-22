//
// Created by iMer on 22.04.2017.
//

#include "Drop.hpp"
#include "Level.hpp"
#include <Engine/Game.hpp>

Drop::Drop(engine::Scene* scene) : SpriteNode(scene) {
	m_clickHandler = m_scene->GetGame()->OnMouseClick.MakeHandler(
			[this](const sf::Mouse::Button& button, const sf::Vector2f& pos, bool down) {
				return IsIn(pos.x, pos.y);
			}, [this](const sf::Mouse::Button& button, const sf::Vector2f& pos, bool down) {
				PickUp();
				return true;
			}, this);
}

Drop::~Drop() {
	m_scene->GetGame()->OnMouseClick.RemoveHandler(m_clickHandler);
}

bool Drop::IsIn(float x, float y) {
	if (m_body) {
		auto f = m_body->GetFixtureList();
		while (f) {
			if (f->TestPoint(b2Vec2(x / m_scene->GetPixelMeterRatio(), y / m_scene->GetPixelMeterRatio()))) {
				return true;
			}
			f = f->GetNext();
		}
	} else {
		sf::Rect<float> r;
		r = GetGlobalTransform().transformRect(r);
		r.contains(x, y);
	}
	return false;
}

void Drop::PickUp() {
	if (m_value) {
		static_cast<Level*>(m_scene)->AddMoney(m_value);
	}
	Delete();
}

bool Drop::initialize(Json::Value& root) {
	if (!engine::SpriteNode::initialize(root)) {
		return false;
	}
	auto d = root["drop"];
	m_value = d.get("value", 0).asInt();
	return true;
}

