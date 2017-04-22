//
// Created by iMer on 22.04.2017.
//

#ifndef LD38_FISH_HPP
#define LD38_FISH_HPP
#include <unordered_set>

#include <Engine/SpriteNode.hpp>

class Fish: public engine::SpriteNode {
public:
	struct Drop {
		std::string script;
		float chance;
		sf::Vector2f position[2];
		std::unordered_set<engine::Node*> activeDrops;
		uint16_t max;
	};
protected:
	std::vector<Drop> m_drops;
	engine::EventHandler<void, engine::Node*>* m_dropDeleteHandler;
	float m_dropTimer;
	std::unique_ptr<engine::BaseEventHandler> m_clickHandler;
public:
	Fish(engine::Scene* scene);
	virtual ~Fish();

protected:
	virtual void OnUpdate(sf::Time interval);

public:
	virtual bool initialize(Json::Value& root);

	void TryDrop();

};


#endif //LD38_FISH_HPP
