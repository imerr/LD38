//
// Created by iMer on 23.04.2017.
//

#ifndef LD38_FISHEGG_HPP
#define LD38_FISHEGG_HPP


#include "Buoyant.hpp"

class FishEgg: public Buoyant {
protected:
	std::string m_result;
public:
	FishEgg(engine::Scene* scene);
	void SetResult(std::string result) {
		m_result = result;
	}
protected:
	virtual void OnUpdate(sf::Time interval);
};


#endif //LD38_FISHEGG_HPP
