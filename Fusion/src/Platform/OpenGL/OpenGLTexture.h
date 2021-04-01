#pragma once

#include "Fusion/Graphics/Texture.h"

namespace Fusion { namespace Graphics {

	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(const std::string& path);
		virtual ~OpenGLTexture2D();

		virtual uint32_t GetWidth() const override { return m_Width; }
		virtual uint32_t GetHeight() const override { return m_Height; }
		virtual uint32_t GetTextureHandle() const override { return m_TextureID; }

		virtual void Bind(uint32_t slot = 0) const override;

		virtual bool operator==(const Texture& other) const override
		{
			return m_TextureID == other.GetTextureHandle();
		}
	private:
		uint32_t m_Width;
		uint32_t m_Height;
		uint32_t m_TextureID;
	};

} }
