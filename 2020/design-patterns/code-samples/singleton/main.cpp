#include <iostream>

class Singleton {
    public:
        static Singleton& get() {
            static Singleton g_instance{"Initial data"};

            return g_instance;
        }

        void print() const {
            std::cout << m_internal_data << "\n";
        }

        void write(std::string data) {
            m_internal_data = std::move(data);
        }

    private:
        Singleton(std::string data) : m_internal_data{std::move(data)} {}

        std::string m_internal_data;
};

int main() {
    const auto& s = Singleton::get();
    s.print();

    Singleton::get().write("Altered data");
    Singleton::get().print();    

    return 0;
}

