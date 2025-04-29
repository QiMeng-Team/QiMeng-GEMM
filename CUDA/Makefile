NVCC = nvcc

TARGET = test

SRCS = $(wildcard *.cu) $(wildcard *.cpp)

NVCC_FLAGS = -lcublas -arch=sm_80 # default arch is sm_80, change on your specific GPU arch

all: $(TARGET)

$(TARGET): $(SRCS)
	$(NVCC) $(SRCS) -o $(TARGET) $(NVCC_FLAGS)

clean:
	rm -f $(TARGET)
