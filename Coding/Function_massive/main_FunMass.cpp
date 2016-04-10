#include <functional>
#include <vector>
#include <iostream>

float f0(float a, float b) { return a*b; }
float f1(float a, float b) { return a + b; }
float f2(float a, float b) { return a - b; }
float f3(float a, float b) { return a / b; }

int main()
{
	std::vector<std::function<float(float, float)>> v = { f0, f1, f2, f3 };
	float a = 5, b = 7;

	std::cout << "a = " << a << " | b = " << b << " (* + - /):" << std::endl;
	for (int i = 0; i < 4;i++)
	std::cout << v[i](a, b) << std::endl;

	system("pause");
	return 0;
}