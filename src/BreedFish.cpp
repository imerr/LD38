//
// Created by iMer on 23.04.2017.
//

#include <Engine/Scene.hpp>
#include <Engine/util/Random.hpp>
#include <Engine/Factory.hpp>
#include "BreedFish.hpp"
#include "misc.hpp.hpp"
#include "FishEgg.hpp"

BreedFish::BreedFish(engine::Scene* scene) : Fish(scene), m_fed(0), m_breedWith(nullptr) {
	m_collideHandler.reset(m_scene->OnContactPreSolve.MakeHandler([this](b2Contact* contact, const b2Manifold* manifold) {
		if (!contact->IsEnabled()) {
			return;
		}
		auto a = static_cast<engine::Node*>(contact->GetFixtureA()->GetBody()->GetUserData());
		auto b = static_cast<engine::Node*>(contact->GetFixtureB()->GetBody()->GetUserData());
		BreedFish* other = nullptr;
		if (a == this && b) {
			if (b->GetType() == NT_BREEDFISH) {
				other = static_cast<BreedFish*>(b);
			} else if (b->GetIdentifier() == "fishfood" && CanEat()) {
				b->Delete();
				Eat();
			}
		} else if (b == this && a) {
			if (a->GetType() == NT_BREEDFISH) {
				other = static_cast<BreedFish*>(a);
			}
		}
		if (other) {
			contact->SetEnabled(false);
			if (CanBreed() && other->CanBreed()) {
				m_breedWith = other;
			}
		}
	}));
}

uint8_t BreedFish::GetType() const {
	return NT_BREEDFISH;
}

void BreedFish::OnUpdate(sf::Time interval) {
	Fish::OnUpdate(interval);
	if (m_fed > 0) {
		m_fed -= interval.asSeconds() / 3;
	}
	if (m_breedWith) {
		if (CanBreed() && m_breedWith->CanBreed()) {
			Breed(m_breedWith);
		}
		m_breedWith = nullptr;
	}
}

void BreedFish::Breed(BreedFish* other) {
	other->UseFood();
	UseFood();

	auto m = GetIdentifier();
	auto o = other->GetIdentifier();
	std::string result;
	if (m == "goldfish_red" && o == "goldfish_green") {
		result = "goldfish_yellow";
	} else if (m == "goldfish_blue" && o == "goldfish_green") {
		result = "goldfish_turquoise";
	} else if (m == "goldfish_red" && o == "goldfish_blue") {
		result = "goldfish_purple";
	} else if (m == "goldfish_yellow" && o == "goldfish_purple") {
		result = "goldfish_red";
	} else if (m == "goldfish_turquoise" && o == "goldfish_pink") {
		result = "goldfish_blue";
	} else if (m == "goldfish_turquoise" && o == "goldfish_yellow") {
		result = "goldfish_green";
	} else {
		engine::RandomInt<int> r(0,1);
		if (r() == 1) {
			result = o;
		} else {
			result = m;
		}
	}
	auto fe = static_cast<FishEgg*>(engine::Factory::CreateChildFromFile("assets/scripts/fish_fishegg.json", m_parent));
	fe->SetResult("assets/scripts/fish_" + result + ".json");
	fe->SetPosition(GetPosition());
}

BreedFish::~BreedFish() {
	m_scene->OnContactPreSolve.RemoveHandler(m_collideHandler.get());
}
