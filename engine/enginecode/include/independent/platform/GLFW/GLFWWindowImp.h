/** \file GLFWWindowImp.h */
#pragma once

#include "core/window.h"
#include <GLFW/glfw3.h>

namespace Engine
{
	/** \class GLFWWindowImp
	* Implementation of a window using GLFW
	*/

	class GLFWWindowImp : public WindowBase
	{
	public:
		GLFWWindowImp(const WindowProperties& properties); //!< Constructor
		void init(const WindowProperties& properties) override; //!< Initialise the window
		void close() override; //!< Close the window
		void onUpdate(float timestep) override; //!< On update function
		void setVsync(bool Vsync) override; //!< sets Vsync
		inline unsigned int getWidth() const override { return m_props.width; } //!< Gets screen width
		inline unsigned int  getHeight() const override { return m_props.height; } //!< Gets screen height
		inline void* getNativeWindow() const override { return m_native; } //!< Gets native window
		inline bool isFullScreenMode() const override { return  m_props.isFullScreen; } //<! Check if screen is in fullscreen mode
		inline bool isVsync() const override { return m_props.isVsync; } //!< Checks if Vysnced

	private:
		WindowProperties m_props; //!< Properties
		GLFWwindow* m_native; //!< Native GLFW window
		float m_aspectRatio; //!< Aspect ratio
	};
}