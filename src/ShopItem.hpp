//
// Created by iMer on 23.04.2017.
//

#ifndef LD38_SHOPITEM_HPP
#define LD38_SHOPITEM_HPP


#include <Engine/SpriteNode.hpp>

class ShopItem: public engine::SpriteNode {
protected:
	std::unique_ptr<engine::BaseEventHandler> m_clickHandler;
	int32_t m_price;
	std::string m_name;
	std::vector<std::string> m_description;
public:
	ShopItem(engine::Scene* scene);
	virtual ~ShopItem();
	int32_t GetPrice() const {
		return m_price;
	};
	const std::string& GetName() const {
		return m_name;
	};
	const std::vector<std::string>& GetDescription() const {
		return m_description;
	};
protected:
	virtual void OnUpdate(sf::Time interval);

public:
	virtual bool initialize(Json::Value& root);

	virtual void OnClick();
};


#endif //LD38_SHOPITEM_HPP
