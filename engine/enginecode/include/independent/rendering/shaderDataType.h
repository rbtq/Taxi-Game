/** \file shaderDataType.h */
#pragma once

#include<cstdint>

namespace Engine
{
	enum class ShaderDataType
	{
		none = 0, Float, Float2, Float3, Float4, Int, Mat4, Byte4, Short, Short2, Short3, Short4, FlatInt
	};

	namespace SDT
	{
		static uint32_t size(ShaderDataType type)
		{
			switch (type)
			{
			case ShaderDataType::FlatInt: return 4;
			case ShaderDataType::Byte4: return 1 *4;
			case ShaderDataType::Int: return 4;
			case ShaderDataType::Float: return 4;
			case ShaderDataType::Float2: return 4*2;
			case ShaderDataType::Float3: return 4*3;
			case ShaderDataType::Float4: return 4*4;
			case ShaderDataType::Mat4: return 4 * 4 * 4;
			default: return 0;
			}
		}

		static uint32_t componentCount(ShaderDataType type)
		{
			switch (type)
			{
			case ShaderDataType::FlatInt: return 1;
			case ShaderDataType::Byte4: return 4;
			case ShaderDataType::Int: return 1;
			case ShaderDataType::Float: return 1;
			case ShaderDataType::Float2: return 2;
			case ShaderDataType::Float3: return 3;
			case ShaderDataType::Float4: return 4;
			case ShaderDataType::Mat4: return 4 * 4;
			default: return 0;
			}
		}

		static uint32_t std140alignment(ShaderDataType type)
		{
			switch (type)
			{
			case ShaderDataType::FlatInt: return 4;
			case ShaderDataType::Byte4: return 1 *4;
			case ShaderDataType::Short: return 2;
			case ShaderDataType::Short2: return 2 * 2;
			case ShaderDataType::Short3: return 2 * 4;
			case ShaderDataType::Short4: return 2 * 4;
			case ShaderDataType::Float: return 4;
			case ShaderDataType::Float2: return 4 * 2;
			case ShaderDataType::Float3: return 4 * 4;
			case ShaderDataType::Float4: return 4 * 4;
			case ShaderDataType::Mat4: return 4 * 4 * 4;
			default: return 0;
			}
		}
	}
}

