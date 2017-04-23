//
// Created by iMer on 23.04.2017.
//

#include "ShopItemSell.hpp"
#include "Level.hpp"
#include <Engine/Scene.hpp>
#include <Engine/ResourceManager.hpp>

ShopItemSell::ShopItemSell(engine::Scene* scene) : ShopItem(scene) {
	m_sellSound.reset(engine::ResourceManager::instance()->MakeSound("assets/sounds/coins.ogg"));
	m_errorSound.reset(engine::ResourceManager::instance()->MakeSound("assets/sounds/error.ogg"));
}

void ShopItemSell::OnClick() {
	auto n = m_scene->GetChildByID("aquariumContainer")->GetChildByID(m_lookFor);
	if (n) {
		n->Delete();
		static_cast<Level*>(m_scene)->AddMoney(m_price);
		m_sellSound->play();
	} else {
		m_errorSound->play();
	}
}

bool ShopItemSell::initialize(Json::Value& root) {
	if (!ShopItem::initialize(root)) {
		return false;
	}
	m_lookFor = root.get("look_for", "asdfghj").asString();
	return true;
}
