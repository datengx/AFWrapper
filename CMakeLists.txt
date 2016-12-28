CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(Hello-Arrayfire)

# FIND_PACKAGE(ArrayFire)
set(arrayfire_root /Users/dateng/Developer/arrayfire)
set(arrayfire_libraries af)

# Additional cmake module, tell cmake to use them
LIST(APPEND CMAKE_MODULE_PATH ${arrayfire_root}/CMakeModules)

# INCLUDE_DIRECTORIES(${ArrayFire_INCLUDE_DIRS})
# message(STATUS ${ArrayFire_INCLUDE_DIRS})
# message(STATUS ${ArrayFire_LIBRARIES})
include_directories(${arrayfire_root}/include)
link_directories(${arrayfire_root}/lib)

# Or if you intend to use CUDA, you need it as well as NVVM:
FIND_PACKAGE(CUDA REQUIRED)
set(CUDA_NVCC_FLAGS "${CUDA_NVCC_FLAGS} -arch=sm_21 -O3 --use_fast_math")
FIND_PACKAGE(NVVM) # this FIND script can be found in the ArrayFire CMake example repository
SET(EXTRA_LIBS ${CMAKE_THREAD_LIBS_INIT} ${CUDA_LIBRARIES} ${NVVM_LIB})

cuda_add_library(
	AFLib
	AFHelper.h
	AFHelper.cpp
)

ADD_EXECUTABLE(testArrayFire testArrayFire.cpp)
TARGET_LINK_LIBRARIES(testArrayFire AFLib ${arrayfire_libraries} ${EXTRA_LIBS})