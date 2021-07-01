#include <iostream>
#include <absl/container/inlined_vector.h>
#include <chrono>
#include <vector>

void TakesVector(const std::vector<int>& ints);
void TakesSpan(absl::Span<const int> ints);

void PassOnlyFirst3Elements() {
  std::vector<int> ints = MakeInts();
  // We need to create a temporary vector, and incur an allocation and a copy.
  TakesVector(std::vector<int>(ints.begin(), ints.begin() + 3));
  // No copy or allocations are made when using Span.
  TakesSpan(absl::Span<const int>(ints.data(), 3));
}

void PassALiteral() {
  // This creates a temporary std::vector<int>.
  TakesVector({1, 2, 3});
  // Span does not need a temporary allocation and copy, so it is faster.
  TakesSpan({1, 2, 3});
}
void IHaveAnArray() {
  int values[10] = ...;
  // Once more, a temporary std::vector<int> is created.
  TakesVector(std::vector<int>(std::begin(values), std::end(values)));
  // Just pass the array. Span detects the size automatically.
  // No copy was made.
  TakesSpan(values);
}

int main() {

		
		auto t3 = std::chrono::system_clock::now();





		auto d1 = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);
		auto d2 = std::chrono::duration_cast<std::chrono::microseconds>(t3 - t2);
		std::cout << d1.count() << " microsecondes" << std::endl;
		std::cout << d2.count() << " microsecondes" << std::endl;


    //smallVector.push_back(11);
}