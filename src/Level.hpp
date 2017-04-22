#ifndef LD38_LEVEL_HPP
#define LD38_LEVEL_HPP


#include <Engine/Scene.hpp>

class Level: public engine::Scene {
protected:
	int64_t m_money;
public:
	Level(engine::Game* game);
	virtual ~Level();

	void AddMoney(int32_t i);
};


#endif //LD38_LEVEL_HPP
