#ifndef LD38_CLAM_HPP
#define LD38_CLAM_HPP


#include "src/Fish.hpp"

class Clam: public Fish {
public:
	Clam(engine::Scene* scene);

	virtual bool CanDrop();

protected:
	virtual void OnUpdate(sf::Time interval);

};


#endif //LD38_CLAM_HPP
