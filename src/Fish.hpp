//
// Created by iMer on 22.04.2017.
//

#ifndef LD38_FISH_HPP
#define LD38_FISH_HPP
#include <unordered_set>
#include <SFML/Audio.hpp>
#include "Buoyant.hpp"

class Fish: public Buoyant {
public:
	struct Drop {
		std::string script;
		float chance;
		sf::Vector2f position[2];
		std::unordered_set<engine::Node*> activeDrops;
		uint16_t max;
		std::shared_ptr<sf::Sound> sound;
	};
protected:
	std::vector<Drop> m_drops;
	engine::EventHandler<void, engine::Node*>* m_dropDeleteHandler;
	float m_dropTimer;
	std::unique_ptr<engine::BaseEventHandler> m_clickHandler;
	sf::Vector2f m_swimPower;
	float m_swimChance;
	bool m_shouldFlip;
	float m_pollutionTolerance;
	float m_health;
	bool m_dead;
	bool m_deadFloat;
public:
	Fish(engine::Scene* scene);
	virtual ~Fish();
	virtual bool CanDrop();

	virtual uint8_t GetType() const;

protected:
	virtual void OnUpdate(sf::Time interval);

public:
	virtual bool initialize(Json::Value& root);

	void TryDrop();

	void ChangeHealth(float amount);

	sf::Sound* m_swimSound;
};


#endif //LD38_FISH_HPP
