// uuid: f27124bf-dbd4-442c-91f0-0b74f9fecfa5

// ------------------------------------------------------------------------
// Copyright (c) 2019 Alexandre Bento Freire. All rights reserved.
// Licensed under the MIT License+uuid License. See License.txt for details
// ------------------------------------------------------------------------

// ------------------------------------------------------------------------
//                               Includes
// ------------------------------------------------------------------------

#include "numnjs.h"
#include <cmath>
#include <limits>
#include <node.h>

namespace numnjs {

// ------------------------------------------------------------------------
//                               Aggregate Functions
// ------------------------------------------------------------------------

void sumFunc(const v8args &args) {
  aggregate1Handler(args, 0, NULL, [](double v, double acc) { return v + acc; },
                    NULL, false, ta_ARRAY_FLOATARRAY_MATRIX);
}

// ------------------------------------------------------------------------
//                               Initialize
// ------------------------------------------------------------------------

void initializeSums(v8exports exports) {

  NODE_SET_METHOD(exports, "sum", sumFunc);
}

} // namespace numnjs