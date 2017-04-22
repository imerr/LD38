//
// Created by iMer on 22.04.2017.
//

#include <Engine/util/Random.hpp>
#include <Engine/Factory.hpp>
#include <Engine/Game.hpp>
#include <Engine/util/json.hpp>
#include "Fish.hpp"
#include "Level.hpp"

Fish::Fish(engine::Scene* scene) : Buoyant(scene), m_dropTimer(0) {
	m_dropDeleteHandler = new engine::EventHandlerWrapper<void, engine::Node*>([this](engine::Node* node) {
		for (Drop& drop : m_drops) {
			if (drop.activeDrops.erase(node) > 0) {
				node->OnDelete.RemoveHandler(m_dropDeleteHandler);
				break;
			}
		}
	});
	m_clickHandler.reset(m_scene->GetGame()->OnMouseClick.MakeHandler(
			[this](const sf::Mouse::Button& button, const sf::Vector2f& pos, bool down) {
				return down && IsIn(pos.x, pos.y);
			}, [this](const sf::Mouse::Button& button, const sf::Vector2f& pos, bool down) {
				float a = engine::b2Angle(pos, m_scene->MeterToPixel(m_body->GetWorldCenter()));
				auto impulse = b2Vec2(2 * cos(a), 3 * sin(a));
				m_body->ApplyLinearImpulse(
						impulse,
						m_scene->PixelToMeter(pos),
						true);
				return true;
			}, this));
}

Fish::~Fish() {
	for (auto& drop : m_drops) {
		for (auto& dropNode : drop.activeDrops) {
			dropNode->OnDelete.RemoveHandler(m_dropDeleteHandler);
		}
	}
	m_scene->GetGame()->OnMouseClick.RemoveHandler(m_clickHandler.get());
}

bool Fish::initialize(Json::Value& root) {
	if (!Buoyant::initialize(root)) {
		return false;
	}
	for (auto& d : root["drops"]) {
		Drop drop{};
		drop.script = d.get("script", "").asString();
		if (drop.script == "") {
			std::cerr << "No script for drop - skipping" << std::endl;
			continue;
		}
		if (!d["position"].isArray() || d["position"].size() != 2) {
			std::cerr << "Position node not an array or doesnt have 2 elements" << std::endl;
			continue;
		}
		drop.position[0] = engine::vector2FromJson<float>(d["position"][0]);
		drop.position[1] = engine::vector2FromJson<float>(d["position"][1]);
		drop.chance = d.get("chance", 0.1).asFloat();
		drop.max = static_cast<uint16_t>(d.get("max", 100).asUInt());
		m_drops.push_back(drop);
	}
	m_buoyancy = root.get("buoyancy", 0.0).asFloat();
	return true;
}

void Fish::OnUpdate(sf::Time interval) {
	Buoyant::OnUpdate(interval);
	m_dropTimer += interval.asSeconds();
	while (m_dropTimer > 1) {
		m_dropTimer -= 1;
		TryDrop();
	}
}

void Fish::TryDrop() {
	if (!CanDrop()) {
		return;
	}
	engine::RandomFloat<float> r(0, 1);
	for (Drop& drop: m_drops) {
		if (drop.activeDrops.size() < drop.max && r() < drop.chance) {
			auto node = engine::Factory::CreateChildFromFile(drop.script, m_parent);
			auto pos = GetGlobalPosition();
			node->SetPosition(pos + engine::RandomVector(drop.position[0], drop.position[1]));
			drop.activeDrops.insert(node);
			node->OnDelete.AddHandler(m_dropDeleteHandler);
		}
	}
}

bool Fish::CanDrop() {
	return true;
}
