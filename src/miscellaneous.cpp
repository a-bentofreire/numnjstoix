// uuid: b7847b3e-c644-42bd-9d5f-4f10c26a070d

// ------------------------------------------------------------------------
// Copyright (c) 2019 Alexandre Bento Freire. All rights reserved.
// Licensed under the MIT License+uuid License. See License.txt for details
// ------------------------------------------------------------------------

// ------------------------------------------------------------------------
//                               Includes
// ------------------------------------------------------------------------

#include "numnjs.h"
#include <cfloat>
#include <cmath>
#include <limits>
#include <node.h>

namespace numnjs {

// ------------------------------------------------------------------------
//                               Aggregate Functions
// ------------------------------------------------------------------------

/* clang-format off */
transfCalc1DblFunc(sqrtFunc, sqrt)
transfCalc1DblFunc(cbrtFunc, cbrt)
transfCalc1DblExpr(squareFunc, v * v)
transfCalc1DblExpr(signFunc, v < 0.0 ? -1.0 : (v > 0.0 ? 1.0 : 0.0))
transfCalc1DblFunc(absFunc, fabs)
binaryCalc1DblExpr(maximumFunc, std::max(v0, v1), false, false)
binaryCalc1DblExpr(minumumFunc, std::min(v0, v1), false, false)
/* clang-format on */

void maxFunc(const v8args &args) {
  aggregate1Handler(args, std::numeric_limits<double>::min(), NULL,
                    [](double v, double acc) { return std::max(v, acc); }, NULL,
                    false, ta_ARRAY_FLOATARRAY_MATRIX);
}

void minFunc(const v8args &args) {
  aggregate1Handler(args, std::numeric_limits<double>::max(), NULL,
                    [](double v, double acc) { return std::min(v, acc); }, NULL,
                    false, ta_ARRAY_FLOATARRAY_MATRIX);
}

// ------------------------------------------------------------------------
//                               Initialize
// ------------------------------------------------------------------------

void initializeMiscellaneous(v8exports exports) {

  NODE_SET_METHOD(exports, "sqrt", sqrtFunc);
  NODE_SET_METHOD(exports, "cbrt", cbrtFunc);
  NODE_SET_METHOD(exports, "square", squareFunc);
  NODE_SET_METHOD(exports, "sign", signFunc);
  NODE_SET_METHOD(exports, "abs", absFunc);
  NODE_SET_METHOD(exports, "maximum", maximumFunc);
  NODE_SET_METHOD(exports, "minimum", minumumFunc);
  NODE_SET_METHOD(exports, "max", maxFunc);
  NODE_SET_METHOD(exports, "min", minFunc);
}

} // namespace numnjs