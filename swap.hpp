#pragma once

namespace jl
{
	// Both paremeters should support assignement
	template <typename LeftType, typename RightType>
	void swap(LeftType& lhs, RightType& rhs)
	{
		auto temp = lhs;
		lhs = rhs;
		rhs = temp;
	}
}