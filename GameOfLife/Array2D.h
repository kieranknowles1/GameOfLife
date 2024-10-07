#pragma once

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
		{}

		T& operator[](Vec2 pos)
		{
			return mData[pos.y * mSize.x + pos.x];
		}

		Vec2 getSize() { return mSize; }

	private:
		Vec2 mSize;
		std::vector<T> mData;
	};
}