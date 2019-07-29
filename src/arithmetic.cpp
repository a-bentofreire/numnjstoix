// uuid: e1f249c1-93a2-4840-a807-0bd8720f0623

// ------------------------------------------------------------------------
// Copyright (c) 2019 Alexandre Bento Freire. All rights reserved.
// Licensed under the MIT License+uuid License. See License.txt for details
// ------------------------------------------------------------------------

// ------------------------------------------------------------------------
//                               Includes
// ------------------------------------------------------------------------

#include "numnjs.h"
#include <math.h>
#include <node.h>

namespace numnjs {

// ------------------------------------------------------------------------
//                               Actual Functions
// ------------------------------------------------------------------------

/* clang-format off */
binaryCalc1DblExpr(addFunc, v0 + v1, false, false)
transfCalc1DblExpr(reciprocalFunc, 1/v)
transfCalc1DblExpr(negativeFunc, -v)
binaryCalc1DblExpr(multiplyFunc, v0 * v1, true, false)
binaryCalc1DblExpr(divideFunc, v0 / v1, false, true)
binaryCalc1DblExpr(powerFunc, pow(v0 , v1), false, false)
binaryCalc1DblExpr(subtractFunc, v0 - v1, false, false)
binaryCalc1DblExpr(modFunc, fmod(v0 , v1), false, false)
/* clang-format on */

// ------------------------------------------------------------------------
//                               Initialize
// ------------------------------------------------------------------------

void initializeArithmetic(v8exports exports) {

  NODE_SET_METHOD(exports, "add", addFunc);
  NODE_SET_METHOD(exports, "reciprocal", reciprocalFunc);
  NODE_SET_METHOD(exports, "negative", negativeFunc);
  NODE_SET_METHOD(exports, "multiply", multiplyFunc);
  NODE_SET_METHOD(exports, "divide", divideFunc);
  NODE_SET_METHOD(exports, "power", powerFunc);
  NODE_SET_METHOD(exports, "subtract", subtractFunc);
  NODE_SET_METHOD(exports, "mod", modFunc);
}

} // namespace numnjs