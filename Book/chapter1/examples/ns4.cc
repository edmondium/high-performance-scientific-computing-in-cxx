#include <iostream>

int c = 0; // ::c

namespace MC {
int c = 1; // ::MC::c
namespace math {
    int d = 7;
}
namespace utils {
    int c = 2; // ::MC::utils::c
    namespace math {
        int c = 3; // ::MC::utils::math::c
        // namespace MC {}
        auto incr_by_c(int f) -> int
        {
            // int c = 4; // local variable c, shadows global c
            return f + c; // local c if uncommented or the first symbol by
                // the name c going up the namespace tree
                // starting from ::MC::utils::math

            // return f + ::c;  // Global c, irrespective of what else is defined

            // return f + ::MC::c;  // c defined in the top level MC namespace
            // irrespective of what else is defined

            // return f + ::MC::utils::c;

            // return f + utils::c; // Compiler reasons something like this...
            // This is not a local variable. So, let's try to resolve the name 
            // utils::c, in the current context, i.e., ::MC::utils::math.
            // There is nothing calld ::MC::utils::math::utils, therefore,
            // the name utils::c can not be resolved from the immediate 
            // namespace. Next let's check if it can be resolved with respect
            // to the parent namespace, ::MC::utils. Doesn't work. There is 
            // nothing called ::MC::utils::utils. One level further up then!
            // We are trying relative to ::MC. At this level, there is something 
            // called, utils, i.e., ::MC::utils. Let's look if there is a symbol
            // called c there. There it is!

            // return f + math::d; // This proceeds like the previous case, but fails.
            // As soon as we reach the level ::MC::utils, we find a namespace called 
            // math relative to it.  The search for the first part of the name is over.
            // In the resulting namespace ::MC::utils::math, there is no symbol 
            // called d. If we had continued up the tree until we had a full match, 
            // we would have found the variable d defined in the namespace
            // ::MC::math. But that's not how name lookup works.
            // This therefore results in an error.
        }
    }
}

}

auto main(int argc, char* argv[]) -> int
{
    std::cout << MC::utils::math::incr_by_c(4) << "\n";
}
