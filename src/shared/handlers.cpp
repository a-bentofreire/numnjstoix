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
//                               Errors Messages
// ------------------------------------------------------------------------

const char *ERR_BOTH_INPUT_CANT_BE_NUMBER = "Both arguments can't be numbers";

// ------------------------------------------------------------------------
//                               aggregate1Handler
// ------------------------------------------------------------------------

void aggregate1Handler(const v8args &args, double acc,
                       bool(initialize)(aggregateParams &params),
                       double(calc)(double v, double acc),
                       double(finalize)(size_t validLen, double acc,
                                        njsArray &values,
                                        aggregateParams &params),
                       bool reqValues, NSJAllow_Type allowType) {

  v8::Isolate *isolate = v8::Isolate::GetCurrent();
  v8::HandleScope scope(isolate);

  aggregateParams params;

  params.isolate = isolate;
  params.args = &args;
  params.argsLen = args.Length();
  params.minParams = 1;
  params.maxParams = 1;

  if (initialize && !initialize(params)) {
    return;
  }

  if (!checkArgCount(isolate, args, params.minParams, params.maxParams)) {
    return;
  }

  v8::Local<v8::Value> arg0 = args[0];
  NJSInputArray input;

  if (!input.init(isolate, arg0, allowType, 1)) {
    return;
  }

  njsArray validValues;
  size_t validLen = 0;
  auto elCount = input.elCount;
  v8::Local<v8::Context> context = isolate->GetCurrentContext();

  for (size_t i = 0; i < elCount; i++) {
    double v = input.getDouble(i, context);
    if (isValidValue(v)) {
      acc = calc(v, acc);
      validLen++;
      if (reqValues) {
        validValues.push_back(v);
      }
    }
  }

  if (finalize != NULL) {
    acc = finalize(validLen, acc, validValues, params);
  }

  returnNumber(isolate, acc, args);
}

// ------------------------------------------------------------------------
//                               binaryHandler
// ------------------------------------------------------------------------

void binaryHandler(const v8args &args, double(calc)(double v0, double v1),
                   void(finalize)(size_t validLen, njsArray &values),
                   bool allowNumber0, bool allowNumber1) {

  v8::Isolate *isolate = v8::Isolate::GetCurrent();
  v8::HandleScope scope(isolate);

  if (!checkArgCount(isolate, args, 2, 2)) {
    return;
  }

  v8::Local<v8::Value> arg0 = args[0];
  NJSInputArray input0;

  if (!input0.init(isolate, arg0,
                   allowNumber0 ? ta_ARRAY_FLOAT_ARRAY_MATRIX_NUMBER
                                : ta_ARRAY_FLOAT_ARRAY_MATRIX,
                   1)) {
    return;
  }

  v8::Local<v8::Value> arg1 = args[1];
  NJSInputArray input1;

  if (!input1.init(isolate, arg1,
                   allowNumber1 ? ta_ARRAY_FLOAT_ARRAY_MATRIX_NUMBER
                                : ta_ARRAY_FLOAT_ARRAY_MATRIX,
                   2)) {
    return;
  }

  auto elCount0 = input0.elCount;
  auto elCount1 = input1.elCount;

  if (input0.isNumber || input1.isNumber) {
    if (input0.isNumber && input1.isNumber) {
      returnException(isolate, ERR_BOTH_INPUT_CANT_BE_NUMBER);
      return;
    }
    if (input0.isNumber) {
      elCount0 = elCount1;
    }
  } else if (elCount0 != elCount1) {
    returnInputMustSameLen(isolate);
    return;
  }

  njsArray values(elCount0);
  size_t validLen = 0;
  v8::Local<v8::Context> context = isolate->GetCurrentContext();

  // #pragma omp parallel private(validLen)
  for (size_t i = 0; i < elCount0; i++) {
    double v0 = input0.getDouble(i, context);
    double v1 = input1.getDouble(i, context);
    if (isValidValue(v0) && isValidValue(v1)) {
      v0 = calc(v0, v1);
      // #pragma omp atomic update
      validLen++;
    }
    values[i] = v0;
  }

  if (finalize != NULL) {
    finalize(validLen, values);
  };

  NJSOutputArray outArray;

  outArray.initFromInput(isolate, !input0.isNumber ? input0 : input1);
  outArray.setFromArray(isolate, values, args);
}

// ------------------------------------------------------------------------
//                               transformHandler
// ------------------------------------------------------------------------

void transformHandler(const v8args &args, double(calc)(double v),
                      void(finalize)(size_t validLen, njsArray &values)) {

  v8::Isolate *isolate = v8::Isolate::GetCurrent();
  v8::HandleScope scope(isolate);

  if (!checkArgCount(isolate, args, 1, 1)) {
    return;
  }

  v8::Local<v8::Value> arg0 = args[0];
  NJSInputArray input;

  if (!input.init(isolate, arg0, ta_ARRAY_FLOAT_ARRAY_MATRIX, 1)) {
    return;
  }

  size_t validLen = 0;
  auto elCount = input.elCount;
  njsArray values(elCount);
  v8::Local<v8::Context> context = isolate->GetCurrentContext();
  for (size_t i = 0; i < elCount; i++) {
    double v = input.getDouble(i, context);
    if (isValidValue(v)) {
      v = calc(v);
      validLen++;
    }
    values[i] = v;
  }

  if (finalize != NULL) {
    finalize(validLen, values);
  };

  NJSOutputArray outArray;
  outArray.initFromInput(isolate, input);
  outArray.setFromArray(isolate, values, args);
}

// ------------------------------------------------------------------------
//                               generateHandler
// ------------------------------------------------------------------------

void generateHandler(const v8args &args, size_t minArgNumber,
                     size_t maxArgNumber,
                     bool(finalize)(v8::Isolate *isolate, const v8args &args,
                                    njsArray &values,
                                    NJSOutputArray &outArray)) {

  v8::Isolate *isolate = v8::Isolate::GetCurrent();
  v8::HandleScope scope(isolate);

  if (!checkArgCount(isolate, args, minArgNumber, maxArgNumber)) {
    return;
  }

  njsArray values;
  NJSOutputArray outArray;
  if (!finalize(isolate, args, values, outArray)) {
    return;
  }
  outArray.setFromArray(isolate, values, args);
}

// ------------------------------------------------------------------------
//                               nInputsHandler
// ------------------------------------------------------------------------

bool NArrayInputs::init(v8::Isolate *isolate, const v8args &args,
                        size_t _numInputs, NSJAllow_Type *allowTypes) {

  numInputs = _numInputs;
  valueArgs.resize(numInputs);
  inputs.resize(numInputs);

  for (size_t i = 0; i < numInputs; i++) {
    valueArgs[i] = args[i];
    if (!(inputs[i]).init(isolate, valueArgs[i], allowTypes[i], i + 1)) {
      return false;
    }
  }
  return true;
}

void NArrayInputs::loadData(v8::Isolate *isolate) {

  auto _numInputs = numInputs;
  valuesList.resize(_numInputs);
  validLenList.resize(_numInputs);
  v8::Local<v8::Context> context = isolate->GetCurrentContext();

  for (size_t i = 0; i < _numInputs; i++) {
    auto elCount = inputs[i].elCount;
    NJSInputArray &input = inputs[i];
    njsArray &values = valuesList[i];
    values.resize(elCount);
    size_t validLen = 0;

    for (size_t j = 0; j < elCount; j++) {
      double v = input.getDouble(j, context);
      if (isValidValue(v)) {
        validLen++;
      }
      values[j] = v;
    }
    validLenList[i] = validLen;
  }
}

void nInputsHandler(const v8args &args, size_t numInputs, size_t extraArgs,
                    NSJAllow_Type *allowTypes,
                    bool(op)(NArrayInputs &naInputs)) {

  v8::Isolate *isolate = v8::Isolate::GetCurrent();
  v8::HandleScope scope(isolate);

  if (!checkArgCount(isolate, args, numInputs, numInputs + extraArgs)) {
    return;
  }

  NArrayInputs naInputs(args);
  naInputs.isolate = isolate;
  if (!naInputs.init(isolate, args, numInputs, allowTypes)) {
    return;
  }

  naInputs.loadData(isolate);
  if (!op(naInputs)) {
    return;
  }
}

} // namespace numnjstoix