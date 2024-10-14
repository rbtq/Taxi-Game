#include "scripts/rotation.h"

void RotationScript::onUpdate(float timeStep)
{
	glm::quat rotation(m_axis * m_rotationSpeed * timeStep);
	auto& tc = m_registry.get<Engine::TransformComponent>(m_entity);
	tc.rotation *= rotation;
	tc.reCalculate();
}