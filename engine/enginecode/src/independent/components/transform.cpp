#include <engine_pch.h>
#include "independent/components/transform.h"

namespace Engine {
	TransformComponent::TransformComponent(glm::vec3 p, glm::vec3 r, glm::vec3 s)
	{
		position = p;
		rotation = glm::quat(r);
		scale = s;
		reCalculate();
	}
	void TransformComponent::reCalculate()
	{
		glm::mat4 t = glm::translate(glm::mat4(1.f), position);
		glm::mat4 r = glm::toMat4(rotation);
		glm::mat4 s = glm::scale(glm::mat4(1.f), scale);

		transform = t * r * s;
	}
	void TransformComponent::reCalculate(glm::mat4 parent)
	{
		glm::mat4 t = glm::translate(glm::mat4(1.f), position);
		glm::mat4 r = glm::toMat4(rotation);
		glm::mat4 s = glm::scale(glm::mat4(1.f), scale);

		transform = parent * t * r * s;
	}
}