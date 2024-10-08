// ------------------------------------------------------------------------
// Copyright (c) 2019-2024 Alexandre Bento Freire. All rights reserved.
// Licensed under the MIT License
// ------------------------------------------------------------------------

// ------------------------------------------------------------------------
//                               Includes
// ------------------------------------------------------------------------

#include "../numnjstoix.h"
#include <node.h>

namespace numnjstoix {

// ------------------------------------------------------------------------
//                               Result Functions
// ------------------------------------------------------------------------

void returnString(v8::Isolate *isolate, const char *value, const v8args &args) {
  args.GetReturnValue().Set(v8::String::NewFromUtf8(isolate, value).ToLocalChecked());
}

void returnNumber(v8::Isolate *isolate, double value, const v8args &args) {
  v8::Local<v8::Number> res = v8::Number::New(isolate, value);
  args.GetReturnValue().Set(res);
}

} // namespace numnjstoix