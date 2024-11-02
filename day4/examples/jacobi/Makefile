NVCC=nvc++
NVCC_FLAGS=-std=c++17 -O3 -stdpar

.PHONY: all

all: jacobi_cxx17

jacobi_cxx17: jacobi_cxx17.cc Makefile
	$(NVCC) $(CFLAGS) $(NVCC_FLAGS) $< $(LIBS) -o $@


.PHONY: clean

clean:
	rm -f jacobi_cxx17


