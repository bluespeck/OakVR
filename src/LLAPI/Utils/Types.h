#pragma once

#include <memory>

namespace oakvr
{
	template <typename T>
	using sp = std::shared_ptr < T > ;

	template <typename T>
	using up = std::shared_ptr < T > ;

	using Real = float;
}