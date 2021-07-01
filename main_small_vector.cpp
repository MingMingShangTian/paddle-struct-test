#include <iostream>
#include <absl/container/inlined_vector.h>
#include <chrono>
#include <string>
#include <vector>
#include "llvm/ADT/SmallVector.h"


int main(int argc, char** argv) {
		const int N(20);

    absl::InlinedVector<int, N> absl_smallVector;
    llvm::SmallVector<int, N> llvm_smallVector;
		std::vector<int> std_vector;

		auto t1 = std::chrono::system_clock::now();

    for(int i = 0; i < N; i++) {
        absl_smallVector.push_back(i);
    }
		for(int i=0; i< N; i++) {
			absl_smallVector[i] *=2;
		}

		auto t2 = std::chrono::system_clock::now();

		for(int i = 0; i< N; i++) {
			llvm_smallVector.push_back(i);
		}
		for(int i=0; i< N; i++) {
			//std::cout << std_vector[i] << std::endl;
			llvm_smallVector[i] *=2;
		}
		
		auto t3 = std::chrono::system_clock::now();

		for(int i = 0; i< N; i++) {
			std_vector.push_back(i);
		}
		for(int i=0; i< N; i++) {
			//std::cout << std_vector[i] << std::endl;
			std_vector[i] *=2;
		}
		
		auto t4 = std::chrono::system_clock::now();

		auto d1 = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);
		auto d2 = std::chrono::duration_cast<std::chrono::microseconds>(t3 - t2);
		auto d3 = std::chrono::duration_cast<std::chrono::microseconds>(t4 - t3);
		std::cout << "absl: " << d1.count() << " microsecondes" << std::endl;
		std::cout << "llvm: " << d2.count() << " microsecondes" << std::endl;
		std::cout <<  "std: " << d3.count() << " microsecondes" << std::endl;
}