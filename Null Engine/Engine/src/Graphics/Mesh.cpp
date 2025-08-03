#include <Graphics/Mesh.h>

#include <glad/glad.h>

namespace NullEngine
{
	Mesh::Mesh(const glm::vec3* vertices, size_t vertexCount, const uint32_t* indices, size_t indexCount)
		: m_IndexCount(static_cast<uint32_t>(indexCount)), m_VAO(0)
	{
		m_VAO = BuildVAO(vertices, vertexCount, indices, indexCount);
		if (m_VAO == 0)
		{
			m_Logger.Error("Failed to create VAO for Mesh");
			throw std::runtime_error("Failed to create VAO for Mesh");
		}
		m_Logger.Info("Mesh created with VAO ID: {}", m_VAO);
	}
	Mesh::~Mesh()
	{
		glDeleteVertexArrays(1, &m_VAO);
	}
	void Mesh::Bind() const
	{
		glBindVertexArray(m_VAO);
	}
	void Mesh::Unbind() const
	{
		glBindVertexArray(0);
	}
	void Mesh::Draw() const
	{
		glBindVertexArray(m_VAO);
		glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, nullptr);
		glBindVertexArray(0);
	}



	uint32_t Mesh::BuildVAO(const glm::vec3* vertices, size_t vertexCount, const uint32_t* indices, size_t indexCount)
	{
		uint32_t VAO;
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
		uint32_t VBO, EBO;
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(glm::vec3), vertices, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(uint32_t), indices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		return VAO;
	}
}