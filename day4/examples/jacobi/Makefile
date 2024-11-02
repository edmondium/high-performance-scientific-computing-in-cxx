NVCC=nvc++
NVCC_FLAGS=-O3 -stdpar -gpu=cc70

.PHONY: all

all: jacobi_cxx17 jacobi_cxx20

jacobi_cxx17: jacobi_cxx17.cc
	$(NVCC) $(CFLAGS) $(NVCC_FLAGS) -std=c++17 $< $(LIBS) -o $@
jacobi_cxx20: jacobi_cxx20.cc
	$(NVCC) $(CFLAGS) $(NVCC_FLAGS) -std=c++20 $< $(LIBS) -o $@


.PHONY: clean

clean:
	rm -f jacobi_cxx17 jacobi_cxx20


