#include "fpch.h"
#include "RenderCommand.h"

namespace Fusion { namespace Graphics {

	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();

} }
