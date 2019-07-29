// uuid: 045cc70e-0803-4e8e-9906-adc5928be3f7

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
#include <math.h>
#include <node.h>
#include <vector>

namespace numnjs {

// ------------------------------------------------------------------------
//                               Actual Functions
// ------------------------------------------------------------------------

/* clang-format off */
transfCalc1DblFunc(sinhFunc, sinh)
transfCalc1DblFunc(coshFunc, cosh)
transfCalc1DblFunc(tanhFunc, tanh)

transfCalc1DblFunc(arcsinhFunc, asinh)
transfCalc1DblFunc(arccoshFunc, acosh)
transfCalc1DblFunc(arctanhFunc, atanh)
/* clang-format on */

// ------------------------------------------------------------------------
//                               Initialize
// ------------------------------------------------------------------------

void initializeHyperbolic(v8exports exports) {

  NODE_SET_METHOD(exports, "sinh", sinhFunc);
  NODE_SET_METHOD(exports, "cosh", coshFunc);
  NODE_SET_METHOD(exports, "tanh", tanhFunc);

  NODE_SET_METHOD(exports, "arcsinh", arcsinhFunc);
  NODE_SET_METHOD(exports, "arccosh", arccoshFunc);
  NODE_SET_METHOD(exports, "arctanh", arctanhFunc);
}

} // namespace numnjs