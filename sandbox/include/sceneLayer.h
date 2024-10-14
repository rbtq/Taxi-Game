#pragma once
#include "core/layer.h"

#include <memory>
#include "engine.h"
#include "scripts/rotation.h"



class SceneLayer : public Engine::Layer
{
public:
	SceneLayer(const char * name, std::vector<entt::entity>& entities, entt::registry& registry);
	void onRender() override; //!< Runs when layer is Rendered
	void onUpdate(float timestep) override;  //!< Runs every frame
private:

	std::vector<entt::entity>& m_entities; //!< Our entites
	entt::registry& m_registry;

	std::shared_ptr<Engine::CameraController> m_camera; //!<Camera
	std::shared_ptr<Engine::OpenGLUniformBuffer> cameraUBO;
	std::shared_ptr<Engine::OpenGLUniformBuffer> lightsUBO;

	glm::mat4 models[3];

	std::shared_ptr<Engine::VertexArray> cubeVAO; //!<vertex array object for cubes
	std::shared_ptr<Engine::VertexArray> pyramidVAO; //!<vertex array object for pyramids
	std::shared_ptr<Engine::VertexArray> cylinderVAO; //!<vertex array object for cylinders

	glm::vec3 pos = glm::vec3(-2.0f, 0.f, -6.f);
	float rot = 0.f;

	std::shared_ptr<Engine::Material> pyramidMat;
	std::shared_ptr<Engine::Material> cubeMat;
	std::shared_ptr<Engine::Material> cube2Mat;
	std::shared_ptr<Engine::Material> cylinderMat;
	std::shared_ptr<Engine::Material> cube3Mat;

	Engine::SceneWideUniforms swu3D;

	glm::vec3 lightColour = glm::vec3(1.f, 1.f, 1.f);
	glm::vec3 lightPos = glm::vec3(1.f, 4.f, 6.f);
	glm::vec3 viewPos = glm::vec3(0.f, 0.f, 0.f);

};
