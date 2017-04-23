#include <Engine/Factory.hpp>
#include <src/Fish/Clam.hpp>
#include "LD38.hpp"
#include "Fish.hpp"
#include "Drop.hpp"
#include "Plant.hpp"
#include "SpeedButton.hpp"
#include "ShopItemBuy.hpp"
#include "ShopItemSell.hpp"
#include "BreedFish.hpp"
#include "FishEgg.hpp"

int main() {
	engine::Factory::RegisterType("fish", engine::Factory::CreateChildNode<Fish>);
	engine::Factory::RegisterType("clam", engine::Factory::CreateChildNode<Clam>);
	engine::Factory::RegisterType("drop", engine::Factory::CreateChildNode<Drop>);
	engine::Factory::RegisterType("plant", engine::Factory::CreateChildNode<Plant>);
	engine::Factory::RegisterType("speed_button", engine::Factory::CreateChildNode<SpeedButton>);
	engine::Factory::RegisterType("buoyant", engine::Factory::CreateChildNode<Buoyant>);
	engine::Factory::RegisterType("buy", engine::Factory::CreateChildNode<ShopItemBuy>);
	engine::Factory::RegisterType("sell", engine::Factory::CreateChildNode<ShopItemSell>);
	engine::Factory::RegisterType("breedfish", engine::Factory::CreateChildNode<BreedFish>);
	engine::Factory::RegisterType("fishegg", engine::Factory::CreateChildNode<FishEgg>);
	LD38 game;
	game.run();
}