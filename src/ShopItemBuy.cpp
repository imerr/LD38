//
// Created by iMer on 23.04.2017.
//

#include <Engine/Factory.hpp>
#include "ShopItemBuy.hpp"
#include "Level.hpp"
#include <Engine/ResourceManager.hpp>

ShopItemBuy::ShopItemBuy(engine::Scene* scene) : ShopItem(scene), m_isPlant(false), m_itemAmount(1) {
	m_buySound.reset(engine::ResourceManager::instance()->MakeSound("assets/sounds/coins.ogg"));
	m_errorSound.reset(engine::ResourceManager::instance()->MakeSound("assets/sounds/error.ogg"));
}

bool ShopItemBuy::initialize(Json::Value& root) {
	if (!ShopItem::initialize(root)) {
		return false;
	}
	m_itemScript = root.get("item_script", "i forgot to put a script for the item to buy. whoops").asString();
	m_itemAmount = root.get("item_amount", 1).asInt();
	// we need some extra handling so plants are always in the background
	m_isPlant = root.get("is_plant", false).asBool();
	if (root["buy_sound"].isString()) {
		m_buySound.reset(engine::ResourceManager::instance()->MakeSound(root["buy_sound"].asString()));

	}

	return true;
}

void ShopItemBuy::OnClick() {
	auto level = static_cast<Level*>(m_scene);
	if (level->GetMoney() < m_price) {
		m_errorSound->play();
		return;
	}
	level->AddMoney(-m_price);
	m_buySound->play();
	// spawn thing
	auto container = level->GetChildByID("aquariumContainer");
	for (int i = 0; i < m_itemAmount; i++) {
		auto pos = level->GetSpawnPosition();
		if (m_isPlant) {
			container = container->GetChildByID("plants");
		}
		auto bought = engine::Factory::CreateChildFromFile(m_itemScript, container);
		if (bought) {
			bought->SetPosition(pos);
		}
	}
}
