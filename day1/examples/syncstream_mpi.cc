/* Compilation and running instructions for JUWELS
 *
 * mpicxx -std=c++20 -fopenmp syncstream.cc -o syncstream.out
 * srun --nodes=1 --cpus-per-task=16 ./syncstream.out
 *
 * The above will run it with 16 MPI processes each with 16
 * OpenMP threads. See if the output remains sane!
 *
 */

#include <iostream>
#include <mpi.h>
#include <omp.h>
#include <syncstream>

auto main(int argc, char* argv[]) -> int
{
    int prov, rank, nruns;
    MPI_Init_thread(&argc, &argv, MPI_THREAD_FUNNELED, &prov);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nruns);

#pragma omp parallel for
    for (auto i = 0UL; i < 16UL; ++i) {
        std::osyncstream { std::cout } << "counter = " << i
                                       << " on thread "
                                       << omp_get_thread_num() << " of rank " << rank << "\n";
    }
    MPI_Finalize();
}
