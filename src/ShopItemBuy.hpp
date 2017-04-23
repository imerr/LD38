//
// Created by iMer on 23.04.2017.
//

#ifndef LD38_SHOPITEMBUY_HPP
#define LD38_SHOPITEMBUY_HPP


#include <SFML/Audio/Sound.hpp>
#include "ShopItem.hpp"

class ShopItemBuy: public ShopItem {
protected:
	std::string m_itemScript;
	bool m_isPlant;
	int m_itemAmount;
	std::unique_ptr<sf::Sound> m_buySound;
	std::unique_ptr<sf::Sound> m_errorSound;
public:
	ShopItemBuy(engine::Scene* scene);

	virtual bool initialize(Json::Value& root);

	virtual void OnClick();

};


#endif //LD38_SHOPITEMBUY_HPP
