#pragma once

#include <Core/Logger.hpp>

#include <glm/glm.hpp>

namespace NullEngine
{
	class Mesh
	{
	public:
		Mesh(const glm::vec3* vertices, size_t vertexCount, const uint32_t* indices, size_t indexCount);
		~Mesh();
		void Bind() const;
		void Unbind() const;
		void Draw() const;

		static uint32_t BuildVAO(const glm::vec3* vertices, size_t vertexCount, const uint32_t* indices, size_t indexCount);

	private:
		uint32_t m_VAO;
		uint32_t m_IndexCount;

		static inline Logger m_Logger{ "Mesh" };
	};
}