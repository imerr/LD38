//
// Created by iMer on 23.04.2017.
//

#include <Engine/util/Random.hpp>
#include <Engine/Factory.hpp>
#include "FishEgg.hpp"

FishEgg::FishEgg(engine::Scene* scene) : Buoyant(scene) {

}

void FishEgg::OnUpdate(sf::Time interval) {
	Buoyant::OnUpdate(interval);
	engine::RandomFloat<float> r(0, 1);
	if (r() < 0.03 * interval.asSeconds()) {
		auto n = engine::Factory::CreateChildFromFile(m_result, m_parent);
		n->SetPosition(GetPosition() - sf::Vector2f(0, 20));
		Delete();
	}
}
