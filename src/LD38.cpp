#include <Engine/Factory.hpp>
#include "LD38.hpp"

LD38::LD38() : Game(1024, 576) {
	m_scene = new engine::Scene(this);
	m_windowTitle = "??? - Ludum Dare 38";
}

LD38::~LD38() {

}
