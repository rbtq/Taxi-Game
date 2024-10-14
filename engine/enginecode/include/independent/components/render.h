#pragma once
#include "platform/OpenGL/vertexArray.h"
#include "rendering/material.h"

namespace Engine {
	class RenderComponent {
	public:
		std::shared_ptr<VertexArray> geometry;
		std::shared_ptr<Material> material;

		RenderComponent(std::shared_ptr<VertexArray> geo, std::shared_ptr<Material> mat) :
			geometry(geo), material(mat)
		{};
	};
}