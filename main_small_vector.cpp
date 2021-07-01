#include <iostream>
#include <absl/container/inlined_vector.h>
#include <chrono>
#include <vector>

int main() {

		const int N= 20;

    absl::InlinedVector<int, N> smallVector;
		std::vector<int> std_vector;
		auto t1 = std::chrono::system_clock::now();
    for(int i = 0; i < N; i++) {
        smallVector.push_back(i);
    }

    // No heap allocations have been performed up to this point.
		
		for(int i=0; i< N; i++) {
			smallVector[i] *=2;
		}
		
		auto t2 = std::chrono::system_clock::now();

		for(int i = 0; i< N; i++) {
			std_vector.push_back(i);
		}
		
		for(int i=0; i< N; i++) {
			//std::cout << std_vector[i] << std::endl;
			std_vector[i] *=2;
		}
		
		auto t3 = std::chrono::system_clock::now();





		auto d1 = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);
		auto d2 = std::chrono::duration_cast<std::chrono::microseconds>(t3 - t2);
		std::cout << d1.count() << " microsecondes" << std::endl;
		std::cout << d2.count() << " microsecondes" << std::endl;


    //smallVector.push_back(11);
}