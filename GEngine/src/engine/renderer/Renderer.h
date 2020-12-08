#pragma once

#include "engine\core\Layer.h"

namespace GEngine
{
	class ENGINE_API Renderer : public Layer
	{
	public:
		Renderer();
		~Renderer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate() override;
		virtual void OnEvent(Event& e) override;

		void Draw(unsigned int size);
		void Bind(const unsigned int vertices_size, const void* vertices_data,
			const unsigned int indices_size, const void* indices_data);
		void Clear();
	private:
		unsigned int m_VertexArray, m_IndexBuffer, m_VertexBuffer;

	};
}
