#pragma once

#include <string>

#include "place.h"


namespace proto {
namespace VarType{
	enum VarType_Type {
  VarType_Type_BOOL = 0,
  VarType_Type_INT16 = 1,
  VarType_Type_INT32 = 2,
  VarType_Type_INT64 = 3,
  VarType_Type_FP16 = 4,
  VarType_Type_FP32 = 5,
  VarType_Type_FP64 = 6,
  VarType_Type_SIZE_T = 19,
  VarType_Type_UINT8 = 20,
  VarType_Type_INT8 = 21,
  VarType_Type_BF16 = 22,
  VarType_Type_COMPLEX64 = 23,
  VarType_Type_COMPLEX128 = 24,
  VarType_Type_LOD_TENSOR = 7,
  VarType_Type_SELECTED_ROWS = 8,
  VarType_Type_FEED_MINIBATCH = 9,
  VarType_Type_FETCH_LIST = 10,
  VarType_Type_STEP_SCOPES = 11,
  VarType_Type_LOD_RANK_TABLE = 12,
  VarType_Type_LOD_TENSOR_ARRAY = 13,
  VarType_Type_PLACE_LIST = 14,
  VarType_Type_READER = 15,
  VarType_Type_RAW = 17,
  VarType_Type_TUPLE = 18
};

typedef VarType_Type Type;


}
}


namespace paddle {
namespace framework {

enum class DataLayout {
  kNHWC = 0,
  kNCHW = 1,
  kAnyLayout = 2,
  kMKLDNN = 3,  // all layouts supported by MKLDNN internally
};

enum class LibraryType {
  kPlain = 0,
  kMKLDNN = 1,
  kCUDNN = 2,
};


class OpKernelType {
 public:
  constexpr static int kDefaultCustomizedTypeValue = 0;

  // In total should be smaller than 64.
  constexpr static int kPlaceBits = 4;
  constexpr static int kPrimaryDTypeBits = 8;
  constexpr static int kLayoutBits = 4;
  constexpr static int kLibBits = 4;
  constexpr static int kCustomizeBits = 4;

  OpKernelType(proto::VarType::Type data_type, platform::Place place,
               DataLayout data_layout = DataLayout::kAnyLayout,
               LibraryType library_type = LibraryType::kPlain,
               int customized_type_value = kDefaultCustomizedTypeValue)
      : data_type_(data_type),
        data_layout_(data_layout),
        place_(place),
        library_type_(library_type),
        customized_type_value_(customized_type_value) {}

/*
  OpKernelType(proto::VarType::Type data_type,
               const platform::DeviceContext& dev_ctx,
               DataLayout data_layout = DataLayout::kAnyLayout,
               LibraryType library_type = LibraryType::kPlain,
               int customized_type_value = kDefaultCustomizedTypeValue)
      : data_type_(data_type),
        data_layout_(data_layout),
        place_(dev_ctx.GetPlace()),
        library_type_(library_type),
        customized_type_value_(customized_type_value) {}
				*/

  virtual ~OpKernelType() {}

  struct Hash {
    size_t operator()(const OpKernelType& key) const {
			int cur_loc = 0;

			int place = key.place_.which();
			cur_loc += OpKernelType::kPlaceBits;

			int data_type = static_cast<int>(key.data_type_) << cur_loc;
			cur_loc += OpKernelType::kPrimaryDTypeBits;

			int data_layout = static_cast<int>(key.data_layout_) << cur_loc;
			cur_loc += OpKernelType::kLayoutBits;

			int library_type = static_cast<int>(key.library_type_) << cur_loc;
			cur_loc += OpKernelType::kLibBits;

			int customized_value = key.customized_type_value_;
			customized_value = customized_value << cur_loc;
			cur_loc += OpKernelType::kCustomizeBits;

			std::hash<int> hasher;
			return hasher(place + data_type + data_layout + library_type +
										customized_value);
				}
  };

  size_t hash_key() const { return Hash()(*this); }

  bool operator<(const OpKernelType& o) const {
    return hash_key() < o.hash_key();
  }

  bool operator==(const OpKernelType& o) const;

  bool operator!=(const OpKernelType& o) const { return !(*this == o); }

  proto::VarType::Type data_type_;
  DataLayout data_layout_;
  platform::Place place_;
  LibraryType library_type_;
  int customized_type_value_;
};

/*
inline std::ostream& operator<<(std::ostream& os,
                                const OpKernelType& kernel_key) {
  os << "data_type[" << kernel_key.data_type_ << "]:data_layout["
     << kernel_key.data_layout_ << "]:place[" << kernel_key.place_
     << "]:library_type[" << kernel_key.library_type_ << "]";
  return os;
}

inline std::string KernelTypeToString(const OpKernelType& kernel_key) {
  std::ostringstream stream;
  stream << kernel_key;
  return stream.str();
}

inline bool NeedTransformLayout(const DataLayout& l, const DataLayout& r) {
  bool ret =
      (l != DataLayout::kAnyLayout && r != DataLayout::kAnyLayout && l != r);
#ifdef PADDLE_WITH_MKLDNN
  // Layout transform needed for either non-MKLDNN to MKLDNN or vice versa
  ret |= (l != DataLayout::kMKLDNN && r == DataLayout::kMKLDNN);
  ret |= (l == DataLayout::kMKLDNN && r != DataLayout::kMKLDNN);
#endif
  return ret;
}

inline bool NeedTransformDataType(const OpKernelType& l,
                                  const OpKernelType& r) {
  return (l.data_type_ != r.data_type_);
}

inline bool NeedTransform(const OpKernelType& l, const OpKernelType& r) {
  return (!platform::places_are_same_class(l.place_, r.place_)) ||
         (l.data_type_ != r.data_type_) ||
         NeedTransformLayout(l.data_layout_, r.data_layout_);
}
*/

}  // namespace framework
}  // namespace paddle
