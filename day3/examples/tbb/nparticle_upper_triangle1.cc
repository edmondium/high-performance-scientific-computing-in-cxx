#include <cassert>
#include <chrono>
#include <iostream>
#include <random>
#include <tbb/enumerable_thread_specific.h>
#include <tbb/task_scheduler_init.h>
#include <tbb/tbb.h>
#include <vector>

constexpr const size_t N = 50000;
std::vector<double> q(N, 0.1), x(N, 0.0), y(N, 0.0), z(N, 0.0);
tbb::enumerable_thread_specific<double> E;

constexpr inline double sqr(double x) { return x * x; }

double e_rect_ser(size_t i0, size_t i1, size_t j0, size_t j1)
{
    //std::cout << "e_rect_ser : "<<i0<<", "<<i1<<", "<<j0<<", "<<j1<<"\n";
    //assert(i0<=N&&i1<=N&&j0<=N&&j1<=N&&(i0<=i1)&&(j0<=j1)&&(i1-i0)<=N && (j1-j0)<=N);
    double etmp = 0;
    for (size_t i = i0; i < i1; ++i) {
        for (size_t j = j0; j < j1; ++j) {
            double r2 = sqr(x[i] - x[j]) + sqr(y[i] - y[j]) + sqr(z[i] - z[j]);
            etmp += q[i] * q[j] / sqrt(r2);
        }
    }
    return etmp;
}

void e_rect_par(size_t i0, size_t i1, size_t j0, size_t j1)
{
    tbb::blocked_range2d<size_t> r { i0, i1, j0, j1 };
    tbb::parallel_for(r, [&](tbb::blocked_range2d<size_t> r) {
        auto& eloc = E.local();
        eloc += e_rect_ser(r.rows().begin(), r.rows().end(), r.cols().begin(), r.cols().end());
    });
}

double e_tri_ser(size_t i0, size_t i1)
{
    //std::cout << "e_tri_ser : "<<i0<<", "<<i1<<"\n";
    //assert(i0<=N&&i1<=N&&i0<=i1&&(i1-i0)<=N);
    double etmp = 0;
    for (size_t i = i0; i < i1; ++i) {
        for (size_t j = i0; j < i1; ++j) {
            if (j > i) {
                double r2 = sqr(x[i] - x[j]) + sqr(y[i] - y[j]) + sqr(z[i] - z[j]);
                etmp += q[i] * q[j] / sqrt(r2);
            }
        }
    }
    return etmp;
}

void e_tri_par(size_t i0, size_t i1)
{
    size_t trisz = (i1 - i0);
    if (trisz < 16) {
        auto& eloc = E.local();
        eloc += e_tri_ser(i0, i1);
    } else {
        size_t nexttrisz = ((trisz + 1) / 2);
        auto tril = [=] { e_tri_par(i0, i0 + nexttrisz); };
        auto trir = [=] { e_tri_par(i1 - nexttrisz, i1); };
        auto rct = [=] { e_rect_par(i0, i0 + trisz / 2, i1 - trisz / 2, i1); };
        tbb::parallel_invoke(rct, tril, trir);
    }
}

double e_par()
{
    double Eglob = 0;
    e_tri_par(0, N);
    for (auto& v : E) {
        Eglob += v;
        v = 0;
    }
    return Eglob;
}

int main(int argc, char* argv[])
{
    auto nthr = tbb::task_scheduler_init::default_num_threads();
    if (argc > 1)
        nthr = std::stoul(argv[1]);
    tbb::task_arena executor;
    executor.initialize(nthr);
    auto gen = [
                   engine = std::mt19937_64{std::random_device{}()},
                   dist = std::uniform_real_distribution<> { -5, 5 }
               ]() mutable { return dist(engine); };
    std::cout << "Filling up coordinate arrays with random numbers serially\n";
    auto t0 = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < N; ++i) {
        x[i] = gen();
        y[i] = gen();
        z[i] = gen();
    }
    auto t1 = std::chrono::high_resolution_clock::now();
    std::cout << "Filling arrays took : " << std::chrono::duration<double>(t1 - t0).count() << " seconds\n";
    std::cout << "Serial energy evaluation ...\n";
    t0 = std::chrono::high_resolution_clock::now();
    double eser = e_tri_ser(0, N);
    t1 = std::chrono::high_resolution_clock::now();
    auto tser = std::chrono::duration<double>(t1 - t0).count();
    std::cout << "Serial energy evaluation took : " << tser << " seconds\n";
    std::cout << "Parallel energy evaluation ...\n";
    t0 = std::chrono::high_resolution_clock::now();
    double epar = executor.execute([&]{ return e_par(); });
    t1 = std::chrono::high_resolution_clock::now();
    auto tpar = std::chrono::duration<double>(t1 - t0).count();
    std::cout << "Parallel energy evaluation took : " << tpar << " seconds\n";
    std::cout << "Total error = " << fabs(eser - epar) << '\n';
    std::cout << "Speed up in TBB version relative to serial version = " << 100 * tser / tpar << std::endl;
}
