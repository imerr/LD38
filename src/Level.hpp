#ifndef LD38_LEVEL_HPP
#define LD38_LEVEL_HPP


#include <Engine/Scene.hpp>
#include "ShopItem.hpp"

class Level: public engine::Scene {
protected:
	int64_t m_money;
	sf::Rect<float> m_waterRect;
	float m_pollution;
	float m_lastPollution;
	engine::SpriteNode* m_aquariumBack;
	engine::SpriteNode* m_aquariumFront;
	engine::Tween<sf::Color>* m_warningTween;
	ShopItem* m_activeShopItem;
	float m_saleTimer;
public:
	Level(engine::Game* game);
	virtual ~Level();

protected:
	virtual void OnUpdate(sf::Time interval);

	virtual void PostUpdate(sf::Time interval);

public:
	void AddMoney(int32_t amount);

	virtual bool initialize(Json::Value& root);

	bool InWater(sf::Vector2f point);

	void AddPollution(float pollution);

	virtual void OnInitializeDone();

	float GetPollutionPct() {
		return std::max(0.0f, std::min(1.0f, m_pollution/1000));
	}

	void SetActiveShopItem(ShopItem* item);
	ShopItem* GetActiveShopItem();

	int64_t GetMoney();

	sf::Vector2f GetSpawnPosition();

	void RefreshSale(bool special);
};


#endif //LD38_LEVEL_HPP
