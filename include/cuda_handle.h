//
// Created by zarko on 7/31/21.
//

#ifndef OSQP_CUDA_HANDLE_H
#define OSQP_CUDA_HANDLE_H


//#include <cublas_v2.h>
//#include <cusparse_v2.h>

typedef struct {
    void *    cublasHandle;
    void *  cusparseHandle;
    int              *d_index;
} CUDA_Handle_t;

#endif //OSQP_CUDA_HANDLE_H
