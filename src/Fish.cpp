//
// Created by iMer on 22.04.2017.
//

#include <Engine/util/Random.hpp>
#include <Engine/Factory.hpp>
#include <Engine/Game.hpp>
#include <Engine/util/json.hpp>
#include "Fish.hpp"
#include "Level.hpp"

Fish::Fish(engine::Scene* scene) : Buoyant(scene), m_dropTimer(0), m_swimChance(-1), m_shouldFlip(false),
								   m_pollutionTolerance(0.5), m_health(100), m_dead(false) {
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
				if (m_dead) {
					Delete();
					return true;
				}
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
	m_swimPower = engine::vector2FromJson<float>(root["swim_power"]);
	m_swimChance = root.get("swim_chance", -1.0).asFloat();
	m_shouldFlip = root.get("should_flip", false).asBool();
	m_pollutionTolerance = root.get("pollution_tolerance", 0.5).asFloat();
	m_health = root.get("health", 100).asFloat();
	return true;
}

void Fish::OnUpdate(sf::Time interval) {
	Buoyant::OnUpdate(interval);
	if (m_dead) {
		return;
	}
	m_dropTimer += interval.asSeconds();
	while (m_dropTimer > 1) {
		m_dropTimer -= 1;
		TryDrop();
		// eeeh we're just gonna reuse the droptimer
		if (m_swimChance > 0 && m_body) {
			engine::RandomFloat<float> r(0, 1);
			if (r() < m_swimChance) {
				float angle = r() * engine::fPI * 2;
				m_body->ApplyLinearImpulseToCenter(b2Vec2(m_swimPower.x * cos(angle), m_swimPower.y * sin(angle)),
												   true);
				if (m_animations.find("swim") != m_animations.end()) {
					PlayAnimation("swim", "default");
				}
			}
		}
		auto level = static_cast<Level*>(m_scene);
		// still the drop timer \o/
		if (level->GetPollutionPct() > m_pollutionTolerance) {
			ChangeHealth(-3);
		} else {
			ChangeHealth(1);
		}
	}
	if (m_shouldFlip && m_body) {
		SetFlipped(m_body->GetLinearVelocity().x < 0);
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
			auto randomPos = engine::RandomVector(drop.position[0], drop.position[1]);
			if (IsFlipped()) {
				randomPos.x *= -1;
			}
			if (IsVFlipped()) {
				randomPos.y *= -1;
			}
			node->SetPosition(pos + randomPos);
			drop.activeDrops.insert(node);
			node->OnDelete.AddHandler(m_dropDeleteHandler);
		}
	}
}

bool Fish::CanDrop() {
	return true;
}

void Fish::ChangeHealth(float amount) {
	m_health += amount;
	sf::Color healthColor = sf::Color::White;
	if (m_health < 10) {
		healthColor.g = healthColor.b = 150;
	} else 	if (m_health < 30) {
		healthColor.g = healthColor.b = 200;
	}

	if (amount < 0) {
		MakeTween<sf::Color>(true, sf::Color::Red, healthColor, 0.5, [this](const sf::Color& c){
			SetColor(c);
		});
	}
	if (m_health < 0) {
		m_dead = true;
		m_buoyancy = 1.2;
		SetVFlipped(true);
	}
}
