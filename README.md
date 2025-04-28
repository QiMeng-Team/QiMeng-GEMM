# QiMeng-GEMM: Automatically Generating High-Performance Matrix Multiplication Code by Exploiting Large Language Models
QiMeng-GEMM is an innovative approach to automatically generate high-performance matrix multiplication (GEMM) code using LLMs. This codebase provides a comprehensive solution for efficiently computing matrix multiplications, leveraging the power of LLMs to generate optimized code based on user inputs.

## Quick Start
### CUDA

To test the performance of cuda code, you can run this:

```bash
cd code/CUDA
make
./test [M] [N] [K]
```

The example of usage is in `CUDA/main.cpp`. You can use this to call the GEMM cuda kernel:
```cpp
cuda_gemm(M, N, K, alpha, d_A, d_B, beta, d_C);  
```

### RISC-V
**Configure Cross-Compiler:** 

First, you need to configure the compilation toolchain on the specific hardware platform. Then, modify the variables `CC`, `CFLAGS`, and `LDFLAGS` as shown below to support the subsequent cross - compilation process. The following takes the C910 platform as an example.
```makefile  
CC = /data/sfs/share/toolchain/Xuantie-900-gcc-linux-5.10.4-glibc-x86_64-V2.8.1/bin/riscv64-unknown-linux-gnu-gcc  
CFLAGS = -static -O3 -march=rv64imafdcvxtheadc -I /data/sfs/share/toolchain/lib/c910/openblas_default/include 
LDFLAGS = /data/sfs/share/toolchain/lib/c910/openblas_default/lib/libopenblas_c910v-r0.3.13.dev.a -lpthread  
```  

**Compile Code:**  
```bash  
make PLATFORM=C920 M=1024 N=1024 K=1024 
``` 

In the Makefile, use `PLATFORM` to specify the RISC-V platform, and then select `Makefile.$(PLATFORM)` to compile the code. All generated code will be output to the `build/` directory.  

**Run Code:**  
```bash  
./scripts/check_gemm.sh M=1024 N=1024 K=1024  
```  


## Paper
This paper has beed published on AAAI2025.

Please cite this paper if you use this code.

```
@article{
  title={QiMeng-GEMM: Automatically Generating High-Performance Matrix Multiplication Code by Exploiting Large Language Models}, 
  volume={39}, 
  url={https://ojs.aaai.org/index.php/AAAI/article/view/34461}, 
  DOI={10.1609/aaai.v39i21.34461}, 
  number={21},
  journal={Proceedings of the AAAI Conference on Artificial Intelligence}, 
  author={Zhou, Qirui and Wen, Yuanbo and Chen, Ruizhi and Gao, Ke and Xiong, Weiqiang and Li, Ling and Guo, Qi and Wu, Yanjun and Chen, Yunji}, 
  year={2025}, 
  month={Apr.}, 
  pages={22982-22990}
}
    
```
