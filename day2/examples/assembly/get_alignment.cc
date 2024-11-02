auto get_alignment(void * var) {
    auto n = reinterpret_cast<unsigned long>(var);
    return (-n) & n;
}

