// ------------------------------------------------------------------------
// Copyright (c) 2019-2024 Alexandre Bento Freire. All rights reserved.
// Licensed under the MIT License
// ------------------------------------------------------------------------

// ------------------------------------------------------------------------
//                               Includes
// ------------------------------------------------------------------------

#define _USE_MATH_DEFINES
#include "numnjs.h"
#include <math.h>
#include <node.h>

namespace numnjs {

// ------------------------------------------------------------------------
//                               Actual Functions
// ------------------------------------------------------------------------

/* clang-format off */
transfCalc1DblFunc(sinFunc, sin)
transfCalc1DblFunc(cosFunc, cos)
transfCalc1DblFunc(tanFunc, tan)

transfCalc1DblFunc(arcsinFunc, asin)
transfCalc1DblFunc(arccosFunc, acos)
transfCalc1DblFunc(arctanFunc, atan)

transfCalc1DblExpr(degreesFunc,  v * (180 * M_1_PI))
transfCalc1DblExpr(radiansFunc,  v / (180 * M_1_PI))
/* clang-format on */

// ------------------------------------------------------------------------
//                               Initialize
// ------------------------------------------------------------------------

void initializeTrigonometric(v8exports exports) {

  NODE_SET_METHOD(exports, "sin", sinFunc);
  NODE_SET_METHOD(exports, "cos", cosFunc);
  NODE_SET_METHOD(exports, "tan", tanFunc);

  NODE_SET_METHOD(exports, "arcsin", arcsinFunc);
  NODE_SET_METHOD(exports, "arccos", arccosFunc);
  NODE_SET_METHOD(exports, "arctan", arctanFunc);

  NODE_SET_METHOD(exports, "degrees", degreesFunc);
  NODE_SET_METHOD(exports, "radians", radiansFunc);
}

} // namespace numnjs