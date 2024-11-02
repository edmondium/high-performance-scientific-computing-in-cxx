NVCC=nvc++
NVCC_FLAGS=-O3 -stdpar -gpu=cc70

.PHONY: all

all: jacobi

jacobi: jacobi.cc
	$(NVCC) $(CFLAGS) $(NVCC_FLAGS) -std=c++17 $< $(LIBS) -o $@


.PHONY: clean

clean:
	rm -f jacobi


