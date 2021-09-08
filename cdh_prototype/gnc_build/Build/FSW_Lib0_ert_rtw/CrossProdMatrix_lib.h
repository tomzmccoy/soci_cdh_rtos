/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: CrossProdMatrix_lib.h
 *
 * Code generated for Simulink model 'FSW_Lib0'.
 *
 * Model version                  : 1.337
 * Simulink Coder version         : 9.0 (R2018b) 24-May-2018
 * C/C++ source code generated on : Sat Apr 17 16:27:21 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: NXP->Cortex-M4
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#ifndef RTW_HEADER_CrossProdMatrix_lib_h_
#define RTW_HEADER_CrossProdMatrix_lib_h_
#ifndef FSW_Lib0_COMMON_INCLUDES_
# define FSW_Lib0_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "zero_crossing_types.h"
#include "ecos.h"
#endif                                 /* FSW_Lib0_COMMON_INCLUDES_ */

#include "FSW_Lib0_types.h"

extern void CrossProdMatrix_lib(real_T rtu_vector, real_T rtu_vector_p, real_T
  rtu_vector_j, real_T rty_skew_mat[9]);
extern void CrossProdMatrix_lib_d(const real_T rtu_vector[3], real_T
  rty_skew_mat[9]);

#endif                                 /* RTW_HEADER_CrossProdMatrix_lib_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
