#pragma once
#include "engine.h"

class RotationScript : public Engine::NativeScript {
public:
	RotationScript(entt::entity entity, glm::vec3 axis, float rotationSpeed) :
		Engine::NativeScript(entity), m_axis(axis), m_rotationSpeed(rotationSpeed) {}
	void onUpdate(float timeStep) override;
protected:
	glm::vec3 m_axis;
	float m_rotationSpeed;
};
