#pragma once

#include "Fusion/Core/Base.h"
#include "Fusion/Events/Event.h"

namespace Fusion {

	struct F_API WindowProps
	{
		std::string Title;
		uint32_t Width;
		uint32_t Height;

		WindowProps(const std::string& title = "Fusion Engine", uint32_t width = 960, uint32_t height = 540)
			: Title(title), Width(width), Height(height)
		{ }
	};

	class F_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() = default;

		virtual void OnUpdate() = 0;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual void* GetWindowHandle() = 0;

		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;

		static Scope<Window> Create(const WindowProps& props = WindowProps());
	};
}
