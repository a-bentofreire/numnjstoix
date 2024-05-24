// ------------------------------------------------------------------------
// Copyright (c) 2019-2024 Alexandre Bento Freire. All rights reserved.
// Licensed under the MIT License
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