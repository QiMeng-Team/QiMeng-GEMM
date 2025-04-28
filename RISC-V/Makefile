# Default platform
PLATFORM ?= C910

# Path to config directory
CONFIG_DIR := config

# Supported platforms
SUPPORTED_PLATFORMS := C910 C920 K1

# Default MKN values
M ?= 1024
N ?= 1024
K ?= 1024

# Default GEMM parameters
DEFAULT_GEMM_P := 8
DEFAULT_GEMM_Q := 16
DEFAULT_GEMM_R := 32

# Check if the platform is supported
ifneq ($(filter $(PLATFORM), $(SUPPORTED_PLATFORMS)),)
    PLATFORM_SUPPORTED = true
else
    PLATFORM_SUPPORTED = false
endif

# Function to extract PQR from the respective config file
define READ_PQR
$(shell awk -v m=$(M) -v n=$(N) -v k=$(K) \
    '$$1 == m && $$2 == n && $$3 == k {print $$5, $$6, $$7}' $(CONFIG_DIR)/$(PLATFORM).conf)
endef

# Conditional inclusion of platform-specific makefile
ifeq ($(PLATFORM_SUPPORTED), true)
    PQR := $(call READ_PQR)
    ifeq ($(strip $(PQR)),)
        GEMM_P := $(DEFAULT_GEMM_P)
        GEMM_Q := $(DEFAULT_GEMM_Q)
        GEMM_R := $(DEFAULT_GEMM_R)
    else
        GEMM_P := $(word 1, $(PQR))
        GEMM_Q := $(word 2, $(PQR))
        GEMM_R := $(word 3, $(PQR))
    endif
    include Makefile.$(PLATFORM)
else
    $(error Unsupported platform $(PLATFORM))
endif

# Main build rule
all:
	@echo "Building for platform $(PLATFORM) with M=$(M), N=$(N), K=$(K)"
	@echo "Using GEMM_P=$(GEMM_P), GEMM_Q=$(GEMM_Q), GEMM_R=$(GEMM_R)"
