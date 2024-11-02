#pragma once

#include <iomanip>
#include <iostream>
#include <string>

class Vbose {
public:
    Vbose()
    {
        std::cout << "Default construct @" << ((size_t)this) << "\n";
    }
    inline auto getval() const { return nm; }
    inline void setval(const std::string& nw) { nm = nw; }

    Vbose(const Vbose& v)
        : nm(v.nm)
    {
        std::cout << "Copy construct @" << ((size_t)this) << " from @" << ((size_t)&v) << "\n";
    }
    Vbose(Vbose&& v) noexcept
        : nm(std::move(v.nm))
    {
        std::cout << "Move construct @" << ((size_t)this) << " from @" << ((size_t)&v) << "\n";
    }

    Vbose(std::string gs) noexcept
        : nm(gs)
    {
        std::cout << "Construct @" << ((size_t)this) << ", using string " << std::quoted(gs) << "\n";
    }

    auto operator=(const Vbose& v) -> Vbose&
    {
        std::cout << "Assign to @ " << ((size_t)this) << "(" << nm << "), "
                  << " from @" << ((size_t)&v) << "(" << std::quoted(v.nm) << ")\n";
        if (this != &v) {
            nm = v.nm;
        }
        return *this;
    }

    auto operator=(Vbose&& v) -> Vbose&
    {
        std::cout << "Move assign to @" << ((size_t)this) << "(" << std::quoted(nm) << "), "
                  << " from @" << ((size_t)&v) << "(" << std::quoted(v.nm) << ")\n";
        std::swap(nm, v.nm);
        return *this;
    }

    ~Vbose()
    {
        std::cout << "Destruct @" << ((size_t)this) << " with data " << std::quoted(nm) << "\n";
    }

    auto operator+(const Vbose& v) -> Vbose
    {
        std::cout << "Inside operator + ()\n";
        return {nm + "+" + v.nm};
    }
    auto value() const noexcept -> std::string
    {
	return nm;
    }
    void value(const std::string& vl)
    {
	std::cout << "Changing value of object @" << ((size_t)this) << " from " << nm << " to " << vl << "\n";
	nm = vl;
    }

private:
    std::string nm { "Uninitialized" };
};
