/** \file layerStack.h */
#pragma once

#include "layer.h"
#include <memory>

namespace Engine
{
	class LayerStack
	{
	public:
		LayerStack() { m_stack.reserve(10); };
		~LayerStack();

		void push(std::shared_ptr<Layer>  layer);
		void pop();

		void update(float timestep);
		void render();

		void onKeyPressed(KeyPressedEvent& e);
		void onKeyReleased(KeyReleasedEvent& e);
		void onMousePressed(MouseButtonPressedEvent& e);
		void onMouseReleased(MouseButtonReleasedEvent& e);
		void onMouseWheel(MouseScrolledEvent& e);
		void onMouseMoved(MouseMovedEvent& e);

		void setActive(const char * layerName, bool activeState);
		void setAllActive(bool activeState);
		void setDisplay(const char* layerName, bool displayState);
		void setAllDisplay(bool displayStatus);
		void setFocused(const char* layerName, bool focusedState);
		void setAllFocused(bool focusedStatus);

		std::vector<std::shared_ptr<Layer>>::iterator begin() { return m_stack.begin(); }
		std::vector<std::shared_ptr<Layer>>::iterator end() { return m_stack.end(); }
		std::vector<std::shared_ptr<Layer>>::reverse_iterator rbegin() { return m_stack.rbegin(); }
		std::vector<std::shared_ptr<Layer>>::reverse_iterator rend() { return m_stack.rend(); }

		std::vector<std::shared_ptr<Layer>>::const_iterator begin() const { return m_stack.begin(); }
		std::vector<std::shared_ptr<Layer>>::const_iterator end() const { return m_stack.end(); }
		std::vector<std::shared_ptr<Layer>>::const_reverse_iterator rbegin() const { return m_stack.rbegin(); }
		std::vector<std::shared_ptr<Layer>>::const_reverse_iterator rend() const { return m_stack.rend(); }
	private:
		std::vector<std::shared_ptr<Layer>> m_stack;
	};
}