/*
 * Copyright 2019 Xilinx, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _TREE_KERNEL_HPP_
#define _TREE_KERNEL_HPP_

#include <hls_stream.h>
#include "xf_fintech/tree_engine.hpp"
#include "xf_fintech/g2_model.hpp"
#include "xf_fintech/trinomial_tree.hpp"
#include "xf_fintech/ornstein_uhlenbeck_process.hpp"
using namespace xf::fintech;

#define N 1000

#ifdef HW_EMU_TEST
#define K 1
#define K2 1
#else
#define K 3
#ifndef U200
#define K2 3
#else
#define K2 1
#endif
#endif

#define DIM 2
#define LEN 128
#define LEN2 65536
#define InitTimeLen 13
#define ExerciseLen 5
#define FloatingLen 10
#define FixedLen 5

typedef double DT;
typedef OrnsteinUhlenbeckProcess<DT> Process;
typedef TrinomialTree<DT, Process, LEN> Tree;
typedef G2Model<DT, Tree, LEN2> Model;

struct ScanInputParam0 {
    DT x0;
    DT nominal;
    DT spread;
    DT initTime[InitTimeLen];
};

struct ScanInputParam1 {
    int index;
    int type;
    DT fixedRate;
    int timestep;
    int initSize;
    DT a;
    DT sigma;
    DT flatRate;
    int exerciseCnt[ExerciseLen];
    int floatingCnt[FloatingLen];
    int fixedCnt[FixedLen];
};

void scanTreeKernels(int len, ScanInputParam0 inputParam0[1], ScanInputParam1 inputParam1[1], DT NPV[N]);

extern "C" void scanTreeKernel1(int len, ScanInputParam0 inputParam0[1], ScanInputParam1 inputParam1[1], DT NPV[N]);
extern "C" void scanTreeKernel2(int len, ScanInputParam0 inputParam0[1], ScanInputParam1 inputParam1[1], DT NPV[N]);
extern "C" void scanTreeKernel3(int len, ScanInputParam0 inputParam0[1], ScanInputParam1 inputParam1[1], DT NPV[N]);
extern "C" void scanTreeKernel4(int len, ScanInputParam0 inputParam0[1], ScanInputParam1 inputParam1[1], DT NPV[N]);

#endif
