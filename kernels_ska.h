
#include <iostream>
#include <unordered_map>
#include <string>
#include <fstream>

#include "flat_hash_map/flat_hash_map.hpp"

#include "op_kernel_type.h"

namespace paddle{
namespace framework{

class OpKernelType;
using OpKernelFunc = std::function<void()>;
using OpKernelMap =
		std::unordered_map<OpKernelType, OpKernelFunc, OpKernelType::Hash>;





static ska::flat_hash_map<std::string, OpKernelMap>&
AllOpKernels_Ska() {
	static ska::flat_hash_map<std::string, OpKernelMap> g_all_op_kernels_ska;
	return g_all_op_kernels_ska;
}


void InitAllOpKernels_Ska() {
	std::ifstream infile("all_kernels.txt");
	std::string line;
	auto& kernels = AllOpKernels_Ska();
	while (std::getline(infile, line)) {
		//std::cout << line << std::endl;

		paddle::framework::OpKernelMap op_kernel_map;

		kernels[line] = op_kernel_map;
	}
}


}
}
