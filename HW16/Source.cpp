#include <iostream>
#include <memory>
#include <utility>

template<typename T>
class shared_ptr {
private:
    T* ptr;
    size_t* ref_count;

    void release() {
        if (ref_count) {
            --(*ref_count);
            if (*ref_count == 0) {
                delete ptr;
                delete ref_count;
            }
        }
        ptr = nullptr;
        ref_count = nullptr;
    }

    void add_ref() {
        if (ref_count) {
            ++(*ref_count);
        }
    }

public:
    explicit shared_ptr(T* p = nullptr) : ptr(p), ref_count(nullptr) {
        if (p) {
            ref_count = new size_t(1);
        }
    }

    shared_ptr(const shared_ptr& other) : ptr(other.ptr), ref_count(other.ref_count) {
        add_ref();
    }

    shared_ptr& operator=(const shared_ptr& other) {
        if (this != &other) {
            release();
            ptr = other.ptr;
            ref_count = other.ref_count;
            add_ref();
        }
        return *this;
    }

    shared_ptr(shared_ptr&& other) noexcept : ptr(other.ptr), ref_count(other.ref_count) {
        other.ptr = nullptr;
        other.ref_count = nullptr;
    }

    shared_ptr& operator=(shared_ptr&& other) noexcept {
        if (this != &other) {
            release();
            ptr = other.ptr;
            ref_count = other.ref_count;
            other.ptr = nullptr;
            other.ref_count = nullptr;
        }
        return *this;
    }

    ~shared_ptr() {
        release();
    }

    T& operator*() const { return *ptr; }
    T* operator->() const { return ptr; }
    T* get() const { return ptr; }

    size_t use_count() const {
        return ref_count ? *ref_count : 0;
    }

    bool unique() const {
        return use_count() == 1;
    }

    explicit operator bool() const {
        return ptr != nullptr;
    }

    void reset(T* p = nullptr) {
        shared_ptr<T>(p).swap(*this);
    }

    void swap(shared_ptr& other) noexcept {
        T* temp_ptr = ptr;
        size_t* temp_count = ref_count;
        ptr = other.ptr;
        ref_count = other.ref_count;
        other.ptr = temp_ptr;
        other.ref_count = temp_count;
    }
};

template<typename T, typename... Args>
shared_ptr<T> make_shared(Args... args) {
    return shared_ptr<T>(new T(args...));
}

int main() {
    shared_ptr<int> p1 = make_shared<int>(100);
    cout << "p1: " << *p1 << ", count: " << p1.use_count() << '\n';

    {
        shared_ptr<int> p2 = p1;
        cout << "p2 створено, count: " << p1.use_count() << '\n';

        shared_ptr<int> p3;
        p3 = p2;
        cout << "p3 присвоєно, count: " << p1.use_count() << '\n';
    }

    cout << "Після блоку, count: " << p1.use_count() << '\n';
    cout << "p1: " << *p1 << '\n';

    p1.reset();
    cout << "Після reset, count: " << p1.use_count() << '\n';

    return 0;
}
