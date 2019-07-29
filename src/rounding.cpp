// uuid: e0b0613c-7064-496f-9181-f7570a79d5ae

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

} // namespace numnjs