#include <iostream>
#include <chrono>


#include "kernels.h"
#include "kernels_absl.h"
#include "kernels_ska.h"
int main() {

//init
	paddle::framework::InitAllOpKernels();
	auto& a = paddle::framework::AllOpKernels();
	std::cout << a.size() <<std::endl;

	paddle::framework::InitAllOpKernels_Absl();
	auto& b = paddle::framework::AllOpKernels_Absl();
	std::cout << b.size() <<std::endl;

	paddle::framework::InitAllOpKernels_Ska();
	auto& c = paddle::framework::AllOpKernels_Ska();
	std::cout << c.size() << std::endl;


	InitKeys();
	

	// test 

	int N = 10000;

	auto t1 = std::chrono::system_clock::now();
	for(int i = 0; i < N; ++i) {
		std::string& key = g_all_keys[i%g_all_keys.size()];
		auto value = a.find(key);
		assert (value != a.end());
	}
	auto t2 = std::chrono::system_clock::now();

	for(int i = 0; i < N; ++i) {
		std::string& key = g_all_keys[i%g_all_keys.size()];
		auto value = b.find(key);
		assert (value != b.end());
	}
	auto t3 = std::chrono::system_clock::now();

	for(int i = 0; i < N; ++i) {
		std::string& key = g_all_keys[i%g_all_keys.size()];
		auto value = c.find(key);
		assert (value != c.end());
	}
	auto t4 = std::chrono::system_clock::now();





	auto d1 = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);
	auto d2 = std::chrono::duration_cast<std::chrono::microseconds>(t3 - t2);
	auto d3 = std::chrono::duration_cast<std::chrono::microseconds>(t4 - t3);
	std::cout << d1.count() << " microsecondes" << std::endl;
	std::cout << d2.count() << " microsecondes" << std::endl;
	std::cout << d3.count() << " microsecondes" << std::endl;


}