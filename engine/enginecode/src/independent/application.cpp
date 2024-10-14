/** \file application.cpp
*/

#include "engine_pch.h"
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <filesystem>
#include "core/application.h"


#ifdef NG_PLATFORM_WINDOWS
#include "platform/windows/winTimer.h"
#include "platform/GLFW/GLFWWindowImp.h"
#endif

#ifdef NG_PLATFORM_WINDOWS
#include "platform/GLFW/GLFWSystem.h"
#endif

#include "platform/OpenGL//vertexArray.h"
#include "platform/OpenGL/OpenGLShader.h"
#include "platform/OpenGL/OpenGLTexture.h"
#include "rendering/Renderer3D.h"
#include "rendering/Renderer2D.h"
#include "platform/OpenGL/OpenGLUniformBuffer.h"
#include "cameras/FixedOrthoController.h"
#include "cameras/FreeEulerController.h"
#include "cameras/FollowController.h"



namespace Engine {
	// Set static vars
	Application* Application::s_instance = nullptr;

	Application::Application()
	{
		if (s_instance == nullptr)
		{
			s_instance = this;
		}

		// Start systems

		// Start log
		m_logSystem.reset(new Log);
		m_logSystem->start();

		//Start the windows System
#ifdef NG_PLATFORM_WINDOWS
		m_windowsSystem.reset(new GLFWSystem);
#endif
		m_windowsSystem->start();


		// reset timer
#ifdef NG_PLATFORM_WINDOWS
		m_timer.reset(new WinTimer);
#else
		m_timer.reset(new ChronoTimer);
#endif
		m_timer->start();

		WindowProperties props("My Game Engine", 1024, 800);
		m_window.reset(WindowBase::create(props));

		// Set up callbacks
		m_window->getEventHandler().setOnWinClose(std::bind(&Application::onClose, this, std::placeholders::_1));
		m_window->getEventHandler().setOnWinResize(std::bind(&Application::onResize, this, std::placeholders::_1));
		m_window->getEventHandler().setOnWinMoved(std::bind(&Application::onMove, this, std::placeholders::_1));
		m_window->getEventHandler().setOnKeyPressed(std::bind(&Application::onKeyPressed, this, std::placeholders::_1));
		m_window->getEventHandler().setOnKeyReleased(std::bind(&Application::onKeyReleased, this, std::placeholders::_1));
		m_window->getEventHandler().setOnMouseButtonPressed(std::bind(&Application::onMouseButtonPressed, this, std::placeholders::_1));
		m_window->getEventHandler().setOnMouseButtonReleased(std::bind(&Application::onMouseButtonReleased, this, std::placeholders::_1));
		m_window->getEventHandler().setOnMouseMoved(std::bind(&Application::onMouseMove, this, std::placeholders::_1));

		// Set input poller
		InputPoller::setNativeWindow(m_window->getNativeWindow());

		Renderer3D::init();
		Renderer2D::init();
		
	}

	void Application::onClose(WindowCloseEvent& e)
	{
		Log::info("Shutting down");
		m_running = false;
	}

	bool Application::onResize(WindowResizeEvent& e)
	{
		e.handle(true);
		//Log::info("Window Resize event: ({0}, {1})", e.getWidth(), e.getHeight());
		return e.handled();;
	}

	bool Application::onMove(WindowMovedEvent& e)
	{
		e.handle(true);
		//Log::info("Window Move event: ({0}, {1})", e.getX(), e.getY());
		return e.handled();;
	}

	bool Application::onKeyPressed(KeyPressedEvent& e)
	{
		e.handle(true);
		//Log::info("Key pressed event: key: {0}, repeat: {1}", e.getKeyCode(), e.getRepeatCount());
		return e.handled();;
	}

	bool Application::onKeyReleased(KeyReleasedEvent& e)
	{
		e.handle(true);
		//Log::info("Key released event: key: {0}", e.getKeyCode());
		return e.handled();;
	}

	bool Application::onMouseButtonPressed(MouseButtonPressedEvent& e)
	{
		e.handle(true);
		//Log::info("Mouse button pressed event: key: {0}", e.getCode());
		return e.handled();;
	}

	bool Application::onMouseButtonReleased(MouseButtonReleasedEvent& e)
	{
		e.handle(true);
		//Log::info("Mouse button released event: key: {0}", e.getCode());
		return e.handled();;
	}

	bool Application::onMouseMove(MouseMovedEvent& e)
	{
		e.handle(true);
		//Log::info("Mouse Move event: ({0}, {1})", e.getX(), e.getY());
		return e.handled();;
	}



	Application::~Application()
	{

		// Stop systems

		// Stop log
		m_logSystem->stop();
		// Stop windows system
		m_windowsSystem->stop();
	}


	void Application::run()
	{


		//glm::mat4 view2D = glm::mat4(1.f);
		//glm::mat4 projection2D = glm::ortho(0.f, static_cast<float>(m_window->getWidth()), static_cast<float>(m_window->getHeight()), 0.f);
//
//		SceneWideUniforms swuOrtho;
//		swu3D["u_projection"] = std::pair<ShaderDataType, void*>(ShaderDataType::Mat4, static_cast<void*>(glm::value_ptr(m_camera->getCamera().projection)));
//		swu3D["u_view"] = std::pair<ShaderDataType, void*>(ShaderDataType::Mat4, static_cast<void*>(glm::value_ptr(m_camera->getCamera().view)));
//
//		SceneWideUniforms swu2D;
//		swu2D["u_view"] = std::pair<ShaderDataType, void*>(ShaderDataType::Mat4, static_cast<void*>(glm::value_ptr(view2D)));
//		swu2D["u_projection"] = std::pair<ShaderDataType, void*>(ShaderDataType::Mat4, static_cast<void*>(glm::value_ptr(projection2D)));
//
//		Quad quads[6] =
//		{
//			Quad::createCentreHalf({300.f, 200.f}, {100.f, 50.f}),
//			Quad::createCentreHalf({200.f, 200.f}, {50.f, 50.f}),
//			Quad::createCentreHalf({400.f, 500.f}, {75.f, 75.f}),
//			Quad::createCentreHalf({100.f, 200.f}, {75.f, 50.f}),
//			Quad::createCentreHalf({100.f, 500.f}, {50.f, 25.f}),
//			Quad::createCentreHalf({300.f, 50.f}, {75.f, 100.f}),
//		};

		//glEnable(GL_DEPTH_TEST);
		//glClearColor(0.26f, 0.98f, 0.80f, 1.0f);

		float timestep = 0.1f;



		while (m_running)
		{
			timestep = m_timer->getTimeElapsed();
			m_timer->reset();

			m_layerStack.update(timestep);
			m_layerStack.render();
			//Log::trace("FPS {0}", 1.0f / timestep);

			//if (InputPoller::isKeyPressed(NG_KEY_1)) { m_camera = followCam; }
			//if (InputPoller::isKeyPressed(NG_KEY_2)) { m_camera = eulerCam; }
			//if (InputPoller::isKeyPressed(NG_KEY_3)) { m_camera = orthoCam; }

			//models[0] = glm::translate(glm::mat4(1.0f), pos) * glm::rotate(glm::mat4(1.0f), rot, glm::vec3(0.f, 1.0f, 0.f));

			//if (InputPoller::isKeyPressed(NG_KEY_J)) { pos.x -= timestep * 3, 0.f, 0.f; }
			//if (InputPoller::isKeyPressed(NG_KEY_L)) { pos.x += timestep * 3, 0.f, 0.f; }
			//if (InputPoller::isKeyPressed(NG_KEY_I)) { pos.z += timestep * 3, 0.f, 0.f; }
			//if (InputPoller::isKeyPressed(NG_KEY_K)) { pos.z -= timestep * 3, 0.f, 0.f; }
			//if (InputPoller::isKeyPressed(NG_KEY_M)) { pos.y -= timestep * 3, 0.f, 0.f; }
			//if (InputPoller::isKeyPressed(NG_KEY_N)) { pos.y += timestep * 3, 0.f, 0.f; }
			//
			//if (InputPoller::isKeyPressed(NG_KEY_U)) { rot += timestep; }
			//if (InputPoller::isKeyPressed(NG_KEY_O)) { rot -= timestep; }

			////for (auto& model : models) { model = glm::rotate(model, timestep, glm::vec3(0.f, 1.0, 0.f)); }
			//models[1] = glm::rotate(models[1], timestep, glm::vec3(0.f, 1.0f, 0.f));
			//models[2] = glm::rotate(models[2], timestep, glm::vec3(0.f, 1.0f, 0.f));

			//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			//glEnable(GL_DEPTH_TEST);

			//
			//Renderer3D::begin(swu3D);

			//Renderer3D::submit(pyramidVAO, pyramidMat, models[0]);
			//Renderer3D::submit(cubeVAO, cubeMat, models[1]);
			//Renderer3D::submit(cubeVAO, cube2Mat, models[2]);

			//Renderer3D::end();

			//glDisable(GL_DEPTH_TEST);

			//glEnable(GL_BLEND);
			//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			//Renderer2D::begin(swu2D);

			//Renderer2D::submit(quads[0], {0.f, 0.5f, 1.f, 1.f});
			//Renderer2D::submit(quads[1], letterSubTexture);
			//Renderer2D::submit(quads[2], numberSubTexture ,{0.8f, 0.5f, .2f, 1.f});
			//Renderer2D::submit(quads[3], numberSubTexture ,{1.f, 0.5f, 1.f, 1.f}, 45.f, true);
			//Renderer2D::submit(quads[3], numberSubTexture ,{1.f, 0.5f, 1.f, 1.f}, glm::radians(-45.f));
			//Renderer2D::submit(quads[4], numberSubTexture, 45.f, true);
			//Renderer2D::submit(quads[5], { 1.f, 0.5f, 0.f, 0.5f }, glm::radians(-45.f));
			//Renderer2D::submit(quads[5], { 0.f, 0.5f, 1.f, 0.5f }, 45.f, true);

			//Renderer2D::end();

			//glDisable(GL_BLEND);

			//glBindBuffer(GL_UNIFORM_BUFFER, cameraUBO->getRenderID());
			//cameraUBO->uploadData("u_projection", glm::value_ptr(m_camera->getCamera().projection));
			//cameraUBO->uploadData("u_view", glm::value_ptr(m_camera->getCamera().view));

			//m_camera->onUpdate(timestep);
			m_window->onUpdate(timestep);
		
		}

	}

}
