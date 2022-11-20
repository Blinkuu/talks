#include <cstddef>
#include <algorithm>
#include <array>
#include <iostream>
#include <cstring>

namespace bnk {
    template<typename T>
    class ConstexprNewAllocator {
        public:
            using value_type = T;
            using pointer = T*;
            using const_pointer = const T*;
            using size_type = std::size_t;
        public:
            [[nodiscard]] constexpr pointer allocate(size_type n) {
                return new value_type[n]{};
            }
            constexpr void deallocate(pointer p, size_type n) {
                delete[] p;
            }
    };

    template<class T, class Allocator = ConstexprNewAllocator<T>>
    class vector {
        public:
        using value_type = T;
        using allocator_type = Allocator;
        using size_type = std::size_t;
        using difference_type = std::ptrdiff_t;
        using reference = value_type&;
        using const_reference = const value_type&;
        using pointer = Allocator::pointer;
        using const_pointer = Allocator::const_pointer;

        public:
        // ctors/dtor
        constexpr vector() : 
            m_allocator{},
            m_data{nullptr},
            m_size{0},
            m_capacity{0}
            {}

        constexpr vector(const size_type size) : 
            m_allocator{},
            m_data{m_allocator.allocate(size)},
            m_size{size},
            m_capacity{size}
            {}

        constexpr vector(const vector& rhs) {
           m_size = rhs.m_size;
           m_capacity = rhs.m_capacity;
           m_data = m_allocator.allocate(m_size);
           std::copy(rhs.begin(), rhs.end(), begin());
        }

        constexpr vector(vector&& rhs) noexcept
            : m_data(std::exchange(rhs.m_data, nullptr)),
              m_size(std::move(rhs.m_size)),
              m_capacity(std::move(rhs.m_capacity))
        {
            rhs.m_size = 0;
            rhs.m_capacity = 0;
        }

        constexpr ~vector() {
             m_allocator.deallocate(m_data, m_size);
        }

        // element access
        [[nodiscard]] constexpr reference operator[](const std::size_t index) noexcept { return m_data[index]; }
        [[nodiscard]] constexpr const_reference operator[](const std::size_t index) const noexcept { return m_data[index]; }
       
        [[nodiscard]] constexpr reference front() noexcept { return *begin(); } 
        [[nodiscard]] constexpr const_reference front() const noexcept { return *begin(); }
        
        [[nodiscard]] constexpr reference back() noexcept { return *end(); }
        [[nodiscard]] constexpr const_reference back() const noexcept { return *end(); }

        [[nodiscard]] constexpr pointer data() noexcept { return m_data; }
        [[nodiscard]] constexpr const_pointer data() const noexcept { return m_data; }

        // modifiers
        constexpr void clear() noexcept {
            m_size ^= m_size;
        }

        constexpr void push_back(const T& value) {
           if(m_size < m_capacity) {
                m_data[m_size++] = T(value);
           } else {
                resize(2 * m_size + 1);
                m_data[m_size++] = T(value);
           }
        }

        constexpr void push_back(T&& value) {
           if(m_size < m_capacity) {
                m_data[m_size++] = T(std::move(value));
           } else {
                resize(2 * m_size + 1);
                m_data[m_size++] = T(std::move(value));
           }
        }

        template<class ... Args>
        constexpr void emplace_back(Args&& ... args) {
           if(m_size < m_capacity) {
                m_data[m_size++] = T(std::forward<Args>(args) ...);
           } else {
               resize(2 * m_size);
                m_data[m_size++] = T(std::forward<Args>(args) ...);
           }
        }

        constexpr void pop_back() {
           --m_size; 
        }

        constexpr void resize(const size_type new_size) {
            m_capacity = new_size;
            pointer tmp = m_allocator.allocate(new_size);
            
            std::copy(begin(), end(), tmp);

            delete[] m_data;
            m_data = tmp; 
        }

        // operators
        constexpr reference operator=(const vector& rhs) {
            if(this != &rhs) {
                if(m_size != rhs.m_size) {
                    delete[] m_data;
                    m_size = 0;
                    m_data = nullptr;
                    m_data = new T[rhs.m_size];
                    m_size = rhs.m_size; 
                }
                std::copy(rhs.begin(), rhs.end(), begin());
            }

            return *this;
        }

        constexpr reference operator=(vector&& rhs) noexcept {
            if(this != &rhs) {
                delete[] m_data;
                
                m_data = std::exchange(rhs.m_data, nullptr);
                m_size = std::move(rhs.m_size);
                m_capacity = std::move(rhs.m_capacity);

                rhs.m_size = 0;
                rhs.m_capacity = 0;
            }

            return *this;
        }

        // capacity
        [[nodiscard]] constexpr size_type empty() const noexcept { return !m_size; }
        [[nodiscard]] constexpr size_type size() const noexcept { return m_size; }

        //range
        [[nodiscard]] constexpr pointer begin() noexcept { return m_data; }
        [[nodiscard]] constexpr const_pointer begin() const noexcept { return m_data; }
        [[nodiscard]] constexpr pointer end() noexcept { return m_data + m_size; }
        [[nodiscard]] constexpr const_pointer end() const noexcept { return m_data + m_size; }

    private:
        Allocator m_allocator;
        pointer m_data = nullptr;
        size_type m_size = 0;
        size_type m_capacity = 1;
    };
}

constexpr auto eval() noexcept {
    bnk::vector<double> v1;

    constexpr auto quadratic = [](const double x) { return x * x; };
    for(std::size_t i = 0; i < 10; i++) {
        v1.push_back(quadratic(i));
    }
    
    v1.pop_back();

    bnk::vector<double> v2 = std::move(v1);

    std::array<double, 10> result{};
    std::copy(v2.begin(), v2.end(), result.begin());
    return result;
}

int main() {
    /*
    This is a toy implementation of std::vector that fully works at compile time.
    It's sole purpose is to show that you can now easily implement containers that work at compile time.
    It lacks certain features.
    It was tested on: g++ (Compiler-Explorer-Build) 10.0.0 20191008 (experimental).
    */
    constexpr auto const_result = eval();

    for(std::size_t i = 0; i < const_result.size(); i++) {
        std::cout << const_result[i] << " \n";
    }

    // bnk::vector<int> vec(2);
    // for(std::size_t i = 1; i <= 5; i+=2) {
    //     vec.emplace_back(i);
    //     vec.emplace_back(i + 1);
    // }

    // std::transform(vec.begin(), vec.end(), vec.begin(),[](auto x) { return x * x; });
    // std::for_each(vec.begin(), vec.end(),[](const auto& x) { std::cout << x << " "; });
 

    return const_result[1];
}




