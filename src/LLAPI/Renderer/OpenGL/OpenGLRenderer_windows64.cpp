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
			: m_pImpl{ new RendererImpl() }
		{
			InitCommon();
		}

		Renderer::~Renderer()
		{
			// Terminate GLFW
			glfwTerminate();
		}

		// --------------------------------------------------------------------------------
		bool Renderer::Initialize()
		{
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
			
			//glCullFace(GL_BACK);
			glFrontFace(GL_CCW);
			//glEnable(GL_CULL_FACE);
			glViewport(0, 0, m_pRenderWindow->GetWidth(), m_pRenderWindow->GetHeight());

			err = glGetError();
			if (err)
				oakvr::Log::PrintError("Err create1 %x", err);

			m_pImpl->m_shaderProgramId = glCreateProgram();
			err = glGetError();
			if (err)
				oakvr::Log::PrintError("Err create2 %x", err);

			// Wireframe mode
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

			m_bInitialized = true;
			return true;
		}

		// --------------------------------------------------------------------------------
		void Renderer::ClearBackground(const Color &color)
		{
			glClearColor(color.r, color.g, color.b, color.a);
			glClear(GL_COLOR_BUFFER_BIT);
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
			GLuint texId;

			glGenTextures(1, &texId);

			//			oakvr::core::Image *pImage = oakvr::Engine::GetResourceManager()->GetResource<oakvr::core::Image>(pTexture->GetId().GetStrId().c_str());
			// Separate resources on unique threads
			//			assert("Could not load texture from file!" && texId > 0);

			pTexture->SetData((void *)texId);

			glBindTexture(GL_TEXTURE_2D, texId);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}

		// --------------------------------------------------------------------------------
		void Renderer::ReleaseTexture(Texture *pTexture)
		{
			GLuint tex = (GLuint)pTexture->GetData();
			glDeleteTextures(1, &tex);
		}

		// --------------------------------------------------------------------------------
		void Renderer::UseTexture(Texture *texture)
		{
			if (texture != nullptr)
			{
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, reinterpret_cast<GLuint>(texture->GetData()));
			}
			else
			{
				glDisable(GL_TEXTURE_2D);
			}

		}

		// --------------------------------------------------------------------------------
		void Renderer::DrawPrimitives(uint32_t numVertices, uint32_t startVertex /* = 0 */)
		{
			glDrawArrays(GL_TRIANGLES, startVertex, numVertices);
			GLenum err = glGetError();
			if (err)
			{
				oakvr::Log::PrintError("glDrawArrays 0x%x", err);
			}
		}

		void Renderer::UseShader(std::shared_ptr<oakvr::render::Shader> &pShader)
		{
			GLuint shaderId = reinterpret_cast<GLuint>(pShader->GetNativeHandle());
			glAttachShader(m_pImpl->m_shaderProgramId, shaderId);
			GLenum err = glGetError();
			if (err)
				oakvr::Log::PrintError("glAttachShader error 0x%x", err);
		}

		void Renderer::PrepareShaders()
		{
			glLinkProgram(m_pImpl->m_shaderProgramId);
			GLenum err = glGetError();
			if (err)
				oakvr::Log::PrintError("glLinkProgram error 0x%x", err);

			//validateProgram(shader_id); // Validate the shader program
			glUseProgram(m_pImpl->m_shaderProgramId);
			err = glGetError();
			if (err)
				oakvr::Log::PrintError("glUseProgram error 0x%x", err);

			oakvr::math::Matrix mProj = oakvr::math::Matrix::PerspectiveProjection(1.05f, 4 / 3.0f, .1f, 100.0f);
			oakvr::math::Matrix mModel = oakvr::math::Matrix::RotationY(3.14 / 4);
			int projectionMatrixLocation = glGetUniformLocation(m_pImpl->m_shaderProgramId, "projectionMatrix");
			int modelMatrixLocation = glGetUniformLocation(m_pImpl->m_shaderProgramId, "modelMatrix");
			glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &mProj.m[0][0]);
			glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &mModel.m[0][0]);
		}

		// --------------------------------------------------------------------------------
		void Renderer::DrawIndexed(uint32_t numIndices, uint8_t stride /* = 4 */, uint32_t startIndex /* = 0 */, uint32_t startVertex /* = 0 */)
		{
			if (stride == 4)
				glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, nullptr);
			else
				glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_SHORT, nullptr);

			GLenum err = glGetError();
			if (err)
			{
				oakvr::Log::PrintError("glDrawArrays 0x%x", err);
			}
			
		}
		
		/*		// --------------------------------------------------------------------------------
		void Renderer::CreateInputLayoutDesc(uint32_t vertexFormat, void *&pLayoutDesc, uint32_t &numElems)
		{
		/*
		D3DVERTEXELEMENT9 layout[12];
		numElems = 0;
		int offset = 0;
		if(vertexFormat & VertexBuffer::eVF_XYZ)
		{
		layout[numElems].Usage = D3DDECLUSAGE_POSITION;
		layout[numElems].UsageIndex = 0;
		layout[numElems].Type = D3DDECLTYPE_FLOAT3;
		layout[numElems].Stream = 0;
		layout[numElems].Offset = offset;
		layout[numElems].Method = D3DDECLMETHOD_DEFAULT;
		offset += 12;
		++numElems;
		}
		if(vertexFormat & VertexBuffer::eVF_Normal)
		{
		layout[numElems].Usage = D3DDECLUSAGE_NORMAL;
		layout[numElems].UsageIndex = 0;
		layout[numElems].Type = D3DDECLTYPE_FLOAT3;
		layout[numElems].Stream = 0;
		layout[numElems].Offset = offset;
		layout[numElems].Method = D3DDECLMETHOD_DEFAULT;
		offset += 12;
		++numElems;
		}
		if(vertexFormat & VertexBuffer::eVF_Diffuse)
		{
		layout[numElems].Usage = D3DDECLUSAGE_COLOR;
		layout[numElems].UsageIndex = 0;
		layout[numElems].Type= D3DDECLTYPE_D3DCOLOR;
		layout[numElems].Stream = 0;
		layout[numElems].Offset = offset;
		layout[numElems].Method = D3DDECLMETHOD_DEFAULT;
		offset += 16;
		++numElems;
		}

		if(vertexFormat & VertexBuffer::eVF_Tex0)
		{
		layout[numElems].Usage = D3DDECLUSAGE_TEXCOORD;
		layout[numElems].UsageIndex = 0;
		layout[numElems].Type = D3DDECLTYPE_FLOAT2;
		layout[numElems].Stream = 0;
		layout[numElems].Offset = offset;
		layout[numElems].Method = D3DDECLMETHOD_DEFAULT;
		offset += 8;
		++numElems;
		}

		pLayoutDesc = new D3DVERTEXELEMENT9[numElems];
		memcpy(pLayoutDesc, layout, numElems * sizeof(D3DVERTEXELEMENT9));

		}
		*/
		
		/*		// --------------------------------------------------------------------------------
		void Renderer::UsePrimitiveTopology( PrimitiveTopology primitiveTopology )
		{
		m_currentPrimitiveTopology = primitiveTopology;
		switch(primitiveTopology)
		{
		case ePT_PointList:
		m_numVerticesPerPrimitive = 1;
		break;
		case ePT_LineList:
		m_numVerticesPerPrimitive = 2;
		break;
		case ePT_LineStrip:
		m_numVerticesPerPrimitive = 2;
		break;
		case ePT_TriangleList:
		m_numVerticesPerPrimitive = 3;
		break;
		case ePT_TriangleStrip:
		m_numVerticesPerPrimitive = 3;
		break;
		default:
		break;
		}
		}
		
		// --------------------------------------------------------------------------------
		void Renderer::UseShader(Shader *pShader)
		{
		}

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
		oakvr::Math::Matrix Renderer::CreateViewMatrix(oakvr::Math::Vector3 eye, oakvr::Math::Vector3 lookAt, oakvr::Math::Vector3 up)
		{
		oakvr::Math::Vector3 look = (lookAt - eye).GetNormalized();
		oakvr::Math::Vector3 right = look.Cross(up).GetNormalized();
		oakvr::Math::Matrix mat;
		mat._11 = right.x;
		mat._12 = right.y;
		mat._13 = right.z;
		mat._14 = 0.0f;

		mat._21 = up.x;
		mat._22 = up.y;
		mat._23 = up.z;
		mat._24 = 0.0f;

		mat._31 = look.x;
		mat._32 = look.y;
		mat._33 = look.z;
		mat._34 = 0.0f;

		mat._41 = eye.Dot(right);
		mat._42 = eye.Dot(up);
		mat._43 = eye.Dot(look);
		mat._44 = 1.0f;

		return mat;
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

