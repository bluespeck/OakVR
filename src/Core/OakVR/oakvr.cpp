#include "oakvr.h"
#include "OakVR/Engine.h"
#include "Time/Timer.h"
#include "Log/Log.h"

#include "Renderer/Renderer/Mesh.h"
#include "OakVR/Camera.h"

#include <iostream>

namespace oakvr
{
	// --------------------------------------------------------------------------------
	bool oakvrInit( std::vector<std::string> cmdLine )
	{
		Log::SetMaxLevel(Log::LogLevel::info);
		for (auto e : OakVR::GetInstance().m_initializers)
			e();
		return true;
	}

	// --------------------------------------------------------------------------------
	bool oakvrUpdate()
	{
		return OakVR::GetInstance().Update();
	}

	// --------------------------------------------------------------------------------
	void oakvrExit()
	{
		OakVR::GetInstance().CleanupEngine();
		Log::PrintInfo("OakVR shutting down!\n");
		
	}


	// --------------------------------------------------------------------------------
	OakVR::OakVR()
	{
		if(!m_engine.Initialize())
		{
			Log::PrintError("Failed to initialize OakVR!\n");
			exit(1);
		}
	}

	

	// --------------------------------------------------------------------------------
	bool OakVR::Update()
	{
		return m_engine.Update();
		
		//std::cout << "Current time: " << m_sEngine.GetTimer().GetElapsedTime() << std::endl;
	}

	void OakVR::CleanupEngine()
	{
		m_engine.CleanUp();
	}

	// --------------------------------------------------------------------------------
	OakVR::~OakVR()
	{
	}
	
	void OakVR::RegisterUpdateable(std::shared_ptr<oakvr::Updateable> pUpdateable)
	{
		m_engine.RegisterUpdateable(pUpdateable);
	}

	void OakVR::UnregisterUpdateable(std::shared_ptr<oakvr::Updateable> pUpdateable)
	{
		m_engine.UnregisterUpdateable(pUpdateable);
	}

	// interface relay
	void OakVR::RegisterMesh(std::shared_ptr<oakvr::render::Mesh> pMesh)
	{
		m_engine.RegisterMesh(pMesh);
	}

	void OakVR::RegisterShader(std::string shaderName)
	{
		m_engine.RegisterShader(shaderName);
	}

	void OakVR::RegisterCamera(std::shared_ptr<oakvr::render::Camera> pCamera)
	{
		m_engine.RegisterCamera(pCamera);
	}

	void OakVR::UnregisterCamera(std::shared_ptr<oakvr::render::Camera> pCamera)
	{
		m_engine.UnregisterCamera(pCamera);
	}

	std::shared_ptr<oakvr::render::Camera> OakVR::GetCurrentCamera()
	{
		return m_engine.GetCurrentCamera();
	}

	void OakVR::SetCurrentCamera(std::shared_ptr<oakvr::render::Camera> pCamera)
	{
		m_engine.SetCurrentCamera(pCamera);
	}

	std::shared_ptr<oakvr::core::MemoryBuffer> OakVR::GetResource(const std::string &id)
	{
		return m_engine.GetResource(id);
	}

	void OakVR::RegisterSubFolderPaths(const std::string &path)
	{
		return m_engine.RegisterSubFolderPaths(path);
	}

}	// namespace oakvr
