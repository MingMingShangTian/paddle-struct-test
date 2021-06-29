#pragma once

#include <functional>
#include <iostream>
#include <vector>

#include "boost/variant.hpp"


namespace paddle {
namespace platform {

struct CPUPlace {
  // WORKAROUND: for some reason, omitting this constructor
  // causes errors with boost 1.59 and OSX
  CPUPlace() {}

  // needed for variant equality comparison
  inline bool operator==(const CPUPlace &) const { return true; }
  inline bool operator!=(const CPUPlace &) const { return false; }
  inline bool operator<(const CPUPlace &) const { return false; }
};

struct CUDAPlace {
  CUDAPlace() : CUDAPlace(0) {}
  explicit CUDAPlace(int d) : device(d) {}

  inline int GetDeviceId() const { return device; }
  // needed for variant equality comparison
  inline bool operator==(const CUDAPlace &o) const {
    return device == o.device;
  }
  inline bool operator!=(const CUDAPlace &o) const { return !(*this == o); }
  inline bool operator<(const CUDAPlace &o) const { return device < o.device; }

  int device;
};

struct CUDAPinnedPlace {
  CUDAPinnedPlace() {}

  // needed for variant equality comparison
  inline bool operator==(const CUDAPinnedPlace &) const { return true; }
  inline bool operator!=(const CUDAPinnedPlace &) const { return false; }
  inline bool operator<(const CUDAPinnedPlace &) const { return false; }
};

// Place for Baidu Kunlun Accelerator
struct XPUPlace {
  XPUPlace() : XPUPlace(0) {}
  explicit XPUPlace(int d) : device(d) {}

  inline int GetDeviceId() const { return device; }
  // needed for variant equality comparison
  inline bool operator==(const XPUPlace &o) const { return device == o.device; }
  inline bool operator!=(const XPUPlace &o) const { return !(*this == o); }
  inline bool operator<(const XPUPlace &o) const { return device < o.device; }

  int device;
};

struct NPUPlace {
  NPUPlace() : NPUPlace(0) {}
  explicit NPUPlace(int d) : device(d) {}

  inline int GetDeviceId() const { return device; }
  // needed for variant equality comparison
  inline bool operator==(const NPUPlace &o) const { return device == o.device; }
  inline bool operator!=(const NPUPlace &o) const { return !(*this == o); }
  inline bool operator<(const NPUPlace &o) const { return device < o.device; }

  int device;
};

struct NPUPinnedPlace {
  NPUPinnedPlace() {}

  inline bool operator==(const NPUPinnedPlace &) const { return true; }
  inline bool operator!=(const NPUPinnedPlace &) const { return false; }
  inline bool operator<(const NPUPinnedPlace &) const { return false; }
};

struct IsCUDAPlace : public boost::static_visitor<bool> {
  bool operator()(const CPUPlace &) const { return false; }
  bool operator()(const XPUPlace &) const { return false; }
  bool operator()(const NPUPlace &) const { return false; }
  bool operator()(const NPUPinnedPlace &) const { return false; }
  bool operator()(const CUDAPlace &) const { return true; }
  bool operator()(const CUDAPinnedPlace &) const { return false; }
};

struct IsCPUPlace : public boost::static_visitor<bool> {
  bool operator()(const CPUPlace &) const { return true; }
  bool operator()(const XPUPlace &) const { return false; }
  bool operator()(const NPUPlace &) const { return false; }
  bool operator()(const NPUPinnedPlace &) const { return false; }
  bool operator()(const CUDAPlace &) const { return false; }
  bool operator()(const CUDAPinnedPlace &) const { return false; }
};

struct IsCUDAPinnedPlace : public boost::static_visitor<bool> {
  bool operator()(const CPUPlace &) const { return false; }
  bool operator()(const XPUPlace &) const { return false; }
  bool operator()(const NPUPlace &) const { return false; }
  bool operator()(const NPUPinnedPlace &) const { return false; }
  bool operator()(const CUDAPlace &) const { return false; }
  bool operator()(const CUDAPinnedPlace &cuda_pinned) const { return true; }
};

struct IsXPUPlace : public boost::static_visitor<bool> {
  bool operator()(const CPUPlace &) const { return false; }
  bool operator()(const XPUPlace &) const { return true; }
  bool operator()(const NPUPlace &) const { return false; }
  bool operator()(const NPUPinnedPlace &) const { return false; }
  bool operator()(const CUDAPlace &) const { return false; }
  bool operator()(const CUDAPinnedPlace &) const { return false; }
};

struct IsNPUPlace : public boost::static_visitor<bool> {
  bool operator()(const CPUPlace &) const { return false; }
  bool operator()(const XPUPlace &) const { return false; }
  bool operator()(const NPUPlace &) const { return true; }
  bool operator()(const NPUPinnedPlace &) const { return false; }
  bool operator()(const CUDAPlace &) const { return false; }
  bool operator()(const CUDAPinnedPlace &) const { return false; }
};

struct IsNPUPinnedPlace : public boost::static_visitor<bool> {
  bool operator()(const CPUPlace &) const { return false; }
  bool operator()(const XPUPlace &) const { return false; }
  bool operator()(const NPUPlace &) const { return false; }
  bool operator()(const NPUPinnedPlace &) const { return true; }
  bool operator()(const CUDAPlace &) const { return false; }
  bool operator()(const CUDAPinnedPlace &) const { return false; }
};

class Place : public boost::variant<CUDAPlace, XPUPlace, NPUPlace, CPUPlace,
                                    CUDAPinnedPlace, NPUPinnedPlace> {
 private:
  using PlaceBase = boost::variant<CUDAPlace, XPUPlace, NPUPlace, CPUPlace,
                                   CUDAPinnedPlace, NPUPinnedPlace>;

 public:
  Place() = default;
  Place(const CPUPlace &cpu_place) : PlaceBase(cpu_place) {}     // NOLINT
  Place(const XPUPlace &xpu_place) : PlaceBase(xpu_place) {}     // NOLINT
  Place(const NPUPlace &npu_place) : PlaceBase(npu_place) {}     // NOLINT
  Place(const CUDAPlace &cuda_place) : PlaceBase(cuda_place) {}  // NOLINT
  Place(const CUDAPinnedPlace &cuda_pinned_place)                // NOLINT
      : PlaceBase(cuda_pinned_place) {}
  Place(const NPUPinnedPlace &npu_pinned_place)  // NOLINT
      : PlaceBase(npu_pinned_place) {}

  bool operator<(const Place &place) const {
    return PlaceBase::operator<(static_cast<const PlaceBase &>(place));
  }
  bool operator==(const Place &place) const {
    return PlaceBase::operator==(static_cast<const PlaceBase &>(place));
  }
};

using PlaceList = std::vector<Place>;

bool is_gpu_place(const Place &);
bool is_xpu_place(const Place &);
bool is_npu_place(const Place &);
bool is_cpu_place(const Place &);
bool is_cuda_pinned_place(const Place &);
bool is_npu_pinned_place(const Place &);
bool places_are_same_class(const Place &, const Place &);
bool is_same_place(const Place &, const Place &);

std::ostream &operator<<(std::ostream &, const Place &);

template <typename Visitor>
struct PlaceVisitorWrapper
    : public boost::static_visitor<typename Visitor::result_type> {
  const Visitor &visitor_;
  explicit PlaceVisitorWrapper(const Visitor &visitor) : visitor_(visitor) {}

  typename Visitor::result_type operator()(const CPUPlace &cpu) const {
    return visitor_(cpu);
  }

  typename Visitor::result_type operator()(const XPUPlace &xpu) const {
    return typename Visitor::result_type();
  }

  typename Visitor::result_type operator()(const NPUPlace &npu) const {
    return typename Visitor::result_type();
  }

  typename Visitor::result_type operator()(
      const NPUPinnedPlace &npu_pinned) const {
    return typename Visitor::result_type();
  }

  typename Visitor::result_type operator()(const CUDAPlace &cuda) const {
    return typename Visitor::result_type();
  }

  typename Visitor::result_type operator()(
      const CUDAPinnedPlace &cuda_pinned) const {
    return typename Visitor::result_type();
  }
};

template <typename Visitor>
typename Visitor::result_type VisitPlace(const Place &place,
                                         const Visitor &visitor) {
  return boost::apply_visitor(PlaceVisitorWrapper<Visitor>(visitor), place);
}

}  // namespace platform
}  // namespace paddle
