#include "AFHelper.h"


template <typename T>
T AFHelper::Max(T* dev_ptr, size_t size) {
	af::array af_dp(size, dev_ptr, afDevice);
	// af now manage the memory, remember to call lock() after
	T tmp_max;
	unsigned idx;
	af::max(&tmp_max, &idx, af_dp);
	af_dp.lock(); // lock af's mem control

	return tmp_max;
}
template float AFHelper::Max(float* dev_ptr, size_t size);

template <typename T>
T AFHelper::Min(T* dev_ptr, size_t size) {
	af::array af_dp(size, dev_ptr, afDevice);
	// af now manage the memory, remember to call lock() after
	T tmp_max;
	unsigned idx;
	af::min(&tmp_max, &idx, af_dp);
	af_dp.lock(); // lock af's mem control

	return tmp_max;
}
template float AFHelper::Min(float* dev_ptr, size_t size);

template <typename T>
void AFHelper::MemcpyD2H(T* dst, T* src, size_t size) {
	if (dst && src) {
		cudaMemcpy(dst, src, size, cudaMemcpyDeviceToHost);
	} else {
		std::cerr << "Null pointer err!" << std::endl;
	}
}
template void AFHelper::MemcpyD2H(float* dst, float* src, size_t size);

template <typename T>
void AFHelper::MemcpyH2D(T* dst, T* src, size_t size) {
	if (dst && src) {
		cudaMemcpy(dst, src, size, cudaMemcpyHostToDevice);
	} else {
		std::cerr << "Null pointer err!" << std::endl;
	}
}
template void AFHelper::MemcpyH2D(float* dst, float* src, size_t size);

template <typename T>
void AFHelper::Free(T* src) {
	cudaFree(src);
}
template void AFHelper::Free(float* src);

af::array AFHelper::morphopen(const af::array& img, const af::array& mask)
{
    return dilate(erode(img, mask), mask);
}

af::array AFHelper::morpherode(const af::array& img, const af::array& mask)
{
    return erode(img, mask);
}