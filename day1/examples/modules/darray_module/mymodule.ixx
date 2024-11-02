export module mymodule;
import <initializer_list>;
import <iostream>;
import <memory>;

export template <class T>
class darray {
private:
    // swap function
    void swap(darray& oth)
    {
        std::swap(arr, oth.arr);
        std::swap(sz, oth.sz);
    }
    std::unique_ptr<T[]> arr;
    size_t sz = 0;

public:
    // read-only access for array elements
    auto operator[](size_t i) const -> T { return arr[i]; }
    // read-write access for array elements
    auto operator[](size_t i) -> T& { return arr[i]; }

    // This is needed if you want to use range based for loops on your class
    auto begin() const -> T* { return arr; }
    // This is needed if you want to use range based for loops on your class
    auto end() const -> T* { return arr + size(); }

    // returns the size
    auto size() const -> decltype(sz) { return sz; }

    // Sums up array and returns the result
    auto sum() const -> T
    {
        T a {};
        for (auto el : (*this)) {
            a += el;
        } // Use the range based for loop. //Well, why not!
        return a;
    }

    // Default constructor, also defaulted.
    darray() = default;
    // Destructor. With storage managed by a unique_ptr, we don't need to delete it.
    ~darray() = default;

    // Constructor with a given size
    darray(size_t N)
    {
        if (N != 0) {
            arr = std::make_unique<T[]>(N);
            sz = N;
        }
    }

    // Copy constructor
    darray(const darray<T>& oth)
    {
        if (oth.sz != 0) {
            sz = oth.sz;
            arr = std::make_unique<T[]>(sz);
        }
        for (size_t i = 0; i < sz; ++i)
            arr[i] = oth.arr[i];
    }
    darray(darray<T>&& oth) noexcept 
    {
         swap(oth);
    }
    // Initialiser list constructor
    darray(std::initializer_list<T> l)
    {
        arr = std::make_unique<T[]>(l.size());
        sz = l.size();
        size_t i = 0;
        for (auto el : l)
            arr[i++] = el;
    }
    // Assignment operator using the copy and swap idiom
    auto operator=(darray d) -> darray&
    {
        swap(d);
        return *this;
    }
};

// Output operator. No need to make it a friend, since we can use only
// public functions of the class to do all the work!
export template <typename T>
auto operator<<(std::ostream& os, const darray<T>& d) -> std::ostream&
{
    os << '[';
    for (size_t i = 0; i < d.size(); ++i) {
        os << d[i];
        if (i != (d.size() - 1))
            os << ',';
    }
    os << ']';
    return os; // This function returns os so that you can write cout << d1 << " other things\n";
    // That is interpreted as (cout << d1) << " other things\n";
}

