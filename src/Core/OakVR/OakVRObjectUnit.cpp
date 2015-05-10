#include "OakVRObjectUnitImpl.h"

#include <algorithm>
#include <memory>

#include "Log/Log.h"


namespace oakvr
{
	OakVRObjectUnit::OakVRObjectUnit()
	{
		m_pImpl = std::make_unique<OakVRObjectUnitImpl>();
	}

	OakVRObjectUnit::~OakVRObjectUnit()
	{
	}

	ObjectSharedPointer OakVRObjectUnit::CreateObject(const StringId &objId)
	{
		return std::make_shared<Object>(objId);
	}

	auto OakVRObjectUnit::AddObjectToGraph(ObjectSharedPointer pObject, const StringId &parentId) -> void
	{
		OAKVR_ASSERT(m_pImpl);

		auto &objectMap = m_pImpl->m_objectMap;
		auto &objectVector = m_pImpl->m_objectVector;
		objectMap[pObject->GetId()] = pObject;
		objectVector.push_back(pObject);
		auto pCurrentParent = pObject->GetParent();
		
		if (!pCurrentParent || parentId != pCurrentParent->GetId())
		{
			// we must also add the object as a child of the parent
			auto pParent = FindObject(parentId);
			
			if (pParent)
			{
				pParent->AddChild(pObject);
			}
			else
			{
				Log::Error("Parent id [%s] was not found", parentId.c_str());
			}

			pObject->SetParent(pParent);
		}
	}

	auto OakVRObjectUnit::RemoveObjectFromGraph(const StringId &id) -> void
	{
		OAKVR_ASSERT(m_pImpl);

		auto &objectMap = m_pImpl->m_objectMap;
		auto it = objectMap.find(id);
		if (it != objectMap.end())
		{
			if (id != "root")
			{
				auto pObject = it->second;
				pObject->GetParent()->RemoveChild(pObject);
			}
			m_pImpl->m_objectMap.erase(it);
		}

		auto &objectVector = m_pImpl->m_objectVector;
		objectVector.erase(std::remove_if(std::begin(objectVector), std::end(objectVector), [&id](const ObjectSharedPointer &pObj) { return pObj->GetId() == id; }));
	}

	ObjectSharedPointer OakVRObjectUnit::FindObject(const StringId &objectId)
	{
		OAKVR_ASSERT(m_pImpl);

		auto &objectMap = m_pImpl->m_objectMap;
		auto it = objectMap.find(objectId);
		if (it != std::end(objectMap))
		{
			return it->second;
		}
		return nullptr;
	}

	auto OakVRObjectUnit::TransferObject(const StringId &id, const StringId &newParentId) -> void
	{
		if (id == "root")
			return;
		
		auto pParent = FindObject(newParentId);
		if (pParent)
		{
			auto pObj = FindObject(id);
			if (pObj)
			{
				pObj->GetParent()->RemoveChild(pObj);
				pObj->SetParent(pParent);
				pParent->AddChild(pObj);
				
			}
			
		}
	}
}