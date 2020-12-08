#include "Engine_pch.h"
#include "Renderer.h"
#include "engine\renderer\Primitives.h"

#include <glm.hpp>

namespace GEngine
{
	Renderer::Renderer() : Layer("RendererLayer")
	{
	}

	Renderer::~Renderer()
	{
	}

	void Renderer::OnAttach()
	{
		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		glGenBuffers(1, &m_VertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);

		glGenBuffers(1, &m_IndexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
	}

	void Renderer::OnDetach()
	{
		glBindVertexArray(0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void Renderer::OnUpdate()
	{
	}

	void Renderer::OnEvent(Event& e)
	{
	}

	void Renderer::Draw(unsigned int size)
	{
		glBindVertexArray(m_VertexArray);
		glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, nullptr);
	}

	void Renderer::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Renderer::Bind(const unsigned int vertices_size, const void* vertices_data, 
		const unsigned int indices_size, const void* indices_data)
	{
		glBufferData(GL_ARRAY_BUFFER, vertices_size * sizeof(Vertex), vertices_data, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_size * sizeof(GLuint), indices_data, GL_STATIC_DRAW);
	}
}