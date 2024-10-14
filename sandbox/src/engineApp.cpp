/** \file engineApp.cpp
*/
#include "engineApp.h"
#include "sceneLayer.h"

engineApp::engineApp()
{
	std::shared_ptr<Engine::Layer> sl(new SceneLayer("Scene Layer", getEntities(), getRegistry()));
	m_layerStack.push(sl);
}

engineApp::~engineApp()
{

}

Engine::Application* Engine::startApplication()
{
	return new engineApp();
}