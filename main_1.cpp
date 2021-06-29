#include <iostream>
#include <chrono>
#include <string>
#include <unordered_map>
#include <absl/container/flat_hash_map.h>

#include "inputs.h"


int main() {

//init
	InitKeys();
	
	std::unordered_map<std::string, std::string> a;
	absl::flat_hash_map<std::string, std::string, absl::Hash<std::string>> b;

	for(int i =0; i < g_all_keys.size(); ++i) {
		std::string key = g_all_keys[i];
		a[key] = key;
		b[key] = key;
	}

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


	auto d1 = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);
	auto d2 = std::chrono::duration_cast<std::chrono::microseconds>(t3 - t2);
	std::cout << d1.count() << " microsecondes" << std::endl;
	std::cout << d2.count() << " microsecondes" << std::endl;


}