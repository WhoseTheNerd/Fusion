#pragma once

#include "Fusion/Core/Window.h"
#include "Fusion/Graphics/Context.h"

struct GLFWwindow;

namespace Fusion {


	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		virtual void OnUpdate() override;

		virtual uint32_t GetWidth() const override { return m_Data.Width; }
		virtual uint32_t GetHeight() const override { return m_Data.Height; }

		virtual void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; };
	private:
		GLFWwindow* m_Window;

		struct WindowData
		{
			std::string Title;
			uint32_t Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;

			// Event Callback

			WindowData(const WindowProps& props)
				: Title(props.Title), Width(props.Width), Height(props.Height), VSync(true)
			{ }
		};

		WindowData m_Data;

		Scope<Graphics::Context> m_Context;
	};
}
