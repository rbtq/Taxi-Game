#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

namespace Engine {

	class TransformComponent {
	public:
		glm::vec3 position = glm::vec3(0.f);
		glm::quat rotation = glm::quat(glm::vec3(0.f));
		glm::vec3 scale = glm::vec3(1.f);
		glm::mat4 transform;

		TransformComponent(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);

		void reCalculate();
		void reCalculate(glm::mat4 parent);
	};

}
