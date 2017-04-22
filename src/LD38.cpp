#include <Engine/Factory.hpp>
#include "LD38.hpp"
#include "Level.hpp"

LD38::LD38() : Game(1024, 576) {
	m_scene = engine::Factory::create<Level>("assets/scripts/level.json", this);
	m_windowTitle = "A small world - Ludum Dare 38";
}

LD38::~LD38() {

}
