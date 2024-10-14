/** \file layer.h */
#pragma once
#include <string>
#include "core/window.h"

namespace Engine {
	class Layer
	{
	public:
		Layer(const char* name) : m_name(name) {}; //!< Constructor

		virtual void onAttach() {} //!< Runs when layer is attached
		virtual void onDetach() {} //!< Runs when layer is Detached
		virtual void onRender() {} //!< Runs when layer is Rendered
		virtual void onUpdate(float timestep) {} //!< Runs every frame
		virtual void onResize(WindowResizeEvent& e) {} //!< Runs when layers window is risized

		inline const char* getName() const { return m_name; } //!< Returns name
		inline void setDisplay(bool displayStatus) { m_isDisplayed = displayStatus; } //!< sets display status
		inline void setActive(bool activeStatus) { m_isActive = activeStatus; } //!< sets active status
		inline void setFocused(bool focusedStatus) { m_isFocused = focusedStatus; } //!< sets focus status
		inline const bool isDisplay() const { return m_isDisplayed; } //!< gets display status
		inline const bool isActive() const { return m_isActive; } //!< gets active status
		inline const bool isFocused() const { return m_isFocused; } //!< gets focus status

		virtual void onKeyPressed(KeyPressedEvent& e) { e.handle(false); } //!< On key press event
		virtual void onKeyReleased(KeyReleasedEvent& e) { e.handle(false); } //!< On key Released event
		virtual void onMousePressed(MouseButtonPressedEvent& e) { e.handle(false); } //!< On mouse press event
		virtual void onMouseReleased(MouseButtonReleasedEvent& e) { e.handle(false); } //!< On mouse released event
		virtual void onMouseWheel(MouseScrolledEvent& e) { e.handle(false); } //!< On mouse scrolled event
		virtual void onMouseMoved(MouseMovedEvent& e) { e.handle(false); } //!< On mouse moved event
	protected:
		const char* m_name; //!< Name of layer
		bool m_isDisplayed = true; //!< Should this layer be rendered
		bool m_isActive = true; //!< Should this layer be updated
		bool m_isFocused = true; //!< Should this layer be getting events

	};
}
