#include <iostream>

#include "array.h"

int main() {
    Array<int> arr{10};
    std::cout << arr << std::endl;

    Array<int> arr1{arr};
    std::cout << arr1 << std::endl;

    Array<int> arr2{10};
    std::cout << arr2 << std::endl;
    arr2 = arr1;
    std::cout << arr2 << std::endl;

    Array<int> arr3{std::move(arr2)};
    std::cout << arr2 << std::endl;
    std::cout << arr3 << std::endl;

    Array<int> arr4{10};
    arr4 = std::move(arr3);
    std::cout << arr3 << std::endl;
    std::cout << arr4 << std::endl;

    for (size_t idx=0; idx<10; ++idx) {
        arr[idx] = idx + 1;
    }
    std::cout << arr << std::endl;
    arr.Swap(0, 5);
    std::cout << *(arr + 5) << std::endl;
    // std::cout << arr[11] << std::endl;
    

    Array<int> arr5{10, 42};
    std::cout << arr5 << std::endl;

    const Array<int> arr6{10, 10};
    std::cout << arr6 << std::endl;
    std::cout << arr6[0] << std::endl;
    std::cout << *(arr6 + 1) << std::endl;

    Array<int> arr7{10, 42};
    arr7.Fill(10);
    std::cout << arr7 << std::endl;

    for (size_t idx=0; idx<10; ++idx) {
        arr[idx] = idx + 1;
    }
    std::cout << arr << std::endl;
    arr.Reverse();
    std::cout << arr << std::endl;

    return 0;
}
