#pragma once

#include <sstream>
#include <string>
#include <stdexcept>
#include <vector>

#include "Serializer.h"

namespace GameOfLife {

	struct Vec2
	{
		int x;
		int y;

		Vec2 operator+(Vec2 other) const
		{
			return { x + other.x, y + other.y };
		}
		Vec2 operator-(Vec2 other) const
		{
			return { x - other.x, y - other.y };
		}

		Vec2 operator*(int scalar) const
		{
			return { x * scalar, y * scalar };
		}

		bool operator==(Vec2 other) const
		{
			return x == other.x && y == other.y;
		}
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

		// Convert the Array2D to a string that can be later loaded
		std::string serialize() const {
			std::string result;
			result +=
				std::to_string(mSize.x)
				+ ' '
				+ std::to_string(mSize.y)
				+ '\n';

			return result + serializeBody();
		}
		// Load an Array2D from a string
		static Array2D deserialize(std::stringstream& str) {
			auto size = Serializer::readVec2(str);
			auto arr = Array2D(size);
			arr.deserializeBody(str);
			return arr;
		}

		// Must be specialised for each implementation
		std::string serializeBody() const;
		// Read body into this
		void deserializeBody(std::stringstream& str);

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