# QiMeng-GEMM-Code: A High-Performance GEMM Library Generated by LLMs 
In the context of continuous evolution of complex instruction set architectures (ISA) and hardware platforms, developing high-performance matrix multiplication (GEMM) code incurs significant human and time costs. This code library provides high-performance GEMM code generated by large models such as DeepSeek-R1, GPT-4o, and Claude 3.7 for mainstream CPU architectures like RISC-V and ARM.  

**Core Features:**  
- **Hardware Platform Coverage:** Customized implementations for various RISC-V hardware platforms.  
- **Lightweight Design:** Each dimension implements GEMM operations independently, maintaining a concise and maintainable codebase.  
- **Education-Friendly:** Demonstrates the full GEMM optimization stack through modular code structures.  

This library not only significantly reduces high-performance computing development costs but also provides a rapid validation platform for matrix operation optimization research.  

**Note:** This is not a full linear algebra library—it solely performs general matrix multiplication ("GEMM").  


## Quick Start  
**Configure Cross-Compiler:** 

First, you need to configure the compilation toolchain on the specific hardware platform. Then, modify the variables `CC`, `CFLAGS`, and `LDFLAGS` as shown below to support the subsequent cross-compilation process. The following takes the C910 platform as an example.
```makefile  
export CC = /data/sfs/share/toolchain/Xuantie-900-gcc-linux-5.10.4-glibc-x86_64-V2.8.1/bin/riscv64-unknown-linux-gnu-gcc  
export CFLAGS = -static -O3 -march=rv64imafdcvxtheadc -I /data/sfs/share/toolchain/lib/c910/openblas_default/include 
export LDFLAGS = /data/sfs/share/toolchain/lib/c910/openblas_default/lib/libopenblas_c910v-r0.3.13.dev.a -lpthread  
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


## Target Platforms/Architectures  
Currently open-sourced for RISC-V platforms including C910, C920 and K1.  
Future plans include releasing GEMM code generated by LLMs for additional hardware platforms.  


## Code Directory Structure  
- **build/:** Contains compiled libraries and executables.  
- **config/:** Hardware-specific configuration files.  
- **driver/:** Driver-layer code for different dimensions of GEMM generated by large models.  
- **kernel/:** Kernel-layer assembly code derived from OpenBLAS.  
- **scripts/:** Helper scripts for project generation.   
- **main.c:** Entry point of the codebase.  


## Performance Comparison  
*(Coming soon)*  


## Contact Us  
For GEMM code of other dimensions, email: <ruizhi@iscas.ac.cn>.  

