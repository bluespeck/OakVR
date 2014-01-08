#include "Common.h"
#include "Renderer/Renderer/Renderer.h"

#include "Renderer/Renderer/RendererCommon.h"
#include "Renderer/Renderer/RendererUtils.h"
#include "Renderer/Renderer/VertexBuffer.h"
#include "Renderer/Renderer/IndexBuffer.h"
#include "Renderer/Renderer/Texture.h"
#include "Renderer/Renderer/Color.h"
#include "Renderer/Renderer/MeshManager.h"
#include "Renderer/Renderer/Mesh.h"

#include "Math/Matrix.h"
#include "Math/Transform.h"
#include "Renderer/Renderer/Shader.h"

#include "FileIO/File.h"
#include "Log/Log.h"
//#include "ResourceManager/Image.h"

#include <cassert>

namespace oakvr
{
	namespace render
	{
		class Renderer::RendererImpl
		{
		public:
			void *m_pDevice;                    // OpenGL device interface (context)
			void *m_pWorkerThreadDevice;		// worker thread context
			long m_mainThreadId;
			long m_shaderProgramId;
		};

		// --------------------------------------------------------------------------------
		Renderer::Renderer()
			: m_pImpl{ new RendererImpl() }
		{
		}

		Renderer::~Renderer()
		{
			// Terminate GLFW
			glfwTerminate();
		}

		// --------------------------------------------------------------------------------
		bool Renderer::Initialize()
		{
			glewExperimental = GL_TRUE;
			GLenum err = glewInit();
			if (err != GLEW_OK)
			{
				Log::PrintError("Failed to initialize GLEW. (%s)\n", glewGetErrorString(err));
				return false;
			}
			else
			{
				Log::PrintInfo("GLEW initialized!\n");
			}
			
			int version[] = { 0, 0};
			glGetIntegerv(GL_MAJOR_VERSION, &version[0]);
			glGetIntegerv(GL_MINOR_VERSION, &version[1]);
			Log::PrintInfo("OpenGL version %d.%d\n", version[0], version[1]);

			glCullFace(GL_BACK);
			glFrontFace(GL_CW);
			glEnable(GL_CULL_FACE);
			glViewport(0, 0, m_pRenderWindow->GetWidth(), m_pRenderWindow->GetHeight());
			


			//			m_shaderProgramId = glCreateProgram();

			m_bInitialized = true;
			return true;
		}

		void Renderer::SetRenderWindow(std::shared_ptr<RenderWindow> pRenderWindow)
		{
			m_pRenderWindow = pRenderWindow;
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

		// --------------------------------------------------------------------------------
		void Renderer::Update(float dt)
		{
			BeginDraw();
			EndDraw();
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
		void Renderer::DrawPrimitives(uint32_t numPrimitives, uint32_t startVertex /* = 0 */)
		{
			//GLenum pt;

			//SetMatrices();

			//UseShaderProgram();

			//glDrawArrays(pt, startVertex, numPrimitives * m_numVerticesPerPrimitive);
			glDrawArrays(GL_TRIANGLES, startVertex, numPrimitives * 3);
		}

		// --------------------------------------------------------------------------------
		/*		void Renderer::UseShaderProgram()
		{
		if(!m_pCurrentVertexShader || !m_pCurrentVertexShader->IsReady() || !m_pCurrentPixelShader || !m_pCurrentPixelShader->IsReady())
		{
		glUseProgramObjectARB(0);
		return;
		}

		glAttachObjectARB(m_shaderProgramId, (GLuint)m_pCurrentVertexShader->GetCompiledShader());
		glAttachObjectARB(m_shaderProgramId, (GLuint)m_pCurrentPixelShader->GetCompiledShader());

		glLinkProgramARB(m_shaderProgramId);
		GLint linkSuccess;
		glGetProgramiv(m_shaderProgramId, GL_LINK_STATUS, &linkSuccess);
		if(!linkSuccess)
		{
		GLcharARB infoLog[1024];
		GLsizei charsWritten;
		glGetInfoLogARB(m_shaderProgramId, 1024, &charsWritten, infoLog);
		infoLog[charsWritten] = 0;
		printf("[oakvr] OpenGL shader program link has failed: %s\n", infoLog);
		exit(1);
		}

		glUseProgramObjectARB(m_shaderProgramId);

		}
		*/
		// --------------------------------------------------------------------------------
		void Renderer::DrawIndexedPrimitives(uint32_t numPrimitives, uint32_t /*numVertices*/, uint32_t startIndex /* = 0 */, uint32_t startVertex /* = 0 */)
		{
			/*	uint8_t numIndicesPerPrimitive = 0;
			GLenum pt;
			switch( m_currentPrimitiveTopology )
			{
			case ePT_PointList:
			numIndicesPerPrimitive = 1;
			pt = GL_POINTS;
			break;
			case ePT_LineList:
			pt = GL_LINES;
			numIndicesPerPrimitive = 2;
			break;
			case ePT_LineStrip:
			pt = GL_LINE_STRIP;
			numIndicesPerPrimitive = 2;
			break;
			case ePT_TriangleList:
			pt = GL_TRIANGLES;
			numIndicesPerPrimitive = 3;
			break;
			case ePT_TriangleStrip:
			pt = GL_TRIANGLE_STRIP;
			numIndicesPerPrimitive = 3;
			break;
			default:
			assert("Unknown primitive topology" && 0);
			break;
			}

			SetMatrices();

			UseShaderProgram();

			// TODO figure out how to set first index and first vertex to use from the buffers
			glDrawElements(pt, numIndicesPerPrimitive * numPrimitives, GL_UNSIGNED_INT, 0);
			if(glGetError() != GL_NO_ERROR)
			{
			printf("glDrawElements error!");
			}
			*/

			glDrawArrays(GL_TRIANGLES, startVertex, numPrimitives * 3);
		}

		// --------------------------------------------------------------------------------
		void Renderer::CreateIndexBuffer(IndexBuffer *pIndexBuffer)
		{
			/*GLuint ibId;
			glGenBuffersARB(1, &ibId);
			glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER, ibId);
			glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER, pIndexBuffer->GetIndexSize() * pIndexBuffer->GetIndexCount(), NULL, GL_DYNAMIC_DRAW);

			pIndexBuffer->SetData((void *)ibId);
			*/
		}

		// --------------------------------------------------------------------------------
		void Renderer::LockIndexBuffer(IndexBuffer *pIndexBuffer, void **ppBuff, uint32_t offsetToLock, uint32_t sizeToLock, uint32_t flags)
		{	/*
			int oldId = 0;
			glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &oldId);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, (int)pIndexBuffer->GetData());
			*ppBuff = glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_READ_WRITE);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, oldId);
			*/
		}

		// --------------------------------------------------------------------------------
		void Renderer::UnlockIndexBuffer(IndexBuffer *pIndexBuffer)
		{
			/*
			int oldId = 0;
			glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &oldId);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, (int)pIndexBuffer->GetData());
			glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, oldId);
			*/
		}

		// --------------------------------------------------------------------------------
		void Renderer::ReleaseIndexBuffer(IndexBuffer *pIndexBuffer)
		{
			/*
			GLuint id = (GLuint)pIndexBuffer->GetData();
			glDeleteBuffers(1, &id);
			*/
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

		// --------------------------------------------------------------------------------
		void Renderer::UseIndexBuffer(IndexBuffer *pIndexBuffer)
		{
			/*			if(!pIndexBuffer)
			glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER, 0);
			else
			glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER, (GLuint)pIndexBuffer->GetData());
			m_pCurrentIndexBuffer = pIndexBuffer;
			*/
		}

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

