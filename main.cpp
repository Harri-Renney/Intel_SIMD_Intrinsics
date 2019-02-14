#include <iostream>
#include <chrono>

//Intel CPU SIMD Intrinsics//
#include <xmmintrin.h>

const int size = 400000000;
const int numberTimesDoubled = 8;

int main(int argc, char* argv[])
{
	std::chrono::time_point<std::chrono::steady_clock> start;


	float* a = new float[size];
	for (int i = 0; i != size; ++i)
	{
		a[i] = 1;
	}

	start = std::chrono::steady_clock::now();
	for (int i = 0; i != size; ++i)
	{
		for (int j = 0; j != numberTimesDoubled; ++j)
		{
			a[i] = a[i] * 2;
		}
	}
	std::cout << "Contents of a: " << a[0] << std::endl;

	auto end = std::chrono::steady_clock::now();
	auto diff = end - start;
	std::cout << "Total time to complete: " << std::chrono::duration<double>(diff).count() << "s" << std::endl;
	std::cout << "Total time to complete: " << std::chrono::duration <double, std::milli>(diff).count() << "ms" << std::endl;
	std::cout << "Total time to complete: " << std::chrono::duration <double, std::nano>(diff).count() << "ns" << std::endl;

	const float two = 2.0;
	__m128 constantTwo = _mm_load_ps1(&two);

	float* b = new float[size];
	for (int i = 0; i != size; ++i)
	{
		b[i] = 1;
	}
	start = std::chrono::steady_clock::now();
	__m128 bVector;
	for (int i = 0; i < size-4; i+=4)
	{
		bVector = _mm_load_ps(b + i);
		for (int j = 0; j != numberTimesDoubled; ++j)
		{
			bVector = _mm_mul_ps(bVector, constantTwo);
		}
		_mm_store_ps(b+i, bVector);
	}
	std::cout << "Contents of b: " << b[0] << std::endl;

	end = std::chrono::steady_clock::now();
	diff = end - start;
	std::cout << "Total time to complete: " << std::chrono::duration<double>(diff).count() << "s" << std::endl;
	std::cout << "Total time to complete: " << std::chrono::duration <double, std::milli>(diff).count() << "ms" << std::endl;
	std::cout << "Total time to complete: " << std::chrono::duration <double, std::nano>(diff).count() << "ns" << std::endl;

	printf("Hit ENTER to stop program.\n");
	getchar();

	return 0;
}