//
// Created by iMer on 22.04.2017.
//

#include <Engine/Text.hpp>
#include "Level.hpp"

Level::Level(engine::Game* game) : Scene(game), m_money(0) {

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
