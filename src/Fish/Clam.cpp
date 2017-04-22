//
// Created by iMer on 22.04.2017.
//

#include <Engine/Scene.hpp>
#include "Clam.hpp"

Clam::Clam(engine::Scene* scene) : Fish(scene) {
}

void Clam::OnUpdate(sf::Time interval) {
	Fish::OnUpdate(interval);
	bool open = GetAnimationName() == "open";
	bool shouldOpen = false;
	if (CanDrop()) {
		for (Drop& drop : m_drops) {
			// Just assume all drops should make it open.. :D
			if (!drop.activeDrops.empty()) {
				shouldOpen = true;
				break;
			}
		}
	}
	if (shouldOpen != open) {
		PlayAnimation(shouldOpen ? "open" : "default");
	}
}

bool Clam::CanDrop() {
	auto vel = m_body->GetLinearVelocity();
	auto rot = engine::NormalizeAngleDeg(GetRotation());
	return engine::floatEqual(vel.x, 0, 0.001) && engine::floatEqual(vel.y, 0, 0.001) && (rot < 60 || rot > 300);
}
