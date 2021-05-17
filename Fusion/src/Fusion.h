#pragma once

#include "Fusion/Core/Base.h"
#include "Fusion/Core/Application.h"
#include "Fusion/Core/Log.h"
#include "Fusion/Core/Layer.h"
#include "Fusion/Core/ColorConversion.h"
#include "Fusion/Core/Input.h"
#include "Fusion/Core/Timer.h"

#include "Fusion/Events/Event.h"
#include "Fusion/Events/KeyEvent.h"
#include "Fusion/Events/MouseEvent.h"
#include "Fusion/Events/ApplicationEvent.h"

#ifdef F_MAIN_APP
#include "Fusion/Core/EntryPoint.h"
#endif

#include "Fusion/Graphics/VertexBuffer.h"
#include "Fusion/Graphics/IndexBuffer.h"
#include "Fusion/Graphics/VertexArray.h"
#include "Fusion/Graphics/Shader.h"
#include "Fusion/Graphics/Texture.h"
#include "Fusion/Graphics/RenderCommand.h"
#include "Fusion/Graphics/OrthographicCameraController.h"
#include "Fusion/Graphics/Renderer2D.h"

#include "Fusion/Audio/OpenAL.hpp"
#include "Fusion/Audio/Sound.hpp"
#include "Fusion/Audio/Music.hpp"
