#include "Common.h"
#include "Renderer/Renderer/Renderer.h"

#include "Renderer/Renderer/Shader.h"

#include "Renderer/Renderer/RendererCommon.h"
#include "Renderer/Renderer/VertexBuffer.h"
#include "Renderer/Renderer/IndexBuffer.h"
#include "Renderer/Renderer/Texture.h"
#include "Renderer/Renderer/Color.h"
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

namespace oakvr
{
	namespace render
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
				
		bool Renderer::Initialize()
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
		void Renderer::ClearBackground(const Color &color)
		{
			PROFILER_FUNC_SCOPED_TIMER;
			glCallAndCheck(glClearColor, color.r, color.g, color.b, color.a);
			glCallAndCheck(glClear, GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		// --------------------------------------------------------------------------------
		void Renderer::BeginDraw()
		{
			PROFILER_FUNC_SCOPED_TIMER;
			glCallAndCheck(glClearColor, 0.4f, 0.6f, 0.9f, 1.0f);
			glCallAndCheck(glClear, GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		}

		// --------------------------------------------------------------------------------
		void Renderer::EndDraw()
		{
			PROFILER_FUNC_SCOPED_TIMER;
			m_pRenderWindow->SwapBuffers();
		}

		// --------------------------------------------------------------------------------
		void Renderer::UseTexture(Texture *texture)
		{
			PROFILER_FUNC_SCOPED_TIMER;
			if (texture != nullptr)
			{
				glCallAndCheck(glEnable, GL_TEXTURE_2D);
				//glBindTexture(GL_TEXTURE_2D, reinterpret_cast<GLuint>(texture->GetData()));
			}
			else
			{
				glCallAndCheck(glDisable, GL_TEXTURE_2D);
			}

		}

		// --------------------------------------------------------------------------------
		void Renderer::DrawPrimitives(uint32_t numVertices, uint32_t startVertex /* = 0 */)
		{
			PROFILER_FUNC_SCOPED_TIMER;
			glCallAndCheck(glDrawArrays, GL_TRIANGLES, startVertex, numVertices);
		}

		void Renderer::UseShaderProgram(sp<oakvr::render::ShaderProgram> pShaderProgram)
		{
			PROFILER_FUNC_SCOPED_TIMER;
			if (pShaderProgram)
				glCallAndCheck(glUseProgram, reinterpret_cast<GLuint>(pShaderProgram.get()->GetNativeHandle()));
		}

		void Renderer::UpdateShaderParams(sp<oakvr::render::ShaderProgram> pShaderProgram)
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
		void Renderer::DrawIndexed(uint32_t numIndices, uint8_t stride /* = 4 */, uint32_t startIndex /* = 0 */, uint32_t startVertex /* = 0 */)
		{
			PROFILER_FUNC_SCOPED_TIMER;
			//oakvr::profiler::ScopedTimer oakvrScopedTimername("drawIndexed", "", __FUNCTION__, __FILE__ + std::to_string(__LINE__));
			if (stride == 4)
				glCallAndCheck(glDrawElements, GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, nullptr);
			else
				glCallAndCheck(glDrawElements, GL_TRIANGLES, numIndices, GL_UNSIGNED_SHORT, nullptr);
		}

		void Renderer::OnResize(unsigned int newWidth, unsigned int newHeight)
		{
			glCallAndCheck(glViewport, 0, 0, m_pRenderWindow->GetWidth(), m_pRenderWindow->GetHeight());
		}
		
		bool Renderer::IsValid()
		{
			return m_pRenderWindow && m_pRenderWindow->IsValid();
		}

		// Wireframe
		void Renderer::EnableWireframe()
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			m_bWireframeEnabled = true;
		}

		void Renderer::DisableWireframe()
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			m_bWireframeEnabled = false;
		}

		void Renderer::ToggleWireframe()
		{
			if (m_bWireframeEnabled == false)
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			else
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			m_bWireframeEnabled = !m_bWireframeEnabled;
		}

		// Wireframe
		void Renderer::EnableCulling()
		{
			glCallAndCheck(glEnable, GL_CULL_FACE);
			m_bCullingEnabled = true;
		}

		void Renderer::DisableCulling()
		{
			glCallAndCheck(glDisable, GL_CULL_FACE);
			m_bCullingEnabled = false;
		}

		void Renderer::ToggleCulling()
		{
			if (m_bCullingEnabled == false)
				glCallAndCheck(glEnable, GL_CULL_FACE);
			else
				glCallAndCheck(glDisable, GL_CULL_FACE);
			m_bCullingEnabled = !m_bCullingEnabled;
		}

		// DepthTest 
		void Renderer::EnableDepthTest()
		{
			glCallAndCheck(glEnable, GL_DEPTH_TEST);
			m_bDepthTestEnabled = true;
		}
		
		void Renderer::DisableDepthTest()
		{
			glCallAndCheck(glDisable, GL_DEPTH_TEST);
			m_bDepthTestEnabled = false;
		}

		void Renderer::ToggleDepthTest()
		{
			if (m_bDepthTestEnabled == false)
				glCallAndCheck(glEnable, GL_DEPTH_TEST);
			else
				glCallAndCheck(glDisable, GL_DEPTH_TEST);
			m_bDepthTestEnabled = !m_bDepthTestEnabled;
		}

		// Blending
		void Renderer::EnableBlending()
		{
			glCallAndCheck(glEnable, GL_BLEND);
			m_bBlendingEnabled = true;
		}

		void Renderer::DisableBlending()
		{
			glCallAndCheck(glDisable, GL_BLEND);
			m_bBlendingEnabled = false;
		}

		void Renderer::ToggleBlending()
		{
			if (m_bBlendingEnabled == false)
				glCallAndCheck(glEnable, GL_BLEND);
			else
				glCallAndCheck(glDisable, GL_BLEND);
			m_bBlendingEnabled = !m_bBlendingEnabled;
		}

	} // namespace render
} // namespace oakvr

