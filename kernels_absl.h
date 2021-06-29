
#include <iostream>
#include <unordered_map>
#include <string>
#include <fstream>

#include <absl/container/flat_hash_map.h>

#include "op_kernel_type.h"

namespace paddle{
namespace framework{

class OpKernelType;
using OpKernelFunc = std::function<void()>;
using OpKernelMap =
		std::unordered_map<OpKernelType, OpKernelFunc, OpKernelType::Hash>;





static absl::flat_hash_map<std::string, OpKernelMap>&
AllOpKernels_Absl() {
	static absl::flat_hash_map<std::string, OpKernelMap> g_all_op_kernels_absl;
	return g_all_op_kernels_absl;
}


void InitAllOpKernels_Absl() {
	std::ifstream infile("all_kernels.txt");
	std::string line;
	auto& kernels = AllOpKernels_Absl();
	while (std::getline(infile, line)) {
		//std::cout << line << std::endl;

		paddle::framework::OpKernelMap op_kernel_map;

		kernels[line] = op_kernel_map;
	}
}


}
}
