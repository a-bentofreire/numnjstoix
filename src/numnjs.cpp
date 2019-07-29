// uuid: 9babe256-16f5-47d6-a75e-6fbf0e3f14dc

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
//                               Constants
// ------------------------------------------------------------------------

#define VERSION "0.1.1"

// ------------------------------------------------------------------------
//                               Actual Functions
// ------------------------------------------------------------------------

void verFunc(const v8args &args) {

  v8::Isolate *isolate = v8::Isolate::GetCurrent();
  v8::HandleScope scope(isolate);

  if (!checkArgCount(isolate, args, 0, 0)) {
    return;
  }
  returnString(isolate, VERSION, args);
}

// ------------------------------------------------------------------------
//                               Initialize Functions
// ------------------------------------------------------------------------

void Initialize(v8exports exports) {

  NODE_SET_METHOD(exports, "ver", verFunc);
  initializeTrigonometric(exports);
  initializeHyperbolic(exports);
  initializeRounding(exports);
  initializeSums(exports);
  initializeExpLogs(exports);
  initializeArithmetic(exports);
  initializeMiscellaneous(exports);
  initializeMatrix(exports);
  initializeStatistics(exports);
}

NODE_MODULE(NODE_GYP_MODULE_NAME, Initialize)

} // namespace numnjs