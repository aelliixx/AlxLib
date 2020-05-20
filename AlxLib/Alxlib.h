#pragma once
#include <math.h>
#include <vector>
#include <bitset>

#define ALX_PI 				(3.1415926535897932384626433832795f)
#define SMALL_NUMBER		(1.e-8f)

namespace alx
{
	namespace tpl
	{
		// Lerps between a and b based on alpha
		template<class T, class U>
		static T Lerp(T A, T B, U alpha)
		{
			return (T)(A + alpha * (B - A));
		}

		// Lerps between a and b based on alpha with ease-in defined by exp
		template<class T>
		T InterpEaseIn(T A, T B, float Alpha, float Exp)
		{
			const float ModifiedAlpha = pow(Alpha, Exp);
			return Lerp<T>(A, B, ModifiedAlpha);
		}

		// Lerps between a and b based on alpha with ease-out defined by exp
		template<class T>
		T InterpEaseOut(T A, T B, float Alpha, float Exp)
		{
			const float ModifiedAlpha = 1.f - pow(1.f - Alpha, Exp);
			return Lerp<T>(A, B, ModifiedAlpha);
		}

		// A combination of InterpEaseIn and InterpEaseOut
		template<class T>
		T InterpEaseInOut(T A, T B, float alpha, float exp)
		{
			return Lerp<T>(A, B, (alpha < 0.5f) ?
				InterpEaseIn(0.f, 1.f, alpha * 2.f, exp) * 0.5f :
				InterpEaseOut(0.f, 1.f, alpha * 2.f - 1.f, exp) * 0.5f + 0.5f);
		}

		// Clamps value between min and max
		template<class T>
		T Clamp(T value, T Min, T Max)
		{
			return value < Min ? Min : value < Max ? value : Max;
		}
	}

	/// float wrappers for lerps
	float fLerp(float A, float B, float alpha)
	{
		return tpl::Lerp<float>(A, B, alpha);
	}

	float fInterpEaseIn(float A, float B, float alpha, float exp)
	{
		return tpl::InterpEaseIn<float>(A, B, alpha, exp);
	}

	float fInterpEaseOut(float A, float B, float alpha, float exp)
	{
		return tpl::InterpEaseOut<float>(A, B, alpha, exp);
	}

	/// float wrapper for Clamp()
	float fClamp(float value, float min, float max)
	{
		return tpl::Clamp<float>(value, min, max);
	}


	/// number manipulation
	// Checks if a number is near 0 or <= a given tolerance; good for avoiding division by 0
	bool NearTolerance(float value, float errorTolerance = SMALL_NUMBER)
	{
		return abs(value) <= errorTolerance;
	}

	// Gets the percentage of how far a value is within a given range
	static float GetRangeAlpha(float minValue, float maxValue, float value)
	{
		const float div = maxValue - minValue;
		if (NearTolerance(div))
			return (value >= maxValue) ? 1.0f : 0.0f;
		return (value - minValue) / div;
	}
	
	// Normalises a value to a given range
	float GetMappedValueUnclamped(float inMin, float inMax, float outMin, float outMax, float value)
	{
		return fLerp(outMin, outMax, GetRangeAlpha(inMin, inMax, value));
	}

	// Clamps a value and normalises it to a given range
	float GetMappedValueClamped(float inMin, float inMax, float outMin, float outMax, float value)
	{
		const float clampedAlpha = fClamp(GetRangeAlpha(inMin, inMax, value), 0.0f, 1.0f);
		return fLerp(outMin, outMax, clampedAlpha);
	}

	/// rng
	// Generates a random number based on a seed using the Lehmer RNG algorithm
	uint64_t LehmerInt64(const uint64_t seed)
	{
		uint64_t sLehmer = seed;
		sLehmer += 0xe120fc15;
		uint64_t tmp;
		tmp = sLehmer * 0x4a39b70d;
		uint64_t m1 = (tmp >> 32) ^ tmp;
		tmp = m1 * 0x12fad5c9;
		uint64_t m2 = (tmp >> 32) ^ tmp;
		return m2;
	}

	uint64_t LehmerInt64()
	{
		static uint64_t seed;
		seed++;
		return LehmerInt64(seed);
	}

	// Gets a random float between 0.f and 1.f using the Lehmer RNG algorithm
	float LehmerFloat(const uint64_t seed)
	{
		return (float)LehmerInt64(seed) / (float)UINT64_MAX;
	}

	float LehmerFloat()
	{
		static uint64_t seed;
		seed++;
		return (float)LehmerInt64(seed) / (float)UINT64_MAX;
	}

	// Gets a random bool using the Lehmer RNG algorith
	bool randBool(const uint64_t seed)
	{
		return (bool)(LehmerInt64(seed) % 2);
	}

	bool randBool()
	{
		static uint64_t seed;
		seed++;
		return (bool)(LehmerInt64(seed) % 2);
	}

	/// vectors from alxvec
	// Get index of the first given element in vector
	template <class T>
	int findInVector(T a, std::vector<T> vect)
	{
		for (int i = 0; i < vect.size(); i++)
		{
			if (a == vect[i])
			{
				return i;
			}
		}
		return -1;
	}

	// Get index of the first given string in a vector of strings
	int findInVector(std::string a, std::vector<std::string> vect)
	{
		for (int i = 0; i < vect.size(); i++)
		{
			if (a == vect[i])
			{
				return i;
			}
		}
		return -1;
	}

	// Get index of the nth given element in vector
	template <class T>
	int findInVector(T a, std::vector<T> vect, int nth)
	{
		int iteration = 1;
		for (int i = 0; i < vect.size(); i++)
		{
			if (a == vect[i])
			{
				if (iteration == nth) { return i; }
				else { iteration++; }
			}
		}
		return -1;
	}

	// Get index of the nth given string in a vector of strings
	int findInVector(std::string a, std::vector<std::string> vect, int nth)
	{
		int iteration = 1;
		for (int i = 0; i < vect.size(); i++)
		{
			if (a == vect[i])
			{
				if (iteration == nth) { return i; }
				else { iteration++; }
			}
		}
		return -1;
	}

	/// vector objects
	// A 2D vector object
	template <class T>
	struct vector2d
	{
		T x, y;

		// todo: vector init and op overloading
	};
	typedef vector2d<float>		vec2d;
	typedef vector2d<double>  vec2d64;

	// A 3D vector object
	template <class T>
	struct vector3d
	{
		T x, y, z;
	};
	typedef vector3d<float>		vec3d;
	typedef vector3d<double>  vec3d64;

	/// Bit operations
	// Remove bits outside of the mask (i.e. 0b1100 with mask of 0b1010 will result in 0b1000)
	uint32_t maskBits(uint32_t a, uint32_t mask)
	{
		return a & mask;
	}

	// Reverse bit order (i.e. 11010010 -> 01001011)
	uint32_t reverseBits(uint32_t a)
	{
		a = (a & 0xF0) >> 4 | (a & 0x0F) << 4;
		a = (a & 0xCC) >> 2 | (a & 0x33) << 2;
		a = (a & 0xAA) >> 1 | (a & 0x55) << 1;
		return a;
	}

	// Get int as a bit string
	std::string decToBin32(int32_t decimal)
	{
		return std::bitset<32>(decimal).to_string();
	}
	std::string decToBin16(int16_t decimal)
	{
		return std::bitset<16>(decimal).to_string();
	}
}