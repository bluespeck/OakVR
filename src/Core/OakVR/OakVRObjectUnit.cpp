#include "OakVRObjectUnit.h"

#include "Log/Log.h"

namespace oakvr
{
	void OakVRObjectUnit::AddObject(ObjectSharedPointer pObject, const StringId &parentId)
	{
		m_objectMap[pObject->GetId()] = pObject;
		auto pCurrentParent = pObject->GetParent();
		
		if (parentId != pCurrentParent->GetId())
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

	void OakVRObjectUnit::RemoveObject(const StringId &id)
	{
		auto it = m_objectMap.find(id);
		if (it != m_objectMap.end())
		{
			if (id != "root")
			{
				auto pObject = it->second;
				pObject->GetParent()->RemoveChild(pObject);
			}
			m_objectMap.erase(it);
		}
	}

	ObjectSharedPointer OakVRObjectUnit::FindObject(const StringId &objectId)
	{
		auto it = m_objectMap.find(objectId);
		if (it != std::end(m_objectMap))
		{
			return it->second;
		}
		return nullptr;
	}

	void OakVRObjectUnit::TransferObject(const StringId &id, const StringId &newParentId)
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