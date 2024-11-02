#pragma once

#include <iomanip>
#include <iostream>
#include <string>

class Vbose {
public:
    Vbose()
    {
        std::cout << "Default constructor of object at " << ((size_t)this) << "\n";
    }
    inline auto getval() const { return nm; }
    inline void setval(const std::string& nw) { nm = nw; }

    Vbose(const Vbose& v)
        : nm(v.nm)
    {
        std::cout << "Copy constructor of object at " << ((size_t)this) << ". ";
        std::cout << "Source for copy is at " << ((size_t)&v) << "\n";
    }
    Vbose(Vbose&& v) noexcept
        : nm(std::move(v.nm))
    {
        std::cout << "Move constructor of object at " << ((size_t)this) << ". ";
        std::cout << "Source for move is at " << ((size_t)&v) << "\n";
    }

    Vbose(std::string gs) noexcept
        : nm(gs)
    {
        std::cout << "Constructor of object at " << ((size_t)this) << ",";
        std::cout << " using string " << std::quoted(gs) << "\n";
    }

    auto operator=(const Vbose& v) -> Vbose&
    {
        std::cout << "Assignment operator: LHS @ " << ((size_t)this) << "(" << nm << "), ";
        std::cout << "RHS @ " << ((size_t)&v) << "(" << std::quoted(v.nm) << ")\n";
        if (this != &v) {
            nm = v.nm;
        }
        return *this;
    }

    auto operator=(Vbose&& v) -> Vbose&
    {
        std::cout << "Move assignment operator: LHS @ " << ((size_t)this) << "(" << std::quoted(nm) << "), ";
        std::cout << "RHS @ " << ((size_t)&v) << "(" << std::quoted(v.nm) << ")\n";
        std::swap(nm, v.nm);
        return *this;
    }

    ~Vbose()
    {
        std::cout << "Destructor of object at " << ((size_t)this) << " with data " << std::quoted(nm) << "\n";
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
	std::cout << "Changing internal value of object at " << ((size_t)this) << " from " << nm << " to " << vl << "\n";
	nm = vl;
    }

private:
    std::string nm { "Uninitialized" };
};
