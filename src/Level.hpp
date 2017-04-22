#ifndef LD38_LEVEL_HPP
#define LD38_LEVEL_HPP


#include <Engine/Scene.hpp>

class Level: public engine::Scene {
protected:
	int64_t m_money;
	sf::Rect<float> m_waterRect;
public:
	Level(engine::Game* game);
	virtual ~Level();

	void AddMoney(int32_t amount);

	virtual bool initialize(Json::Value& root);

	bool InWater(sf::Vector2f point);
};


#endif //LD38_LEVEL_HPP
