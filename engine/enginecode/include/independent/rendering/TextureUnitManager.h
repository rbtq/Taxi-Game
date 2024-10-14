/** file\ TextureUnitManager.h */
#pragma once

#include <vector>

namespace Engine
{
	class TextureUnitManager
	{
	public:
		TextureUnitManager(uint32_t capacity) : m_capacity(capacity), m_buffer(capacity, 0xFFFFFFFF) {} //!< Constructor which takes a capacity
		inline bool full() { return m_full; }  //!< Is the buffer full
		void clear(); //!< Clear and rest the buffer
		bool getUnit(uint32_t textureID, uint32_t & textureUnit); //!< Returns whether or not the texture needs binding to the unit. Texture unit is always set to the unit
	private:
		uint32_t m_capacity; //!, Capacity of ring buffer
		std::vector<uint32_t> m_buffer; //!< Internal buffer
		bool m_full = false; //!< Is the buffer full
		uint32_t m_head = 0; //!< Head of the buffer
		uint32_t m_tail = 0; //!< Tail of the buffer
	};
}
