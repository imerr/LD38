#include <Engine/Factory.hpp>
#include <src/Fish/Clam.hpp>
#include "LD38.hpp"
#include "Fish.hpp"
#include "Drop.hpp"
#include "Plant.hpp"

int main() {
	engine::Factory::RegisterType("fish", engine::Factory::CreateChildNode<Fish>);
	engine::Factory::RegisterType("clam", engine::Factory::CreateChildNode<Clam>);
	engine::Factory::RegisterType("drop", engine::Factory::CreateChildNode<Drop>);
	engine::Factory::RegisterType("plant", engine::Factory::CreateChildNode<Plant>);
	LD38 game;
	game.run();
}