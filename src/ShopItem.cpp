//
// Created by iMer on 23.04.2017.
//

#include "ShopItem.hpp"
#include "Level.hpp"
#include <Engine/Game.hpp>

ShopItem::ShopItem(engine::Scene* scene) : SpriteNode(scene) {
	m_clickHandler.reset(m_scene->GetGame()->OnMouseClick.MakeHandler(
			[this](const sf::Mouse::Button& button, const sf::Vector2f& pos, bool down) {
				return IsActive() && !down && button == sf::Mouse::Left && IsIn(pos.x, pos.y);
			}, [this](const sf::Mouse::Button& button, const sf::Vector2f& pos, bool down) {
				OnClick();
				return true;
			}, this));
}

void ShopItem::OnUpdate(sf::Time interval) {
	auto level = static_cast<Level*>(m_scene);
	auto active = level->GetActiveShopItem();
	auto mousePos = level->GetGame()->GetMousePosition();
	bool in = IsIn(mousePos.x, mousePos.y);
	if (in && active != this) {
		level->SetActiveShopItem(this);
	}
	if (!in && active == this) {
		level->SetActiveShopItem(nullptr);
	}
}

ShopItem::~ShopItem() {
	m_scene->GetGame()->OnMouseClick.RemoveHandler(m_clickHandler.get());
	auto level = static_cast<Level*>(m_scene);
	if (level->GetActiveShopItem() == this)  {
		level->SetActiveShopItem(nullptr);
	}
}

bool ShopItem::initialize(Json::Value& root) {
	if (!engine::SpriteNode::initialize(root)) {
		return false;
	}
	m_price = root.get("price", 1).asUInt();
	m_name = root.get("name", "i should put a name for this item").asString();
	m_description.clear();
	for (auto& desc : root["description"]) {
		m_description.push_back(desc.asString());
	}
	return true;
}

void ShopItem::OnClick() {

}
