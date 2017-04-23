//
// Created by iMer on 23.04.2017.
//

#ifndef LD38_BREEDFISH_HPP
#define LD38_BREEDFISH_HPP


#include "Fish.hpp"

class BreedFish: public Fish {
protected:
	float m_fed;
	BreedFish* m_breedWith;
public:
	BreedFish(engine::Scene* scene);
	virtual ~BreedFish();
	virtual uint8_t GetType() const;

protected:
	virtual void OnUpdate(sf::Time interval);

public:
	bool CanEat() {
		return m_fed < 35;
	}
	bool CanBreed() {
		return m_fed > 40;
	}
	void UseFood() {
		m_fed -= 40;
	}
	void Eat() {
		m_fed += 30;
	}
	std::unique_ptr<engine::BaseEventHandler> m_collideHandler;

	void Breed(BreedFish* other);

};


#endif //LD38_BREEDFISH_HPP
