template<typename T>
struct type_is {
    using type = T;
};

int main() {
    type_is<int>::type x = 5;
}