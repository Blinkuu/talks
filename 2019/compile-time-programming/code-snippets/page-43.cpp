#include <type_traits>
#include <cstring>
#include <iostream>
#include <string_view>

template<typename T>
void print(const T& obj) {
    std::cout << "x = " << obj.x << ", y = " << obj.y << "\n";
}

void print(const char* str) {
    std::cout << str;
}

void println() {
    std::cout << "\n";
}

struct PODType {
    int x;
    int y;
};

struct NonPODType {

    NonPODType(int _x, int _y) : x(_x), y(_y) {}

    NonPODType(const NonPODType& rhs) {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        x = rhs.x;
        y = rhs.y;
    }

    int x;
    int y;
};

template<bool>
struct Swap {
    template<typename T>
    static void swap(T& lhs, T& rhs) {
        T tmp;
        std::memcpy(&tmp, &lhs, sizeof(T));
        std::memcpy(&lhs, &rhs, sizeof(T));
        std::memcpy(&rhs, &tmp, sizeof(T));
    }
};

template<>
struct Swap<false> {
    template<typename T>
    static void swap(T& lhs, T& rhs) {
        T tmp(lhs);
        lhs = rhs;
        rhs = tmp;
    }
};

// C++14
template<typename T>
void swap1(T& lhs, T& rhs) {
    Swap<std::is_pod_v<T>>::swap(lhs, rhs);
}

// C++17
template<typename T>
void swap2(T& lhs, T& rhs) {
    if constexpr(std::is_pod_v<T>) {
        T tmp;
        std::memcpy(&tmp, &lhs, sizeof(T));
        std::memcpy(&lhs, &rhs, sizeof(T));
        std::memcpy(&rhs, &tmp, sizeof(T));
    } else {
        T tmp(lhs);
        lhs = rhs;
        rhs = tmp;
    }
}

int main() {
    static_assert(std::is_pod_v<PODType> == true);
    static_assert(std::is_pod_v<NonPODType> == false);

    PODType pod_type1 = {5, 5};
    PODType pod_type2 = {7, 7};

    NonPODType non_pod_type1 = {1, 1};
    NonPODType non_pod_type2 = {3, 3};

    // C++14
    print("C++14\n");
    println();
    print(pod_type1);
    print(pod_type2);

    swap1(pod_type1, pod_type2);

    println();
    print(pod_type1);
    print(pod_type2);

    println();
    println();

    print(non_pod_type1);
    print(non_pod_type2);

    swap1(non_pod_type1, non_pod_type2);

    println();
    print(non_pod_type1);
    print(non_pod_type2);

    // C++17
    print("-----\n");
    print("C++17\n");
    println();

    print(pod_type1);
    print(pod_type2);

    swap2(pod_type1, pod_type2);

    println();
    print(pod_type1);
    print(pod_type2);

    println();
    println();

    print(non_pod_type1);
    print(non_pod_type2);

    swap2(non_pod_type1, non_pod_type2);

    println();
    print(non_pod_type1);
    print(non_pod_type2);
}


