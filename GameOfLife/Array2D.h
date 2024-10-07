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
		bool isValid(Vec2 pos)
		{
			return pos.x >= 0 && pos.x < mSize.x && pos.y >= 0 && pos.y < mSize.y;
		}

		T& operator[](Vec2 pos)
		{
			if (!isValid(pos))
			{
				throw std::out_of_range("Array2D index out of bounds");
			}
			return mData[pos.y * mSize.x + pos.x];
		}

		Vec2 getSize() { return mSize; }

	private:
		Vec2 mSize;
		std::vector<T> mData;
	};
}