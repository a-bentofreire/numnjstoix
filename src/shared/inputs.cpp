// ------------------------------------------------------------------------
// Copyright (c) 2019-2024 Alexandre Bento Freire. All rights reserved.
// Licensed under the MIT License
// ------------------------------------------------------------------------

// ------------------------------------------------------------------------
//                               Includes
// ------------------------------------------------------------------------

#include "../numnjs.h"
#include <node.h>

namespace numnjs {

// ------------------------------------------------------------------------
//                               Errors Messages
// ------------------------------------------------------------------------

const char *ERR_REQ_N_ARG = "It requires %d argument(s)";
const char *ERR_REQ_AT_LEAST_ARG = "It requires at least %d argument(s)";
const char *ERR_REQ_AT_MOST_ARG = "It requires at most %d argument(s)";

// ------------------------------------------------------------------------
//                               Exception Handling
// ------------------------------------------------------------------------

bool checkArgCount(v8::Isolate *isolate, const v8args &args,
                   size_t reqMinArgCount, size_t reqMaxArgCount) {

  const size_t argsLen = args.Length();

  if (argsLen < reqMinArgCount) {
    returnException(isolate,
                    reqMinArgCount == reqMaxArgCount ? ERR_REQ_N_ARG
                                                     : ERR_REQ_AT_LEAST_ARG,
                    reqMinArgCount);
    return false;
  }

  if (argsLen > reqMaxArgCount) {
    returnException(isolate,
                    reqMinArgCount == reqMaxArgCount ? ERR_REQ_N_ARG
                                                     : ERR_REQ_AT_MOST_ARG,
                    reqMaxArgCount);
    return false;
  }

  return true;
}

bool getBoolInput(v8::Isolate *isolate, const v8args &args, size_t argNumber,
                  bool &outValue, bool required) {

  const v8::Local<v8::Value> &arg = args[argNumber];
  if (!arg->IsBoolean()) {
    if (required) {
      returnTypeMismatch(isolate, argNumber + 1);
    }
    return false;
  }
  v8::Local<v8::Boolean> boolValue = v8::Local<v8::Boolean>::Cast(arg);
  outValue = boolValue->Value();
  return true;
}

bool getIntInput(v8::Isolate *isolate, const v8args &args, size_t argNumber,
                 int &outValue, bool required) {

  const v8::Local<v8::Value> &arg = args[argNumber];
  if (!arg->IsNumber()) {
    if (required) {
      returnTypeMismatch(isolate, argNumber + 1);
    }
    return false;
  }
  v8::Local<v8::Integer> intValue = v8::Local<v8::Integer>::Cast(arg);
  outValue = intValue->Value();
  return true;
}

bool getPositiveIntInput(v8::Isolate *isolate, const v8args &args,
                         size_t argNumber, int &outValue, bool required) {
  if (!getIntInput(isolate, args, argNumber, outValue, required)) {
    return false;
  }

  if (outValue <= 0) {
    returnMustBePositive(isolate, argNumber + 1);
    return false;
  }

  return true;
}

int64_t getArgsData(const v8args &args) {
  return v8::Local<v8::Integer>::Cast(args.Data())->Value();
}

} // namespace numnjs