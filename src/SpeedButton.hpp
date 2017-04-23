//
// Created by iMer on 23.04.2017.
//

#ifndef LD38_SPEEDBUTTON_HPP
#define LD38_SPEEDBUTTON_HPP

#include <memory>
#include <Engine/SpriteNode.hpp>

class SpeedButton: public engine::SpriteNode {
protected:
	std::unique_ptr<engine::BaseEventHandler> m_clickHandler;
	std::vector<float> m_speeds;
	size_t m_currentSpeed;
public:
	SpeedButton(engine::Scene* scene);
	virtual bool initialize(Json::Value& root);
	void IncreaseSpeed();

	void DecreaseSpeed();
	void UpdateSpeed();
};


#endif //LD38_SPEEDBUTTON_HPP
