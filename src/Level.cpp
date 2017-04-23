//
// Created by iMer on 22.04.2017.
//

#include <Engine/Text.hpp>
#include <Engine/Game.hpp>
#include <Engine/util/json.hpp>
#include <Engine/SpriteNode.hpp>
#include <Engine/util/Random.hpp>
#include "Level.hpp"

Level::Level(engine::Game* game) : Scene(game), m_money(2000), m_pollution(0), m_aquariumBack(nullptr),
								   m_aquariumFront(nullptr), m_warningTween(nullptr), m_lastPollution(0),
								   m_activeShopItem(nullptr), m_saleTimer(0) {
}

Level::~Level() {
}

void Level::AddMoney(int32_t i) {
	m_money += i;
	if (m_money < 0) {
		m_money = 0;
	}
	auto moneyDisplay = m_ui->GetChildByID("money");
	if (moneyDisplay) {
		static_cast<engine::Text*>(moneyDisplay)->SetText(std::to_string(m_money));
	}
}


bool Level::initialize(Json::Value& root) {
	if (!engine::Scene::initialize(root)) {
		return false;
	}
	m_waterRect = engine::rectFromJson<float>(root["waterArea"]);
	return true;
}

bool Level::InWater(sf::Vector2f point) {
	return m_waterRect.contains(point);
}

void Level::AddPollution(float pollution) {
	m_pollution += pollution;
	float pollutionPct = GetPollutionPct();
	sf::Color color = engine::blendValueWithEasing(sf::Color::White, sf::Color(118, 40, 0), pollutionPct, 1,
												   engine::EasingLinear);
	if (m_aquariumBack) {
		m_aquariumBack->SetColor(color);
	}
	if (m_aquariumFront) {
		m_aquariumFront->SetColor(color);
	}
	auto pollutionDisplay = m_ui->GetChildByID("pollution");
	if (pollutionDisplay) {
		static_cast<engine::Text*>(pollutionDisplay)->SetText(
				std::to_string(static_cast<int>(pollutionPct * 100)) + "%");
	}
	if (pollutionPct > 0.5) {
		if (!m_warningTween) {
			m_warningTween = MakeTween<sf::Color>(true, sf::Color::White, sf::Color(255, 105, 45), 1,
												  [this](const sf::Color& value) {
													  auto pollutionDisplay = m_ui->GetChildByID("pollution");
													  if (pollutionDisplay) {
														  static_cast<engine::Text*>(pollutionDisplay)->SetColor(value);
													  }
												  }, engine::EasingLinear, true, true);
		}
	} else {
		if (m_warningTween) {
			m_warningTween->OnDone.Fire(m_warningTween);
			m_warningTween = nullptr;
		}
		if (pollutionDisplay) {
			static_cast<engine::Text*>(pollutionDisplay)->SetColor(sf::Color::White);
		}
	}
}

void Level::OnInitializeDone() {
	m_aquariumBack = static_cast<engine::SpriteNode*>(GetChildByID("aquariumBack"));
	m_aquariumFront = static_cast<engine::SpriteNode*>(GetChildByID("aquariumFront"));
}

void Level::PostUpdate(sf::Time interval) {
	auto up = m_ui->GetChildByID("pollution_up");
	auto down = m_ui->GetChildByID("pollution_down");
	if (up && down) {
		if (engine::floatEqual(m_pollution, m_lastPollution, 0.0001f)) {
			up->SetActive(false);
			down->SetActive(false);
		} else if (m_pollution > m_lastPollution) {
			up->SetActive(true);
			down->SetActive(false);
		} else {
			up->SetActive(false);
			down->SetActive(true);
		}
	}
	if (m_pollution < 0) {
		m_pollution = 0;
	}
	if (m_pollution > 1000) {
		m_pollution = 1000;
	}
	m_lastPollution = m_pollution;
}

void Level::SetActiveShopItem(ShopItem* item) {
	m_activeShopItem = item;
	auto info = m_ui->GetChildByID("item_info");
	if (!info) {
		return;
	}
	if (!item) {
		info->SetActive(false);
		return;
	}
	info->SetActive(true);
	auto title = static_cast<engine::Text*>(info->GetChildByID("title"));
	if (title) {
		title->SetText(std::to_string(item->GetPrice()) + "  " + item->GetName());
	}
	const auto& desc = m_activeShopItem->GetDescription();
	for (size_t i = 0; i < 5 ; i++) {
		auto line = static_cast<engine::Text*>(info->GetChildByID("line_" + std::to_string(i + 1)));
		if (!line) {
			break;
		}
		if (i >= desc.size()) {
			line->SetText("");
		} else {
			line->SetText(desc[i]);
		}
	}
}

ShopItem* Level::GetActiveShopItem() {
	return m_activeShopItem;
}

int64_t Level::GetMoney() {
	return m_money;
}

sf::Vector2f Level::GetSpawnPosition() {
	engine::RandomFloat<float> x(m_waterRect.left + 80,  m_waterRect.left + m_waterRect.width - 80);
	return sf::Vector2f(x(), -50);
}

void Level::OnUpdate(sf::Time interval) {
	m_saleTimer -= interval.asSeconds();
	if (m_saleTimer < 0) {
		m_saleTimer = 30;
		RefreshSale(true);
		RefreshSale(false);
	}
	auto sell = m_ui->GetChildByID("sell");
	if (sell) {
		auto time = static_cast<engine::Text*>(sell->GetChildByID("time"));
		if (time) {
			time->SetText(std::to_string(static_cast<int>(m_saleTimer)));
		}
	}
	engine::Scene::OnUpdate(interval);
}

void Level::RefreshSale(bool special) {
	auto sell = m_ui->GetChildByID("sell");
	if (sell) {
		auto n = sell->GetChildByID(special ? "special" : "normal");
		if (n && n->GetChildren().size() > 0) {
			for (auto& child : n->GetChildren()) {
				child->SetActive(false);
			}
			engine::RandomInt<size_t> r(0, n->GetChildren().size() - 1);
			n->GetChildren()[r()]->SetActive(true);
		}
	}
}
