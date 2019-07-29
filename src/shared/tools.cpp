// uuid: 56675641-83ea-4893-8620-74a441b47571

// ------------------------------------------------------------------------
// Copyright (c) 2019 Alexandre Bento Freire. All rights reserved.
// Licensed under the MIT License+uuid License. See License.txt for details
// ------------------------------------------------------------------------

// ------------------------------------------------------------------------
//                               Includes
// ------------------------------------------------------------------------

#include "../numnjs.h"
#include <cmath>
#include <node.h>

namespace numnjs {

// ------------------------------------------------------------------------
//                               Node Overrides
// ------------------------------------------------------------------------

void NODE_SET_METHOD_DATA(v8::Local<v8::Object> recv, const char *name,
                          v8::FunctionCallback callback, int dataValue) {

  v8::Isolate *isolate = v8::Isolate::GetCurrent();
  v8::HandleScope handle_scope(isolate);
  const v8::Local<v8::Integer> data = v8::Integer::New(isolate, dataValue);
  v8::Local<v8::Context> context = isolate->GetCurrentContext();
  v8::Local<v8::FunctionTemplate> t =
      v8::FunctionTemplate::New(isolate, callback, data);
  v8::Local<v8::Function> fn = t->GetFunction(context).ToLocalChecked();
  v8::Local<v8::String> fn_name =
      v8::String::NewFromUtf8(isolate, name, v8::NewStringType::kInternalized)
          .ToLocalChecked();
  fn->SetName(fn_name);
  recv->Set(context, fn_name, fn).FromJust();
}

// ------------------------------------------------------------------------
//                               Test Functions
// ------------------------------------------------------------------------

bool isValidValue(double x) { return !(std::isinf(x) || std::isnan(x)); }

} // namespace numnjs