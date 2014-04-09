#include <memory>

#include "Common.h"
#include "Renderer/Renderer/Renderer.h"

#include "Renderer/Renderer/Shader.h"

#include "Renderer/Renderer/RendererCommon.h"
#include "Renderer/Renderer/RendererUtils.h"
#include "Renderer/Renderer/VertexBuffer.h"
#include "Renderer/Renderer/IndexBuffer.h"
#include "Renderer/Renderer/Texture.h"
#include "Renderer/Renderer/Color.h"
#include "Renderer/Renderer/MeshManager.h"
#include "Renderer/Renderer/Mesh.h"


#include "Math/Matrix.h"
#include "Renderer/Renderer/Shader.h"

#include "FileIO/File.h"
#include "Log/Log.h"
//#include "ResourceManager/Image.h"

#include "Profiler\Profiler.h"

namespace oakvr
{
	namespace render
	{
		class Renderer::RendererImpl
		{
		public:
			void *m_pDevice;                    // OpenGL device interface (context)
			GLuint m_shaderProgramId;
		};

		// --------------------------------------------------------------------------------
		Renderer::Renderer()
			: m_pImpl{ std::make_unique<RendererImpl>() }
		{
			InitCommon();
		}

		Renderer::~Renderer()
		{
			// Terminate GLFW
			glfwTerminate();
		}
				
		bool Renderer::Initialize()
		{
			PROFILER_FUNC_SCOPED_TIMER;
			//glewExperimental = GL_TRUE;
			GLenum err = glewInit();
			if (err != GLEW_OK)
			{
				Log::PrintError("Failed to initialize GLEW. (%s)", glewGetErrorString(err));
				return false;
			}
			else
			{
				Log::PrintInfo("GLEW initialized!");
				glGetError();
			}
			
			int version[] = { 0, 0};
			
			glGetIntegerv(GL_MAJOR_VERSION, &version[0]);
			glGetIntegerv(GL_MINOR_VERSION, &version[1]);
			Log::PrintInfo("OpenGL version %d.%d", version[0], version[1]);
			
			glViewport(0, 0, m_pRenderWindow->GetWidth(), m_pRenderWindow->GetHeight());

			m_pImpl->m_shaderProgramId = glCreateProgram();

			glCullFace(GL_BACK);
			glEnable(GL_CULL_FACE);
			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_LESS);
			glEnable(GL_BLEND);

			// Wireframe mode
			//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

			m_bInitialized = true;
			return true;
		}


		// --------------------------------------------------------------------------------
		void Renderer::ClearBackground(const Color &color)
		{
			PROFILER_FUNC_SCOPED_TIMER;
			glClearColor(color.r, color.g, color.b, color.a);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		// --------------------------------------------------------------------------------
		void Renderer::BeginDraw()
		{
			glClearColor(0.4f, 0.6f, 0.9f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		}

		// --------------------------------------------------------------------------------
		void Renderer::EndDraw()
		{
			PROFILER_FUNC_SCOPED_TIMER;
			m_pRenderWindow->SwapBuffers();
		}

		// --------------------------------------------------------------------------------
		void Renderer::Cleanup()
		{

		}

		/*
		// --------------------------------------------------------------------------------
		void Renderer::ReleaseShader(Shader *pShader)
		{
			if (pShader == nullptr)
				return;
			//			glDeleteShader((GLuint)pShader->GetCompiledShader());
		}
		*/
		// --------------------------------------------------------------------------------
		void Renderer::CreateTexture(Texture *pTexture)
		{
			
		}

		// --------------------------------------------------------------------------------
		void Renderer::ReleaseTexture(Texture *pTexture)
		{
			
			
		}

		// --------------------------------------------------------------------------------
		void Renderer::UseTexture(Texture *texture)
		{
			PROFILER_FUNC_SCOPED_TIMER;
			if (texture != nullptr)
			{
				glEnable(GL_TEXTURE_2D);
				//glBindTexture(GL_TEXTURE_2D, reinterpret_cast<GLuint>(texture->GetData()));
			}
			else
			{
				glDisable(GL_TEXTURE_2D);
			}

		}

		// --------------------------------------------------------------------------------
		void Renderer::DrawPrimitives(uint32_t numVertices, uint32_t startVertex /* = 0 */)
		{
			PROFILER_FUNC_SCOPED_TIMER;
			glDrawArrays(GL_TRIANGLES, startVertex, numVertices);
#ifdef OAKVR_RENDER_DEBUG
			GLenum err = glGetError();
			if (err)
				oakvr::Log::PrintError("glDrawArrays 0x%x", err);
#endif
			
		}

		void Renderer::UseShader(std::shared_ptr<oakvr::render::Shader> &pShader)
		{
			PROFILER_FUNC_SCOPED_TIMER;
			GLuint shaderId = reinterpret_cast<GLuint>(pShader->GetNativeHandle());
			glAttachShader(m_pImpl->m_shaderProgramId, shaderId);
#ifdef OAKVR_RENDER_DEBUG
			GLenum err = glGetError();
			if (err)
				oakvr::Log::PrintError("glAttachShader error 0x%x", err);
#endif
		}

		void Renderer::PrepareShaders()
		{
			PROFILER_FUNC_SCOPED_TIMER;
			glLinkProgram(m_pImpl->m_shaderProgramId);
#ifdef OAKVR_RENDER_DEBUG
			GLenum err = glGetError();
			if (err)
				oakvr::Log::PrintError("glLinkProgram error 0x%x", err);
#endif

			//validateProgram(shader_id); // Validate the shader program
			glUseProgram(m_pImpl->m_shaderProgramId);
#ifdef OAKVR_RENDER_DEBUG
			err = glGetError();
			if (err)
				oakvr::Log::PrintError("glUseProgram error 0x%x", err);
#endif
		}

		void Renderer::BindAdditionalShaderParams()
		{
			PROFILER_FUNC_SCOPED_TIMER;
			oakvr::math::Matrix mProj = oakvr::math::Matrix::PerspectiveProjection(3.14158592f / 3.f, 4.f / 3.f, .1f, 100.0f);
			oakvr::math::Matrix mView = oakvr::math::Matrix::Identity();
			mView._42 = -1.3f;
			mView._43 = -4.f;
			static float angle = 0;
			if (angle >= 2 * 3.14f)
				angle = 0;
			oakvr::math::Matrix mModel = oakvr::math::Matrix::RotationY(angle);
			angle += 0.05f;
			int projectionMatrixLocation = glGetUniformLocation(m_pImpl->m_shaderProgramId, "projectionMatrix");
			int viewMatrixLocation = glGetUniformLocation(m_pImpl->m_shaderProgramId, "viewMatrix");
			int modelMatrixLocation = glGetUniformLocation(m_pImpl->m_shaderProgramId, "modelMatrix");
			glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &mProj.m[0][0]);
			glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &mView.m[0][0]);
			glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &mModel.m[0][0]);

			GLint textureLocation = glGetUniformLocation(m_pImpl->m_shaderProgramId, "texDiffuse0");
			glActiveTexture(GL_TEXTURE0);
			glUniform1i(textureLocation, 0);
#ifdef OAKVR_RENDER_DEBUG
			GLenum err = glGetError();
			if (err)
				oakvr::Log::PrintError("glUseProgram error 0x%x", err);
#endif
		}

		// --------------------------------------------------------------------------------
		void Renderer::DrawIndexed(uint32_t numIndices, uint8_t stride /* = 4 */, uint32_t startIndex /* = 0 */, uint32_t startVertex /* = 0 */)
		{
			PROFILER_FUNC_SCOPED_TIMER;
			//oakvr::profiler::ScopedTimer oakvrScopedTimername("drawIndexed", "", __FUNCTION__, __FILE__ + std::to_string(__LINE__));
			if (stride == 4)
				glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, nullptr);
			else
				glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_SHORT, nullptr);
#ifdef OAKVR_RENDER_DEBUG
			GLenum err = glGetError();
			if (err)
			{
				oakvr::Log::PrintError("glDrawArrays 0x%x", err);
			}
#endif
			
		}
		
		/*

		// --------------------------------------------------------------------------------
		void Renderer::EnableDepthBuffer()
		{
		glEnable(GL_DEPTH_TEST);
		}

		// --------------------------------------------------------------------------------
		void Renderer::DisableDepthBuffer()
		{
		glDisable(GL_DEPTH_TEST);
		}

		// --------------------------------------------------------------------------------
		void Renderer::EnableOrtographicProjection()
		{
		m_bPerspectiveProjection = false;
		}

		// --------------------------------------------------------------------------------
		void Renderer::EnablePerspectiveProjection()
		{
		m_bPerspectiveProjection = true;
		}

		// --------------------------------------------------------------------------------
		void Renderer::EnableFillWireframe()
		{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}

		// --------------------------------------------------------------------------------
		void Renderer::EnableFillSolid()
		{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
		*/
	} // namespace render
} // namespace oakvr

