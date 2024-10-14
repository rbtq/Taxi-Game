#include "glad/glad.h"
#include "sceneLayer.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

SceneLayer::SceneLayer(const char* name,std::vector<entt::entity>& entities, entt::registry& registry) 
	: Layer(name), m_entities(entities), m_registry(registry)
{

	m_entities.reserve(1000);

#pragma region RAW_DATA

	float pyramidVertices[8 * 16] = {
		//	 <------ Pos ------>  <--- normal --->	<---UV--->
			-0.5f, -0.5f, -0.5f,  0.f, -1.f, 0.f,	0.f, 0.f,//  square Magneta
			 0.5f, -0.5f, -0.5f,  0.f, -1.f, 0.f,	0.f, 0.5f,
			 0.5f, -0.5f,  0.5f,  0.f, -1.f, 0.f,	0.33f, 0.5f,
			-0.5f, -0.5f,  0.5f,  0.f, -1.f, 0.f,	0.33f, 0.f,

			-0.5f, -0.5f, -0.5f,  -0.8944f, 0.4472f, 0.0f,	0.33f, 0.f,  //triangle Green
			-0.5f, -0.5f,  0.5f,  -0.8944f, 0.4472f, 0.0f,	0.66f, 0.25f,
			 0.0f,  0.5f,  0.0f,  -0.8944f, 0.4472f, 0.0f,	0.33f, 0.5f,

			-0.5f, -0.5f,  0.5f,  0.0f, 0.4472f,0.8944f,	0.f, 0.f, //triangle Red
			 0.5f, -0.5f,  0.5f,  0.0f, 0.4472f,0.8944f,	0.f, 0.f,
			 0.0f,  0.5f,  0.0f,  0.0f, 0.4472f,0.8944f,	0.f, 0.f,

			 0.5f, -0.5f,  0.5f,  0.8944f, 0.4472f, 0.0f,	0.f, 0.f, //  triangle Yellow
			 0.5f, -0.5f, -0.5f,  0.8944f, 0.4472f, 0.0f,	0.f, 0.f,
			 0.0f,  0.5f,  0.0f,  0.8944f, 0.4472f, 0.0f,	0.f, 0.f,

			 0.5f, -0.5f, -0.5f,  0.0f, 0.4472f, -0.8944f,	0.f, 0.f,//  triangle Blue
			-0.5f, -0.5f, -0.5f,  0.0f, 0.4472f, -0.8944f,	0.f, 0.f,
			 0.0f,  0.5f,  0.0f,  0.0f, 0.4472f, -0.8944f,	0.f, 0.f,
	};

	

	uint32_t pyramidIndices[3 * 6] =
	{
		0, 1, 2,
		2, 3, 0,
		4, 5, 6,
		7, 8, 9,
		10, 11, 12,
		13, 14, 15
	};


	std::vector<uint32_t> cubeIndicies;
	std::vector<float> cubeVerticies;

	std::vector<uint32_t> cylinderIndicies;
	std::vector<float> cylinderVerticies;



	Engine::Loader::loadModelFile("assets/models/lettercube/letterCube.obj", cubeIndicies, cubeVerticies,true);

	Engine::Loader::loadModelFile("assets/models/cylinder.obj", cylinderIndicies, cylinderVerticies, true);



#pragma endregion

#pragma region GL_BUFFERS


	std::shared_ptr<Engine::VertexBuffer> cubeVBO;
	std::shared_ptr<Engine::IndexBuffer> cubeIBO;

	cubeVAO.reset(new Engine::VertexArray());

	Engine::VertexBufferLayout cubeBL = { Engine::ShaderDataType::Float3, Engine::ShaderDataType::Float3, Engine::ShaderDataType::Float2 };
	cubeVBO.reset(new Engine::VertexBuffer(cubeVerticies.data(), cubeVerticies.size() * sizeof(float), cubeBL));

	cubeIBO.reset(new Engine::IndexBuffer(cubeIndicies.data(), cubeIndicies.size()));

	cubeVAO->addVertexBuffer(cubeVBO);
	cubeVAO->setIndexBuffer(cubeIBO);

	// Unbind everything so we can't mess is up
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);



	std::shared_ptr<Engine::VertexBuffer> pyramidVBO;
	std::shared_ptr<Engine::IndexBuffer> pyramidIBO;

	pyramidVAO.reset(new Engine::VertexArray());
	Engine::VertexBufferLayout pyramidBL = { Engine::ShaderDataType::Float3, Engine::ShaderDataType::Float3, Engine::ShaderDataType::Float2 };
	pyramidVBO.reset(new Engine::VertexBuffer(pyramidVertices, sizeof(pyramidVertices), pyramidBL));

	pyramidIBO.reset(new Engine::IndexBuffer(pyramidIndices, 18));

	pyramidVAO->addVertexBuffer(pyramidVBO);
	pyramidVAO->setIndexBuffer(pyramidIBO);

	// Unbind everything so we can't mess is up
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	std::shared_ptr<Engine::VertexBuffer> cylinderVBO;
	std::shared_ptr<Engine::IndexBuffer> cylinderIBO;

	cylinderVAO.reset(new Engine::VertexArray());
	Engine::VertexBufferLayout cylinderBL = { Engine::ShaderDataType::Float3, Engine::ShaderDataType::Float3, Engine::ShaderDataType::Float2 };
	cylinderVBO.reset(new Engine::VertexBuffer(cylinderVerticies.data(), cylinderVerticies.size() * sizeof(float), cylinderBL));

	cylinderIBO.reset(new Engine::IndexBuffer(cylinderIndicies.data(), cylinderIndicies.size() * sizeof(float)));

	cylinderVAO->addVertexBuffer(cylinderVBO);
	cylinderVAO->setIndexBuffer(cylinderIBO);

	// Unbind everything so we can't mess is up
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

#pragma endregion

#pragma region SHADERS

	std::shared_ptr<Engine::OpenGLShader> FCShader;
	FCShader.reset(new Engine::OpenGLShader("./assets/shaders/flatColour.glsl"));

	std::shared_ptr<Engine::OpenGLShader> TPShader;
	TPShader.reset(new Engine::OpenGLShader("./assets/shaders/texturedPhong.glsl"));

	//std::shared_ptr<Engine::OpenGLShader> FCShader;
	//FCShader.reset(new Engine::OpenGLShader("./assets/shaders/flatColour.vert", "./assets/shaders/flatColour.frag"));

	//std::shared_ptr<Engine::OpenGLShader> TPShader;
	//TPShader.reset(new Engine::OpenGLShader("./assets/shaders/texturedPhong.vert", "./assets/shaders/texturedPhong.frag"));

#pragma endregion 

#pragma region TEXTURES

	std::shared_ptr<Engine::OpenGLTexture> letterTexture;
	letterTexture.reset(new Engine::OpenGLTexture("assets/textures/letterCube.png"));
	std::shared_ptr<Engine::OpenGLTexture> numberTexture;
	numberTexture.reset(new Engine::OpenGLTexture("assets/textures/numberCube.png"));

	std::shared_ptr<Engine::OpenGLTexture> moonTexture;
	moonTexture.reset(new Engine::OpenGLTexture("assets/textures/moon.png"));

	Engine::SubTexture letterSubTexture(letterTexture, { 0.f, 0.f }, { 1.0f, 0.5f });
	Engine::SubTexture numberSubTexture(numberTexture, { 0.f, 0.5f }, { 1.0f, 1.0f });
	//Engine::SubTexture moonEngine::SubTexture(moonTexture, { 0.5f, 0.0f }, { 1.0f, 1.0f });

	/*letterTexture->bindToSlot(0);
	numberTexture->bindToSlot(1);
	moonTexture->bindToSlot(2);*/

#pragma endregion


#pragma region MATERIALS

	pyramidMat.reset(new Engine::Material(TPShader, glm::vec4(0.f, 0.5f, 1.f, 1.f)));
	cubeMat.reset(new Engine::Material(TPShader, letterTexture));
	cube2Mat.reset(new Engine::Material(TPShader, numberTexture));
	cube3Mat.reset(new Engine::Material(TPShader));
	cylinderMat.reset(new Engine::Material(TPShader));

#pragma endregion

	m_entities.push_back(m_registry.create());
	m_entities.push_back(m_registry.create());
	m_entities.push_back(m_registry.create());
	m_entities.push_back(m_registry.create());
	m_entities.push_back(m_registry.create());

	m_registry.emplace<Engine::TransformComponent>(m_entities[0], glm::vec3(-2.f, 0.f, -6.f), glm::vec3(0.f), glm::vec3(1.f));
	m_registry.emplace<Engine::TransformComponent>(m_entities[1], glm::vec3(0.f, 0.f, -6.f), glm::vec3(0.f), glm::vec3(1.f));
	m_registry.emplace<Engine::TransformComponent>(m_entities[2], glm::vec3(2.f, 0.f, -6.f), glm::vec3(0.f), glm::vec3(1.f));
	m_registry.emplace<Engine::TransformComponent>(m_entities[3], glm::vec3(4.f, 0.f, -6.f), glm::vec3(0.f), glm::vec3(1.f));
	m_registry.emplace<Engine::TransformComponent>(m_entities[4], glm::vec3(-4.f, 0.f, -6.f), glm::vec3(0.f), glm::vec3(1.f));

	m_registry.emplace<Engine::RenderComponent>(m_entities[0], pyramidVAO, pyramidMat);
	m_registry.emplace<Engine::RenderComponent>(m_entities[1], cubeVAO, cubeMat);
	m_registry.emplace<Engine::RenderComponent>(m_entities[2], cubeVAO, cube2Mat);
	m_registry.emplace<Engine::RenderComponent>(m_entities[3], cylinderVAO, cylinderMat);
	m_registry.emplace<Engine::RenderComponent>(m_entities[4], cubeVAO, cube3Mat);

	m_registry.emplace<Engine::NativeScriptComponent>(m_entities[1]);
	m_registry.get<Engine::NativeScriptComponent>(m_entities[1]).create<RotationScript>(m_entities[1], glm::vec3(0.f, 1.f, 0.f), 10);

	glm::mat4 view = glm::lookAt(
		glm::vec3(0.f, 0.f, 0.f),
		glm::vec3(0.f, 0.f, -1.f),
		glm::vec3(0.f, 1.f, 0.f)
	);
	glm::mat4 projection = glm::perspective(glm::radians(45.f), 1024.f / 800.f, 0.1f, 100.f);

#pragma region CAMERAS

	Engine::FixedOrthoParams orthoParams;
	orthoParams.position = glm::vec3(0.f);
	orthoParams._near = -10.f;
	orthoParams._far = 10.f;
	//orthoParams.top = m_window->getHeight() / 2;
	orthoParams.bottom = -orthoParams.top;
	//orthoParams.right = m_window->getWidth() / 2;
	orthoParams.left = -orthoParams.right;

	std::shared_ptr<Engine::FixedOthroController> orthoCam;
	orthoCam.reset(new Engine::FixedOthroController(orthoParams));

	//Engine::FollowParams followParams;
	//followParams.entityTransform = &models[0];
	//followParams.offset = glm::vec3(0.f, 1.f, 4.f);
	//followParams.aspectRatio = 4.f / 3.f;
	//followParams.farClip = 100.f;
	//followParams.nearClip = 0.1f;
	//followParams.fovY = 45.f;


	//std::shared_ptr<Engine::FollowController> followCam;
	//followCam.reset(new Engine::FollowController(followParams));

	Engine::FreeEulerParams eulerParams;
	eulerParams.aspectRatio = 4.f / 3.f;
	eulerParams.farClip = 100.f;
	eulerParams.nearClip = 0.1f;
	eulerParams.fovY = 45.f;
	eulerParams.sensitivity = 100.f;
	eulerParams.speed = 5.f;
	//eulerParams.ScrHeight = m_window->getHeight();
	//eulerParams.ScrWidth = m_window->getWidth();

	std::shared_ptr<Engine::FreeEulerController> eulerCam;
	eulerCam.reset(new Engine::FreeEulerController(eulerParams));

	m_camera = eulerCam;

#pragma endregion


	Engine::UniformBufferLayout camLayout = { {"u_projection", Engine::ShaderDataType::Mat4},  {"u_view", Engine::ShaderDataType::Mat4} };


	cameraUBO.reset(new Engine::OpenGLUniformBuffer(camLayout));

	cameraUBO->attachShaderBlock(FCShader, "b_camera");
	cameraUBO->attachShaderBlock(TPShader, "b_camera");

	cameraUBO->uploadData("u_projection", glm::value_ptr(m_camera->getCamera().projection));
	cameraUBO->uploadData("u_view", glm::value_ptr(m_camera->getCamera().view));




	Engine::UniformBufferLayout lightsLayout = { {"u_lightPos", Engine::ShaderDataType::Float4}, {"u_viewPos", Engine::ShaderDataType::Float4}, {"u_lightColour", Engine::ShaderDataType::Float4} };


	lightsUBO.reset(new Engine::OpenGLUniformBuffer(lightsLayout));

	lightsUBO->attachShaderBlock(TPShader, "b_lights");


	lightsUBO->uploadData("u_lightPos", glm::value_ptr(lightPos));
	lightsUBO->uploadData("u_viewPos", glm::value_ptr(viewPos));
	lightsUBO->uploadData("u_lightColour", glm::value_ptr(lightColour));

}

void SceneLayer::onRender()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);



	auto view = m_registry.view<Engine::RenderComponent>();

	Engine::Renderer3D::begin(swu3D);

	for (auto entity : view) {
		auto& tc = m_registry.get<Engine::TransformComponent>(entity);
		auto& rc = m_registry.get<Engine::RenderComponent>(entity);
		Engine::Renderer3D::submit(rc.geometry, rc.material, tc.transform);
	}

	Engine::Renderer3D::end();
}

void SceneLayer::onUpdate(float timestep)
{
	
	auto view = m_registry.view<Engine::NativeScriptComponent>();

	for (auto entity : view) {
		m_registry.get<Engine::NativeScriptComponent>(entity).onUpdate(timestep);
	}

	glBindBuffer(GL_UNIFORM_BUFFER, cameraUBO->getRenderID());
	cameraUBO->uploadData("u_projection", glm::value_ptr(m_camera->getCamera().projection));
	cameraUBO->uploadData("u_view", glm::value_ptr(m_camera->getCamera().view));

	m_camera->onUpdate(timestep);
}
