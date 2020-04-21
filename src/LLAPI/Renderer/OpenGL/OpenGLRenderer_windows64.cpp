#include "Common.h"
#include "Renderer/Renderer/Renderer.h"

#include "Renderer/Renderer/Shader.h"

#include "Renderer/Renderer/RendererCommon.h"
#include "Renderer/Renderer/VertexBuffer.h"
#include "Renderer/Renderer/IndexBuffer.h"
#include "Renderer/Renderer/Texture.h"
#include "Renderer/Renderer/Color.h"
#include "Renderer/Renderer/RenderableManager.h"
#include "Renderer/Renderer/MeshManager.h"
#include "Renderer/Renderer/Mesh.h"

#include "Math/Matrix.h"
#include "Renderer/Renderer/Shader.h"
#include "Renderer/Renderer/ShaderProgram.h"

#include "Utils/RenderUtils.h"

#include "FileIO/File.h"
#include "Log/Log.h"

#include "Profiler/Profiler.h"

#include <memory>

namespace oakvr::render
{
	class Renderer::RendererImpl
	{
	public:
	};

	// --------------------------------------------------------------------------------
	Renderer::Renderer()
		: m_pImpl{ std::make_unique<RendererImpl>() }
	{
		InitCommon();
	}

	Renderer::~Renderer()
	{
	}

	auto Renderer::Initialize() -> bool
	{
		//PROFILER_FUNC_SCOPED_TIMER;
		glewExperimental = GL_TRUE;
		GLenum err = glewInit();
		if (err != GLEW_OK)
		{
			Log::Error("Failed to initialize GLEW. (%s)", glewGetErrorString(err));
			return false;
		}
		else
		{
			Log::Info("GLEW initialized!");
		}

		int version[] = { 0, 0 };
		glGetIntegerv(GL_MAJOR_VERSION, &version[0]);
		glGetIntegerv(GL_MINOR_VERSION, &version[1]);
		Log::Info("OpenGL version %d.%d", version[0], version[1]);

		glCallAndCheck(glViewport, 0, 0, m_pRenderWindow->GetWidth(), m_pRenderWindow->GetHeight());
		glCallAndCheck(glCullFace, GL_BACK);
		glCallAndCheck(glFrontFace, GL_CCW);
		glCallAndCheck(glEnable, GL_CULL_FACE);
		glCallAndCheck(glDepthFunc, GL_LESS);
		glCallAndCheck(glEnable, GL_DEPTH_TEST);
		glCallAndCheck(glBlendFunc, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glCallAndCheck(glEnable, GL_BLEND);

		return true;
	}


	// --------------------------------------------------------------------------------
	auto Renderer::ClearBackground(const Color& color) -> void
	{
		PROFILER_FUNC_SCOPED_TIMER;
		glCallAndCheck(glClearColor, color.r, color.g, color.b, color.a);
		glCallAndCheck(glClear, GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	// --------------------------------------------------------------------------------
	auto Renderer::BeginDraw() -> void
	{
		PROFILER_FUNC_SCOPED_TIMER;
		glCallAndCheck(glClearColor, 0.4f, 0.6f, 0.9f, 1.0f);
		glCallAndCheck(glClear, GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}

	// --------------------------------------------------------------------------------
	auto Renderer::EndDraw() -> void
	{
		PROFILER_FUNC_SCOPED_TIMER;
		m_pRenderWindow->SwapBuffers();
	}

	// --------------------------------------------------------------------------------
	auto Renderer::UseTexture(Texture* texture) -> void
	{
		PROFILER_FUNC_SCOPED_TIMER;
		if (texture != nullptr)
		{
			glCallAndCheck(glEnable, GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, reinterpret_cast<GLuint>(texture->GetNativeHandle()));
		}
		else
		{
			glCallAndCheck(glDisable, GL_TEXTURE_2D);
		}

	}

	// --------------------------------------------------------------------------------
	auto Renderer::DrawPrimitives(uint32_t numVertices, uint32_t startVertex /* = 0 */) -> void
	{
		PROFILER_FUNC_SCOPED_TIMER;
		glCallAndCheck(glDrawArrays, GL_TRIANGLES, startVertex, numVertices);
	}

	auto Renderer::UseShaderProgram(sp<oakvr::render::ShaderProgram> pShaderProgram) -> void
	{
		PROFILER_FUNC_SCOPED_TIMER;
		if (pShaderProgram)
			glCallAndCheck(glUseProgram, reinterpret_cast<GLuint>(pShaderProgram.get()->GetNativeHandle()));
	}

	auto Renderer::UpdateShaderParams(sp<oakvr::render::ShaderProgram> pShaderProgram) -> void
	{
		//TODO: Add set shader param function
		PROFILER_FUNC_SCOPED_TIMER;
		const oakvr::math::Matrix mProj = m_projMatrix.GetTransposed();
		const oakvr::math::Matrix mView = m_viewMatrix.GetTransposed();
		const oakvr::math::Matrix mWorld = m_worldMatrix.GetTransposed();

		//const oakvr::math::Matrix mProj = m_projMatrix;
		//const oakvr::math::Matrix mView = m_viewMatrix;
		//const oakvr::math::Matrix mWorld = m_worldMatrix;

		GLuint programId = reinterpret_cast<GLuint>(pShaderProgram->GetNativeHandle());
		int projectionMatrixLocation = glCallAndCheck(glGetUniformLocation, programId, "projectionMatrix");
		int viewMatrixLocation = glCallAndCheck(glGetUniformLocation, programId, "viewMatrix");
		int worldMatrixLocation = glCallAndCheck(glGetUniformLocation, programId, "worldMatrix");
		glCallAndCheck(glUniformMatrix4fv, projectionMatrixLocation, 1, GL_FALSE, &mProj.m[0][0]);
		glCallAndCheck(glUniformMatrix4fv, viewMatrixLocation, 1, GL_FALSE, &mView.m[0][0]);
		glCallAndCheck(glUniformMatrix4fv, worldMatrixLocation, 1, GL_FALSE, &mWorld.m[0][0]);

		GLint textureLocation = glCallAndCheck(glGetUniformLocation, programId, "texDiffuse0");
		//glActiveTexture(GL_TEXTURE0);
		glCallAndCheck(glUniform1i, textureLocation, 0);
	}

	// --------------------------------------------------------------------------------
	auto Renderer::DrawIndexed(uint32_t numIndices, uint8_t stride /* = 4 */, uint32_t startIndex /* = 0 */, uint32_t startVertex /* = 0 */) -> void
	{
		PROFILER_FUNC_SCOPED_TIMER;
		//oakvr::profiler::ScopedTimer oakvrScopedTimername("drawIndexed", "", __FUNCTION__, __FILE__ + std::to_string(__LINE__));
		if (stride == 4)
			glCallAndCheck(glDrawElements, GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, nullptr);
		else
			glCallAndCheck(glDrawElements, GL_TRIANGLES, numIndices, GL_UNSIGNED_SHORT, nullptr);
	}

	auto Renderer::OnResize(unsigned int newWidth, unsigned int newHeight) -> void
	{
		glCallAndCheck(glViewport, 0, 0, m_pRenderWindow->GetWidth(), m_pRenderWindow->GetHeight());
	}

	auto Renderer::IsValid() -> bool
	{
		return m_pRenderWindow && m_pRenderWindow->IsValid();
	}

	// Wireframe
	auto Renderer::EnableWireframe() -> void
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		m_bWireframeEnabled = true;
	}

	auto Renderer::DisableWireframe() -> void
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		m_bWireframeEnabled = false;
	}

	auto Renderer::ToggleWireframe() -> void
	{
		if (m_bWireframeEnabled == false)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		m_bWireframeEnabled = !m_bWireframeEnabled;
	}

	// Wireframe
	auto Renderer::EnableCulling() -> void
	{
		glCallAndCheck(glEnable, GL_CULL_FACE);
		m_bCullingEnabled = true;
	}

	auto Renderer::DisableCulling() -> void
	{
		glCallAndCheck(glDisable, GL_CULL_FACE);
		m_bCullingEnabled = false;
	}

	auto Renderer::ToggleCulling() -> void
	{
		if (m_bCullingEnabled == false)
			glCallAndCheck(glEnable, GL_CULL_FACE);
		else
			glCallAndCheck(glDisable, GL_CULL_FACE);
		m_bCullingEnabled = !m_bCullingEnabled;
	}

	// DepthTest 
	auto Renderer::EnableDepthTest() -> void
	{
		glCallAndCheck(glEnable, GL_DEPTH_TEST);
		m_bDepthTestEnabled = true;
	}

	auto Renderer::DisableDepthTest() -> void
	{
		glCallAndCheck(glDisable, GL_DEPTH_TEST);
		m_bDepthTestEnabled = false;
	}

	auto Renderer::ToggleDepthTest() -> void
	{
		if (m_bDepthTestEnabled == false)
		{
			glCallAndCheck(glEnable, GL_DEPTH_TEST);
			m_bDepthTestEnabled = true;
		}
		else
		{
			glCallAndCheck(glDisable, GL_DEPTH_TEST);
			m_bDepthTestEnabled = false;
		}
	}

	// Blending
	auto Renderer::EnableBlending() -> void
	{
		glCallAndCheck(glEnable, GL_BLEND);
		m_bBlendingEnabled = true;
	}

	auto Renderer::DisableBlending() -> void
	{
		glCallAndCheck(glDisable, GL_BLEND);
		m_bBlendingEnabled = false;
	}

	auto Renderer::ToggleBlending() -> void
	{
		if (m_bBlendingEnabled == false)
			glCallAndCheck(glEnable, GL_BLEND);
		else
			glCallAndCheck(glDisable, GL_BLEND);
		m_bBlendingEnabled = !m_bBlendingEnabled;
	}

}
