// ------------------------------------------------------------------------
// Copyright (c) 2019-2024 Alexandre Bento Freire. All rights reserved.
// Licensed under the MIT License
// ------------------------------------------------------------------------

// ------------------------------------------------------------------------
//                               Includes
// ------------------------------------------------------------------------

#include "../numnjstoix.h"
#include <cmath>
#include <node.h>

namespace numnjstoix {

// ------------------------------------------------------------------------
//                               Global Variables
// ------------------------------------------------------------------------

const njs_allow_typerec allowTypes[] = {

    // ta_ARRAY_FLOAT_ARRAY
    {/* allowNumber : */ false,
     /* allowArray : */ true,
     /* allowMatrix : */ false,
     /* allowFloatArray : */ true},

    // ta_ARRAY_FLOAT_ARRAY_MATRIX
    {/* allowNumber : */ false,
     /* allowArray : */ true,
     /* allowMatrix : */ true,
     /* allowFloatArray : */ true},

    // ta_ARRAY_FLOAT_ARRAY_MATRIX_NUMBER
    {/* allowNumber : */ true,
     /* allowArray : */ true,
     /* allowMatrix : */ true,
     /* allowFloatArray : */ true},

    // ta_MATRIX
    {/* allowNumber : */ false,
     /* allowArray : */ false,
     /* allowMatrix : */ true,
     /* allowFloatArray : */ false}};

// ------------------------------------------------------------------------
//                               NJSInputArray
// ------------------------------------------------------------------------

NJSInputArray::~NJSInputArray() { delete matrixRows; }

bool NJSInputArray::init(v8::Isolate *isolate, const v8::Local<v8::Value> src,
                         NSJAllow_Type allowType, size_t argNumber) {

  const njs_allow_typerec &allowTypeRec = allowTypes[allowType];
  v8::Local<v8::Context> context = isolate->GetCurrentContext();

  if (src->IsArray()) {
    arrayType = typ_ARRAY;
    inputA = v8localArray::Cast(src);
    size_t _dim1 = inputA->Length();
    dim1 = _dim1;

    if (_dim1 > 0) {
      v8::Local<v8::Value> el;
      if (inputA->Get(context, 0).ToLocal(&el) && el->IsArray()) {
        if (!allowTypeRec.allowMatrix) {
          returnTypeMismatch(isolate, argNumber);
          return false;
        }

        arrayType = typ_MATRIX;
        isSingleDim = false;
        isMatrix = true;
        nrDims = 2;
        matrixRows = new std::vector<v8localArray>(_dim1);

        for (size_t i = 0; i < _dim1; i++) {
          if (inputA->Get(context, i).ToLocal(&el)) {
            v8localArray *row = &((*matrixRows)[i]);
            *row = v8localArray::Cast(el);
            size_t rowSize = (*row)->Length();
            if (i == 0) {
              dim2 = rowSize;
            } else if (dim2 != rowSize) {

              returnTypeMismatch(isolate, argNumber);
              return false;
            }
          }
        }
        dim2 = (*matrixRows)[0]->Length();
      }
    }

    if (!allowTypeRec.allowArray && nrDims == 1) {
      returnTypeMismatch(isolate, argNumber);
      return false;
    }

  } else if (src->IsTypedArray()) {
    if (!allowTypeRec.allowFloatArray) {
      returnTypeMismatch(isolate, argNumber);
      return false;
    }
    isTypedArray = true;
    arrayType = src->IsFloat32Array() ? typ_FLOAT_ARRAY32 : typ_FLOAT_ARRAY64;
    inputTA = v8::Local<v8::TypedArray>::Cast(src);
    dim1 = inputTA->Length();

  } else if (src->IsNumber()) {
    if (!allowTypeRec.allowNumber) {
      returnTypeMismatch(isolate, argNumber);
      return false;
    }
    isSingleDim = false;
    nrDims = 0;
    dim1 = 1;
    v8::Maybe<double> maybeEl = src->NumberValue(context);
    if (maybeEl.IsJust()) {
      numberValue = maybeEl.FromJust();
      isNumber = true;
    } else {
      return false;
    }
  }

  else {
    returnTypeMismatch(isolate, argNumber);
    return false;
  }

  elCount = dim1 * dim2;
  return true;
}

double NJSInputArray::getDouble(size_t i, v8::Local<v8::Context> context) {
  v8::Local<v8::Value> el;

  switch (nrDims) {
  case 0:
    return numberValue;

  case 1:
    if (isTypedArray ? inputTA->Get(context, i).ToLocal(&el)
                     : inputA->Get(context, i).ToLocal(&el)) {
      v8::Maybe<double> maybeEl = el->NumberValue(context);
      return maybeEl.IsJust() ? maybeEl.FromJust() : std::nan("");
    } else {
      return std::nan("");
    }

  case 2:
    v8localArray &row = (*matrixRows)[i / dim2];
    if (row->Get(context, i % dim2).ToLocal(&el)) {
      v8::Maybe<double> maybeEl = el->NumberValue(context);
      return maybeEl.IsJust() ? maybeEl.FromJust() : std::nan("");
    } else {
      return std::nan("");
    }
  }
  return 0; // to avoid warning message
}

// ------------------------------------------------------------------------
//                               NJSOutputArray
// ------------------------------------------------------------------------

void NJSOutputArray::init(v8::Isolate *isolate, NJSArray_Type arrayType,
                          size_t _elCount, size_t _nr_dims, size_t _dim1,
                          size_t _dim2) {

  elCount = _elCount;
  dim1 = _dim1;
  dim2 = _dim2;
  nrDims = _nr_dims;

  switch (arrayType) {
  case typ_MATRIX:
    recSize = 0;
    res = v8::Array::New(isolate, _dim1);
    break;

  case typ_NUMBER:
  case typ_ARRAY:
    recSize = 0;
    res = v8::Array::New(isolate, _elCount);
    break;

  case typ_FLOAT_ARRAY32:
    recSize = 4;
    array_buffer = v8::ArrayBuffer::New(isolate, recSize * _elCount);
    res = v8::Float32Array::New(array_buffer, 0, _elCount);
    break;

  default:
    // case typ_FLOAT_ARRAY64:
    recSize = 8;
    array_buffer = v8::ArrayBuffer::New(isolate, recSize * _elCount);
    res = v8::Float64Array::New(array_buffer, 0, _elCount);
    break;
  }
}

void NJSOutputArray::initFromInput(v8::Isolate *isolate,
                                   const NJSInputArray &inputArray) {
  init(isolate, inputArray.arrayType, inputArray.elCount, inputArray.nrDims,
       inputArray.dim1, inputArray.dim2);
}

void NJSOutputArray::setFromArray(v8::Isolate *isolate, const njsArray &values,
                                  const v8args &args) {

  size_t _elCount = elCount;
  size_t _dim2 = dim2;
  v8::Local<v8::Object> row;
  v8::Local<v8::Context> context = isolate->GetCurrentContext();
  v8::Maybe<bool> result1 = v8::Just(true);
  v8::Maybe<bool> result2 = v8::Just(true);
  v8::Maybe<bool> result3 = v8::Just(true);

  for (size_t i = 0; i < _elCount; i++) {
    v8::Local<v8::Number> v = v8::Number::New(isolate, values[i]);
    switch (nrDims) {
    case 1:
      // @TODO: Speed the process of setting each value
      result1 = res->Set(context, i, v);
      if (result1.IsNothing() || !result1.FromJust()) {
        returnNodeError(isolate);
      }
      break;

    case 2:
      size_t p1 = i / _dim2;
      size_t p2 = i % _dim2;
      if (p2 == 0) {
        row = v8::Array::New(isolate, _dim2);
        result2 = res->Set(context, p1, row);
        if (result2.IsNothing() || !result2.FromJust()) {
          returnNodeError(isolate);
        }
      }
      result3 = row->Set(context, p2, v);
      if (result3.IsNothing() || !result3.FromJust()) {
        returnNodeError(isolate);
      }
      break;
    }
  }
  args.GetReturnValue().Set(res);
}

} // namespace numnjstoix