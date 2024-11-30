
#include <array>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <string>
#include <sycl/sycl.hpp>

using type_t = int;
constexpr size_t SIZE = 1024;

enum class Operation : uint8_t {
  ADD,
  SUB,
  UNKOWN,
};

namespace {
Operation get_operation(const char *arg) {
  if (std::string("-add") == arg) {
    return Operation::ADD;
  }
  if (std::string("-sub") == arg) {
    return Operation::SUB;
  }
  return Operation::UNKOWN;
}
} // namespace

int main(int argc, const char *argv[]) {
  assert(argc == 2);
  auto operation = get_operation(argv[1]);
  assert(operation != Operation::UNKOWN);

  static std::array<type_t, SIZE> arr1;
  static std::array<type_t, SIZE> arr2;
  static std::array<type_t, SIZE> res;

  arr1.fill(1);
  arr2.fill(2);
  sycl::queue queue;
  {
    sycl::buffer<int, 1> arr1Buf{arr1.data(), sycl::range<1>{SIZE}};
    sycl::buffer<int, 1> arr2Buf{arr2.data(), sycl::range<1>{SIZE}};
    sycl::buffer<int, 1> resBuf{res.data(), sycl::range<1>{SIZE}};
    queue.submit([&](sycl::handler &cgh) {
      sycl::accessor writeArr1{arr1Buf, cgh, sycl::read_only};
      sycl::accessor writeArr2{arr2Buf, cgh, sycl::read_only};
      sycl::accessor writeRes{resBuf, cgh, sycl::write_only, sycl::no_init};
      cgh.parallel_for(SIZE, [=](auto idx) {
        switch (operation) {
        case Operation::ADD:
          writeRes[idx] = writeArr1[idx] + writeArr2[idx];
          break;
        case Operation::SUB:
          writeRes[idx] = writeArr1[idx] - writeArr2[idx];
          break;
        default:
          break;
        }
      });
    });
  }
  for (size_t i = 0; i < SIZE; i++) {
    std::cout << "res[" << i << "] = " << res.at(i) << "\n";
  }
}
