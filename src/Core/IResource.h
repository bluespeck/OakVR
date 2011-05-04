#ifndef __OAK3D_INCLUDE_IRESOURCE_H__
#define __OAK3D_INCLUDE_IRESOURCE_H__

#include <string>

class IResource
{
public:
	IResource() {}
	virtual ~IResource() {}

	virtual void Load(std::wstring path) = 0;
	virtual void Reload() = 0;
	virtual void Release() = 0;

private:
	long m_id;
};

#endif
