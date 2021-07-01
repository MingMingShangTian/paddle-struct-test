#include <iostream>
#include "llvm/ADT/SmallVector.h"

int main() {
    llvm::SmallVector<int, 10> smallVector;
    for(int i = 0; i < 10; i++)
    {
        smallVector.push_back(i);
    }

    // No heap allocations have been performed up to this point.

    smallVector.push_back(11);
}