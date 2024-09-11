// ------------------------------------------------------------------------
// Copyright (c) 2019-2024 Alexandre Bento Freire. All rights reserved.
// Licensed under the MIT License
// ------------------------------------------------------------------------

// ------------------------------------------------------------------------
//                               Includes
// ------------------------------------------------------------------------

#include "numnjstoix.h"
#include <math.h>
#include <node.h>

namespace numnjstoix {

// ------------------------------------------------------------------------
//                               Actual Functions
// ------------------------------------------------------------------------

/* clang-format off */
transfCalc1DblFunc(roundFunc, round)
transfCalc1DblFunc(floorFunc, floor)
transfCalc1DblFunc(ceilFunc, ceil)
/* clang-format on */

// ------------------------------------------------------------------------
//                               Initialize
// ------------------------------------------------------------------------

void initializeRounding(v8exports exports) {

  NODE_SET_METHOD(exports, "round", roundFunc);
  NODE_SET_METHOD(exports, "floor", floorFunc);
  NODE_SET_METHOD(exports, "ceil", ceilFunc);
}

} // namespace numnjstoix