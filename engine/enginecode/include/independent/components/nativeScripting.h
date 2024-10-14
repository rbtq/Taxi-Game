#pragma once

#include <entt/entt.hpp>
#include "core/application.h"

namespace Engine {
	class NativeScript {
	public:
		NativeScript() :m_entity(entt::null), m_registry(Application::getInstance().getRegistry()) {}
		NativeScript(entt::entity entity) :m_entity(entity), m_registry(Application::Application::getInstance().getRegistry()) {}
		virtual void onUpdate(float timestep) {};
		virtual void onKeyPress(KeyPressedEvent& e) {};

	protected:
		entt::registry& m_registry;
		entt::entity m_entity;
	};

	class NativeScriptComponent {
	public:
		NativeScriptComponent() = default;
		~NativeScriptComponent() = default;
		void onUpdate(float timestep) { m_instance->onUpdate(timestep); }
		void onKeyPress(KeyPressedEvent& e) { m_instance->onKeyPress(e); }

		template <typename G, typename ...Args>
		void create(Args&&... args) {
			G* ptr = new G(std::forward<Args>(args)...);
			m_instance.reset(static_cast<NativeScript*>(ptr));
		}
	protected:
		std::shared_ptr<NativeScript> m_instance;
	};
}