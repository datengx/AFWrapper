#ifndef __AFHelper_H_
#define __AFHelper_H_

#include <arrayfire.h>
#include <af/cuda.h>

class AFHelper {
public:
	AFHelper() {

	}
	~AFHelper() {

	}

	template <typename T>
	T Max(T* dev_ptr, size_t size);

	template <typename T>
	T Min(T* dev_ptr, size_t size);

	template <typename T>
	void MemcpyD2H(T* dst, T* src, size_t size);

	template <typename T>
	void MemcpyH2D(T* dst, T* src, size_t size);

	template <typename T>
	void Free(T* src);

private:
	// Internal function AFHelper is not supposed to interface with external af::array directly
	af::array morphopen(const af::array& img, const af::array& mask);

	af::array morpherode(const af::array& img, const af::array& mask);
};

#endif