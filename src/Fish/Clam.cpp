//
// Created by iMer on 22.04.2017.
//

#include "Clam.hpp"

Clam::Clam(engine::Scene* scene) : Fish(scene) {

}

void Clam::OnUpdate(sf::Time interval) {
	Fish::OnUpdate(interval);
	bool open = GetAnimationName() == "open";
	bool shouldOpen = false;
	for (Drop& drop : m_drops) {
		// Just assume all drops should make it open.. :D
		if (!drop.activeDrops.empty()) {
			shouldOpen = true;
			break;
		}
	}
	if (shouldOpen != open) {
		PlayAnimation(shouldOpen ? "open" : "default");
	}
}
