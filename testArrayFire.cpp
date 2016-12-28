/*******************************************************
 * Copyright (c) 2014, ArrayFire
 * All rights reserved.
 *
 * This file is distributed under 3-clause BSD license.
 * The complete license agreement can be obtained at:
 * http://arrayfire.com/licenses/BSD-3-Clause
 ********************************************************/

#include <arrayfire.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "AFHelper.h"

// using namespace af;

af::array threshold(const af::array &in, float thresholdValue)
{
    int channels = in.dims(2);
    af::array ret_val = in.copy();
    if (channels>1)
        ret_val = af::colorSpace(in, AF_GRAY, AF_RGB);
    ret_val = (ret_val<thresholdValue)*0.0f + 1.0f*(ret_val>thresholdValue);
    return ret_val;
}

af::array morphopen(const af::array& img, const af::array& mask)
{
    return dilate(erode(img, mask), mask);
}

af::array morpherode(const af::array& img, const af::array& mask)
{
    return erode(img, mask);
}

int main(int argc, char *argv[])
{
    try {

        af::array input = af::loadImage("/Users/dateng/Developer/CUDA/test_arrayfire/test_0.pgm", false);
        // Select a device and display arrayfire info
        int device = argc > 1 ? atoi(argv[1]) : 0;
        af::setDevice(device);
        af::info();

        printf("Create a matrix of random floats on the GPU\n");
        // af::array A = af::randu(3900,3900, u8);
        // af_print(A);

        AFHelper* af_helper = new AFHelper();
        af::array mask = af::constant(1, 3, 3);

        // af::array A_threshold = threshold(A, 128);
        af::array test_th = threshold(input, 128);
        // af::array A_b8 = A_threshold.as(b8);
        af::array test_b8 = test_th.as(b8);
        af::array out = af::constant(0, 3948, 3948, b8);
        af::array test_b8_open = af::constant(0, 3948, 3948, b8);
        af::timer start1 = af::timer::start();
        
        for (int i = 0; i < 10; i++) {
            test_b8_open = morphopen(test_b8, mask);
            // af::saveImage("/Users/dateng/Developer/CUDA/test_arrayfire/test_0_eroded.pgm", test_b8_open);
            out = regions(test_b8_open, AF_CONNECTIVITY_8);
        }
        printf("elapsed seconds: %g\n", af::timer::stop(start1));

        float* d_out = out.device<float>();
        float out_max = af_helper->Max(d_out, 3948*3948);
        std::cout << "out_max: " << out_max << std::endl;
        // out.unlock();
        // out = out / out_max * 255.0;
        // af::array out_u8 = out.as(u8);
        // out.unlock();
        // float* host_ptr = (float*) malloc(3948*3948*sizeof(float));
        // af_helper->MemcpyD2H(host_ptr, d_out, 3948*3948*sizeof(float));
        // out.unlock();
        // free(host_ptr);
        // af_helper->Free(d_out);
        af::saveImage("/Users/dateng/Developer/CUDA/test_arrayfire/test_0_out.pgm", out);
        out.unlock();
        // for (int i = 0; i < 3948; i++) {
        //     for (int j = 0; j < 3948; j++) std::cout << host_ptr[i*3948+j] << " ";
        //     std::cout << std::endl;
        // }   

        //af_print(A_threshold);
        //af_print(out);

        // Find maximum value in an array
        // af::timer start1 = af::timer::start();
        // float* d_A = A.device<float>(); // automatically locked
        // float max_value = af_helper->Max(d_A, 3900*3900);
        // printf("elapsed seconds: %g\n", af::timer::stop(start1));

        // std::cout << "Max is: " << max_value << std::endl;



        // printf("Element-wise arithmetic\n");
        // array B = sin(A) + 1.5;
        // af_print(B);

        // printf("Negate the first three elements of second column\n");
        // B(seq(0, 2), 1) = B(seq(0, 2), 1) * -1;
        // af_print(B);

        // printf("Fourier transform the result\n");
        // array C = fft(B);
        // af_print(C);

        // printf("Grab last row\n");
        // array c = C.row(end);
        // af_print(c);

        // printf("Scan Test\n");
        // dim4 dims(16, 4, 1, 1);
        // array r = constant(2, dims);
        // af_print(r);

        // printf("Scan\n");
        // array S = af::scan(r, 0, AF_BINARY_MUL);
        // af_print(S);

        // printf("Create 2-by-3 matrix from host data\n");
        // float d[] = { 1, 2, 3, 4, 5, 6 };
        // array D(2, 3, d, afHost);
        // af_print(D);

        // printf("Copy last column onto first\n");
        // D.col(0) = D.col(end);
        // af_print(D);

        // Sort A
        // printf("Sort A and print sorted array and corresponding indices\n");
        // af::array vals, inds;
        // af::sort(vals, inds, A);
        // af_print(vals);
        // af_print(inds);

    } catch (af::exception& e) {

        fprintf(stderr, "%s\n", e.what());
        throw;
    }

    return 0;
}