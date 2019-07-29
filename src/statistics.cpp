// uuid: 5cabc9c0-d1ce-4c2c-a4ea-b9728ae43008

// ------------------------------------------------------------------------
// Copyright (c) 2019 Alexandre Bento Freire. All rights reserved.
// Licensed under the MIT License+uuid License. See License.txt for details
// ------------------------------------------------------------------------

// ------------------------------------------------------------------------
//                               Includes
// ------------------------------------------------------------------------

#include "numnjs.h"
#include <algorithm>
#include <cfloat>
#include <cmath>
#include <limits>
#include <node.h>
#include <vector>

namespace numnjs {

// ------------------------------------------------------------------------
//                               Actual Functions
// ------------------------------------------------------------------------

/**
 * Calculates the average.
 */
void averageFunc(const v8args &args) {
  aggregate1Handler(args, 0, NULL, [](double v, double acc) { return v + acc; },
                    [](size_t validLen, double acc, njsarray &values,
                       aggregateParams &params) { return acc / validLen; },
                    false, ta_ARRAY_FLOATARRAY);
}

/**
 * Internal function to calculate the variance.
 */
double calcVarFunc(size_t validLen, double acc, njsarray &values,
                   aggregateParams &params) {
  const auto avg = acc / validLen;
  double t = 0;
  for (size_t i = 0; i < validLen; i++) {
    double d = (values[i] - avg);
    t += d * d;
  }
  return t / validLen;
}

/**
 * Calculates the variance.
 */
void varFunc(const v8args &args) {
  aggregate1Handler(args, 0, NULL, [](double v, double acc) { return v + acc; },
                    calcVarFunc, true, ta_ARRAY_FLOATARRAY);
}

/**
 * Calculates the standard deviation.
 */
void stdFunc(const v8args &args) {
  aggregate1Handler(args, 0, NULL, [](double v, double acc) { return v + acc; },
                    [](size_t validLen, double acc, njsarray &values,
                       aggregateParams &params) {
                      return sqrt(calcVarFunc(validLen, acc, values, params));
                    },
                    true, ta_ARRAY_FLOATARRAY);
}

/**
 * Calculates the skewness.
 */
void skewFunc(const v8args &args) {
  aggregate1Handler(args, 0, NULL, [](double v, double acc) { return v + acc; },
                    [](size_t validLen, double acc, njsarray &values,
                       aggregateParams &params) {
                      const auto avg = acc / validLen;
                      double varAcc = 0;
                      double skewAcc = 0;
                      for (size_t i = 0; i < validLen; i++) {
                        double d = (values[i] - avg);
                        varAcc += d * d;
                        skewAcc += d * d * d;
                      }
                      const double var = varAcc / validLen;
                      const double std_pwr3 = pow(var, 1.5);
                      return (skewAcc / validLen) / std_pwr3;
                    },
                    true, ta_ARRAY_FLOATARRAY);
}

/**
 * Calculates the kurtosis function.
 */
void kurtosisFunc(const v8args &args) {
  aggregate1Handler(args, 0,

                    [](aggregateParams &params) {
                      /* checks if it's Fisher or Pearson */
                      params.maxParams = 2;
                      params.boolValue1 = false;
                      if (params.argsLen == 2) {
                        if (!getBoolInput(params.isolate, *params.args, 1,
                                          params.boolValue1, true)) {
                          return false;
                        }
                      }
                      return true;
                    },

                    [](double v, double acc) { return v + acc; },

                    [](size_t validLen, double acc, njsarray &values,
                       aggregateParams &params) {
                      const auto avg = acc / validLen;
                      double varAcc = 0;
                      double kurtAcc = 0;
                      for (size_t i = 0; i < validLen; i++) {
                        double d = (values[i] - avg);
                        double d_pwr2 = d * d;
                        varAcc += d_pwr2;
                        kurtAcc += d_pwr2 * d_pwr2;
                      }
                      const double var = varAcc / validLen;
                      const double std_pwr4 = var * var;
                      const double resValue = (kurtAcc / validLen) / std_pwr4;
                      return resValue + (params.boolValue1 ? -3 : 0);
                    },

                    true, ta_ARRAY_FLOATARRAY);
}

/**
 * Calculates the covariance function.
 */
void covFunc(const v8args &args) {

  NSJAllow_Type allowTypes[] = {ta_ARRAY_FLOATARRAY, ta_ARRAY_FLOATARRAY};

  nInputsHandler(args, 2, 0, allowTypes, [](NArrayInputs &naInputs) {
    size_t elCount = naInputs.inputs[0].elCount;
    njsarray &values0 = naInputs.valuesList[0];
    njsarray &values1 = naInputs.valuesList[1];
    size_t validLen = naInputs.validLenList[0];
    if (validLen != naInputs.validLenList[1]) {
      returnInputMustSameLen(naInputs.isolate);
      return false;
    }
    // compute averages
    double avg0 = 0;
    double avg1 = 0;
    for (size_t i = 0; i < elCount; i++) {
      double v0 = values0[i];
      bool isValid = isValidValue(v0);
      avg0 += isValid ? v0 : 0;
      double v1 = values1[i];
      avg1 += isValid ? v1 : 0;
    }

    avg0 /= validLen;
    avg1 /= validLen;
    double cov = 0;
    for (size_t i = 0; i < elCount; i++) {
      double v0 = values0[i];
      double v1 = values1[i];
      bool isValid = isValidValue(v0);
      cov += isValid ? (v0 - avg0) * (v1 - avg1) : 0;
    }
    naInputs.returnAsNumber(cov / (validLen - 1));
    return true;
  });
}

// ------------------------------------------------------------------------
//                               Initialize
// ------------------------------------------------------------------------

void initializeStatistics(v8exports exports) {

  NODE_SET_METHOD(exports, "average", averageFunc);
  NODE_SET_METHOD(exports, "var", varFunc);
  NODE_SET_METHOD(exports, "std", stdFunc);
  NODE_SET_METHOD(exports, "skew", skewFunc);
  NODE_SET_METHOD(exports, "kurtosis", kurtosisFunc);
  NODE_SET_METHOD(exports, "cov", covFunc);
}

} // namespace numnjs