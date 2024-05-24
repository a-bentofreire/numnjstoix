// ------------------------------------------------------------------------
// Copyright (c) 2019-2024 Alexandre Bento Freire. All rights reserved.
// Licensed under the MIT License
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
transfCalc1DblFunc(expFunc, exp)
transfCalc1DblFunc(expm1Func, expm1)
transfCalc1DblFunc(exp2Func, exp2)

transfCalc1DblFunc(logFunc, log)
transfCalc1DblFunc(log10Func, log10)
transfCalc1DblFunc(log2Func, log2)
/* clang-format on */

// ------------------------------------------------------------------------
//                               Initialize
// ------------------------------------------------------------------------

void initializeExpLogs(v8exports exports) {

  NODE_SET_METHOD(exports, "exp", expFunc);
  NODE_SET_METHOD(exports, "expm1", expm1Func);
  NODE_SET_METHOD(exports, "exp2", exp2Func);

  NODE_SET_METHOD(exports, "log", logFunc);
  NODE_SET_METHOD(exports, "log10", log10Func);
  NODE_SET_METHOD(exports, "log2", log2Func);
}

} // namespace numnjs