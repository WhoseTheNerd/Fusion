#include "fpch.h"
#include "Renderer2D.h"

#include "Fusion/Graphics/VertexArray.h"
#include "Fusion/Graphics/IndexBuffer.h"
#include "Fusion/Graphics/Shader.h"
#include "Fusion/Graphics/RenderCommand.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Fusion { namespace Graphics {

	struct QuadVertex
	{
		glm::vec3 Position;
		glm::vec2 TexCoords;
		float TexIndex;
		glm::vec4 Color;
		float UseColor;
	};

	struct Renderer2DData
	{
		static const uint32_t MaxQuads = 20000;
		static const uint32_t MaxVertices = MaxQuads * 4;
		static const uint32_t MaxIndices = MaxQuads * 6;
		static const uint32_t MaxTextureSlots = 32;

		Ref<VertexArray> VAO;
		Ref<VertexBuffer> VBO;
		Ref<IndexBuffer> IBO;
		Ref<Shader> Shader;

		uint32_t QuadIndexCount = 0;
		QuadVertex* QuadVertexBufferBase = nullptr;
		QuadVertex* QuadVertexBufferPtr = nullptr;

		std::array<Ref<Texture2D>, MaxTextureSlots> TextureSlots;
		uint32_t TextureSlotIndex = 0;

		glm::vec4 QuadVertexPositions[4];
	};

	static Renderer2DData s_Data;

	void Renderer2D::Init()
	{
		s_Data.VAO = VertexArray::Create();
		s_Data.VAO->Bind();

		s_Data.VBO = VertexBuffer::Create(s_Data.MaxVertices * sizeof(QuadVertex));
		s_Data.VBO->SetLayout({
			{Fusion::Graphics::ShaderDataType::Float3, "in_Position"},
			{Fusion::Graphics::ShaderDataType::Float2, "in_TexCoords"},
			{Fusion::Graphics::ShaderDataType::Float, "in_TexIndex"},
			{Fusion::Graphics::ShaderDataType::Float4, "in_Color"},
			{Fusion::Graphics::ShaderDataType::Float, "in_UseColor"}
		});

		s_Data.QuadVertexBufferBase = new QuadVertex[s_Data.MaxVertices];

		uint32_t* quadIndices = new uint32_t[s_Data.MaxIndices];

		uint32_t offset = 0;
		for (uint32_t i = 0; i < s_Data.MaxIndices; i += 6)
		{
			quadIndices[  i  ] = offset + 0;
			quadIndices[i + 1] = offset + 1;
			quadIndices[i + 2] = offset + 2;

			quadIndices[i + 3] = offset + 2;
			quadIndices[i + 4] = offset + 3;
			quadIndices[i + 5] = offset + 0;

			offset += 4;
		}

		std::vector<uint32_t> indices(quadIndices, quadIndices + s_Data.MaxIndices);
		s_Data.IBO = IndexBuffer::Create(indices);
		s_Data.IBO->Bind();

		s_Data.VAO->AddVertexBuffer(s_Data.VBO);
		s_Data.VAO->AddIndexBuffer(s_Data.IBO);

		delete[] quadIndices;

		std::string vertexShaderSrc = R"(
#version 450
layout (location = 0) in vec3 in_Position;
layout (location = 1) in vec2 in_TexCoords;
layout (location = 2) in float in_TexIndex;
layout (location = 3) in vec4 in_Color;
layout (location = 4) in float in_UseColor;
out vec2 out_TexCoords;
out flat float out_TexIndex;
out vec4 out_Color;
out float out_UseColor;
uniform mat4 u_Model = mat4(1.0);
uniform mat4 u_View = mat4(1.0);
uniform mat4 u_Projection = mat4(1.0);
void main()
{
	out_TexCoords = in_TexCoords;
	out_TexIndex = in_TexIndex;
	out_Color = in_Color;
	out_UseColor = in_UseColor;
	gl_Position = u_Projection * u_View * u_Model * vec4(in_Position, 1.0);
}		
)";

		std::string fragmentShaderSrc = R"(
#version 450
layout(location = 0) out vec4 FragColor;
in vec2 out_TexCoords;
in flat float out_TexIndex;
in vec4 out_Color;
in float out_UseColor;
uniform sampler2D u_Textures[32];
void main()
{
	if (out_UseColor == 1.0) {
		FragColor = out_Color;
	}
	else {
		FragColor = texture(u_Textures[int(out_TexIndex)], out_TexCoords);
	}
}		
)";

		s_Data.Shader = Fusion::Graphics::Shader::Create(vertexShaderSrc, fragmentShaderSrc);
		s_Data.Shader->Bind();

		int32_t samplers[s_Data.MaxTextureSlots];
		for (uint32_t i = 0; i < s_Data.MaxTextureSlots; i++)
			samplers[i] = i;

		s_Data.Shader->SetIntArray("u_Textures", samplers, s_Data.MaxTextureSlots);

		s_Data.QuadVertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
		s_Data.QuadVertexPositions[1] = { 0.5f, -0.5f, 0.0f, 1.0f };
		s_Data.QuadVertexPositions[2] = { 0.5f,  0.5f, 0.0f, 1.0f };
		s_Data.QuadVertexPositions[3] = { -0.5f,  0.5f, 0.0f, 1.0f };
	}

	void Renderer2D::Shutdown()
	{
		delete[] s_Data.QuadVertexBufferBase;
	}

	void Renderer2D::BeginScene(const Camera& camera)
	{
		s_Data.Shader->SetMat4("u_Projection", camera.GetProjectionMatrix());
		s_Data.Shader->SetMat4("u_View", camera.GetViewMatrix());

		s_Data.QuadIndexCount = 0;
		s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;
	}

	void Renderer2D::EndScene()
	{
		Flush();
	}

	void Renderer2D::StartBatch()
	{
		s_Data.QuadIndexCount = 0;
		s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;

		s_Data.TextureSlotIndex = 0;
	}

	void Renderer2D::Flush()
	{
		if (s_Data.QuadIndexCount == 0) return; //Nothing to draw

		uint32_t dataSize = static_cast<uint32_t>((uint8_t*)s_Data.QuadVertexBufferPtr - (uint8_t*)s_Data.QuadVertexBufferBase);
		s_Data.VBO->SetData(s_Data.QuadVertexBufferBase, dataSize);

		uint32_t count = dataSize / sizeof(QuadVertex);

		for (uint32_t i = 0; i < s_Data.TextureSlotIndex; i++)
			s_Data.TextureSlots[i]->Bind(i);

		RenderCommand::DrawIndexed(s_Data.VAO, s_Data.QuadIndexCount);
	}

	void Renderer2D::NextBatch()
	{
		Flush();
		StartBatch();
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		constexpr uint32_t quadVertexCount = 4;
		constexpr glm::vec2 textureCoords[] = { {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f} };

		if (s_Data.QuadIndexCount >= s_Data.MaxIndices)
			NextBatch();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		for (uint32_t i = 0; i < quadVertexCount; i++)
		{
			s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[i];
			s_Data.QuadVertexBufferPtr->TexCoords = textureCoords[i];
			s_Data.QuadVertexBufferPtr->TexIndex = 0.0f;
			s_Data.QuadVertexBufferPtr->Color = color;
			s_Data.QuadVertexBufferPtr->UseColor = 1.0f;
			s_Data.QuadVertexBufferPtr++;
		}

		s_Data.QuadIndexCount += 6;
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, Ref<Texture2D> texture)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, texture);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, Ref<Texture2D> texture)
	{
		constexpr uint32_t quadVertexCount = 4;
		constexpr glm::vec2 textureCoords[] = { {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f} };

		if (s_Data.QuadIndexCount >= s_Data.MaxIndices)
			NextBatch();

		float textureIndex = -1.0f;
		for (uint32_t i = 0; i < s_Data.TextureSlotIndex; i++)
		{
			if (*s_Data.TextureSlots[i] == *texture)
			{
				textureIndex = static_cast<float>(i);
				break;
			}
		}

		if (textureIndex < 0.0f)
		{
			if (s_Data.TextureSlotIndex >= s_Data.MaxTextureSlots)
				NextBatch();

			textureIndex = static_cast<float>(s_Data.TextureSlotIndex);
			s_Data.TextureSlots[s_Data.TextureSlotIndex] = texture;
			s_Data.TextureSlotIndex++;
		}

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		for (uint32_t i = 0; i < quadVertexCount; i++)
		{
			s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[i];
			s_Data.QuadVertexBufferPtr->TexCoords = textureCoords[i];
			s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
			s_Data.QuadVertexBufferPtr->Color = {0.2f, 0.3f, 0.8f, 1.0f};
			s_Data.QuadVertexBufferPtr->UseColor = 0.0f;
			s_Data.QuadVertexBufferPtr++;
		}

		s_Data.QuadIndexCount += 6;
	}

	

} }
