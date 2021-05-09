#pragma once

#include "Fusion/Core/Base.h"

#include "Fusion/Graphics/Camera.h"
#include "Fusion/Graphics/Texture.h"

#include <glm/glm.hpp>

namespace Fusion { namespace Graphics {

	class F_API Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const Camera& camera);
		static void EndScene();

		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);

		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, Ref<Texture2D> texture);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, Ref<Texture2D> texture);
	private:
		static void StartBatch();
		static void Flush();
		static void NextBatch();
	};

} }
