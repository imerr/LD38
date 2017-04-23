#ifndef LD38_LEVEL_HPP
#define LD38_LEVEL_HPP


#include <Engine/Scene.hpp>

class Level: public engine::Scene {
protected:
	int64_t m_money;
	sf::Rect<float> m_waterRect;
	float m_pollution;
	engine::SpriteNode* m_aquariumBack;
	engine::SpriteNode* m_aquariumFront;
	engine::Tween<sf::Color>* m_warningTween;
public:
	Level(engine::Game* game);
	virtual ~Level();

	void AddMoney(int32_t amount);

	virtual bool initialize(Json::Value& root);

	bool InWater(sf::Vector2f point);

	void AddPollution(float pollution);

	virtual void OnInitializeDone();

	float GetPollutionPct() {
		return std::min(1.0f, m_pollution/1000);
	}
};


#endif //LD38_LEVEL_HPP
