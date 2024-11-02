// examples/asan0.cc
auto main() -> int
{
    auto* X = new double[400]; // space for 400 doubles reserved on the heap
    // X holds the address of where those 400 doubles are on the heap.
    // For instance, X could be the numeric address 337932100.
    // work with X, e.g.,
    if (X != nullptr) {
        for (int i = 0; i < 400; ++i) {
            X[i] = 0;
        }
    }

    // Done with calculations using X
    delete[] X; // Previously allocated space for 400 doubles is now released
    // X is still 337932100, but the previously allocated 400 doubles at
    // that address on the heap is already gone!

    if (X != nullptr) {
        for (int i = 0; i < 400; ++i) {
            X[i] = 1;
        }
        return X[33] > X[23];
    }
}
