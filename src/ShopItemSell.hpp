//
// Created by iMer on 23.04.2017.
//

#ifndef LD38_SHOPITEMSELL_HPP
#define LD38_SHOPITEMSELL_HPP


#include <SFML/Audio/Sound.hpp>
#include "ShopItem.hpp"

class ShopItemSell: public ShopItem {
protected:
	std::string m_lookFor;
	std::unique_ptr<sf::Sound> m_sellSound;
	std::unique_ptr<sf::Sound> m_errorSound;
public:
	ShopItemSell(engine::Scene* scene);

	virtual bool initialize(Json::Value& root);

	virtual void OnClick();

};


#endif //LD38_SHOPITEMSELL_HPP
