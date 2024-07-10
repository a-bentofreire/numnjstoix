// ------------------------------------------------------------------------
// Copyright (c) 2019-2024 Alexandre Bento Freire. All rights reserved.
// Licensed under the MIT License
// ------------------------------------------------------------------------

// ------------------------------------------------------------------------
//                               Includes
// ------------------------------------------------------------------------

#include "../numnjs.h"
#include <node.h>
#include <stdarg.h>

namespace numnjs {

// ------------------------------------------------------------------------
//                               Errors Messages
// ------------------------------------------------------------------------

const char *ERR_TYPE_MISMATCH = "Argument %d has an invalid type";
const char *ERR_MUST_BE_POSITIVE = "Argument %d must be positive";
const char *ERR_BOTH_INPUT_MUST_SAME_LEN =
    "Both arguments must have the same length";
const char *ERR_MUST_BE_SQUARE_MATRIX = "Argument %d must be a square matrix";
const char *ERR_NODE = "Node error";

// ------------------------------------------------------------------------
//                               Exception Handling
// ------------------------------------------------------------------------

void returnTypeMismatch(v8::Isolate *isolate, size_t argNumber) {
  returnException(isolate, ERR_TYPE_MISMATCH, argNumber);
}

void returnMustBePositive(v8::Isolate *isolate, size_t argNumber) {
  returnException(isolate, ERR_MUST_BE_POSITIVE, argNumber);
}

void returnInputMustSameLen(v8::Isolate *isolate) {
  returnException(isolate, ERR_BOTH_INPUT_MUST_SAME_LEN);
}

void returnMustBeSquareMatrix(v8::Isolate *isolate, size_t argNumber) {
  returnException(isolate, ERR_MUST_BE_SQUARE_MATRIX, argNumber);
}

void returnNodeError(v8::Isolate *isolate) {
  returnException(isolate, ERR_NODE);
}

void returnException(v8::Isolate *isolate, const char *msg, ...) {

  va_list args;
  va_start(args, msg);
  char buf[512];
  vsnprintf(buf, sizeof(buf), msg, args);
  va_end(args);

  isolate->ThrowException(
      v8::Exception::TypeError(v8::String::NewFromUtf8(isolate, buf).ToLocalChecked()));
}

} // namespace numnjs