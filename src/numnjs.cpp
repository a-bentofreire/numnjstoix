// ------------------------------------------------------------------------
// Copyright (c) 2019-2024 Alexandre Bento Freire. All rights reserved.
// Licensed under the MIT License
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

#define VERSION "0.2.0"

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

void Initialize(v8exports exports, v8::Local<v8::Value> module, void* priv) {

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