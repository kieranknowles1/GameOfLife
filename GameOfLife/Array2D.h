#pragma once

#include <stdexcept>
#include <vector>

namespace GameOfLife {

	struct Vec2
	{
		int x;
		int y;
	};

	// 2D array. Size must be known at construction time.
	template <typename T>
	class Array2D
	{
	public:
		Array2D(Vec2 size)
			: mSize(size)
			, mData(size.x * size.y)
		{
			if (size.x <= 0 || size.y <= 0)
			{
				throw std::invalid_argument("Array2D size must be positive");
			}
		}

		// Get whether a position is valid
		bool isValid(Vec2 pos) const
		{
			return pos.x >= 0 && pos.x < mSize.x && pos.y >= 0 && pos.y < mSize.y;
		}

		const T& operator[](Vec2 pos) const
		{
			if (!isValid(pos))
			{
				throw std::out_of_range("Array2D index out of bounds");
			}
			return mData[pos.y * mSize.x + pos.x];
		}

		T& operator[](Vec2 pos)
		{
			// const_cast is used to avoid code duplication by calling the overload (Vec2<T> vs const Vec2<T>)
			auto constThis = const_cast<const Array2D*>(this);
			return const_cast<T&>(constThis->operator[](pos));
		}

		Vec2 getSize() const { return mSize; }

	private:
		Vec2 mSize;
		std::vector<T> mData;
	};
}