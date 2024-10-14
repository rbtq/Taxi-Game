/** \file layerStack.cpp */
#include "engine_pch.h"
#include "core/layerStack.h"

Engine::LayerStack::~LayerStack()
{
	for (uint32_t i = m_stack.size(); i > 0; --i) pop();
}

void Engine::LayerStack::push(std::shared_ptr<Layer> layer)
{
	layer->onAttach();
	std::shared_ptr<Layer> tmp(layer);
	m_stack.push_back(tmp);
}

void Engine::LayerStack::pop()
{
	m_stack.back()->onDetach();
	m_stack.pop_back();
}

void Engine::LayerStack::update(float timestep)
{
	for (auto& layer : m_stack) /*if (layer->isActive())*/layer->onUpdate(timestep);
}

void Engine::LayerStack::render()
{
	for (auto& layer : m_stack) /*if (layer->isDisplay())*/layer->onRender();
}

void Engine::LayerStack::onKeyPressed(KeyPressedEvent& e)
{
	for (auto& layer : m_stack) if (layer->isFocused() && !e.handled())layer->onKeyPressed(e);
}

void Engine::LayerStack::onKeyReleased(KeyReleasedEvent& e)
{
	for (auto& layer : m_stack) if (layer->isFocused() && !e.handled())layer->onKeyReleased(e);
}

void Engine::LayerStack::onMousePressed(MouseButtonPressedEvent& e)
{
	for (auto& layer : m_stack) if (layer->isFocused() && !e.handled())layer->onMousePressed(e);
}

void Engine::LayerStack::onMouseReleased(MouseButtonReleasedEvent& e)
{
	for(auto & layer : m_stack) if (layer->isFocused() && !e.handled())layer->onMouseReleased(e);
}

void Engine::LayerStack::onMouseWheel(MouseScrolledEvent& e)
{
	for (auto& layer : m_stack) if (layer->isFocused() && !e.handled())layer->onMouseWheel(e);
}

void Engine::LayerStack::onMouseMoved(MouseMovedEvent& e)
{
	for (auto& layer : m_stack) if (layer->isFocused() && !e.handled())layer->onMouseMoved(e);
}

void Engine::LayerStack::setActive(const char* layerName, bool activeState)
{
	for (auto& layer : m_stack) if (layer->getName() == layerName) layer->setActive(activeState);
}

void Engine::LayerStack::setAllActive(bool activeState)
{
	for (auto& layer : m_stack) layer->setActive(activeState);
}

void Engine::LayerStack::setDisplay(const char* layerName, bool displayState)
{
	for (auto& layer : m_stack) if (layer->getName() == layerName) layer->setDisplay(displayState);
}

void Engine::LayerStack::setAllDisplay(bool displayStatus)
{
	for (auto& layer : m_stack) layer->setDisplay(displayStatus);
}

void Engine::LayerStack::setFocused(const char* layerName, bool focusedState)
{
	for (auto& layer : m_stack) if (layer->getName() == layerName) layer->setFocused(focusedState);
}

void Engine::LayerStack::setAllFocused(bool focusedStatus)
{
	for (auto& layer : m_stack) layer->setFocused(focusedStatus);
}
