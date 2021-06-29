
#include <iostream>
#include <unordered_map>
#include <string>
#include <fstream>
#include "inputs.h"
#include "op_kernel_type.h"

namespace paddle{
namespace framework{

class OpKernelType;
using OpKernelFunc = std::function<void()>;
using OpKernelMap =
		std::unordered_map<OpKernelType, OpKernelFunc, OpKernelType::Hash>;





static std::unordered_map<std::string, OpKernelMap>&
AllOpKernels() {
	static std::unordered_map<std::string, OpKernelMap> g_all_op_kernels;
	return g_all_op_kernels;
}


void InitAllOpKernels() {
	std::ifstream infile("all_kernels.txt");
	std::string line;
	auto& kernels = AllOpKernels();
	while (std::getline(infile, line)) {
		//std::cout << line << std::endl;

		paddle::framework::OpKernelMap op_kernel_map;

		kernels[line] = op_kernel_map;
	}


}


}
}
