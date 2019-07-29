// uuid: bade8d12-b73c-476b-b321-aeab1b0229a6

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
//                               Global Variables
// ------------------------------------------------------------------------

const njsallow_typerec allowTypes[] = {

    // ta_ARRAY_FLOATARRAY
    {/* allowNumber : */ false,
     /* allowArray : */ true,
     /* allowMatrix : */ false,
     /* allowFloatArray : */ true},

    // ta_ARRAY_FLOATARRAY_MATRIX
    {/* allowNumber : */ false,
     /* allowArray : */ true,
     /* allowMatrix : */ true,
     /* allowFloatArray : */ true},

    // ta_ARRAY_FLOATARRAY_MATRIX_NUMBER
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

  const njsallow_typerec &allowTypeRec = allowTypes[allowType];

  if (src->IsArray()) {
    arrayType = typ_ARRAY;
    inputA = v8localArray::Cast(src);
    size_t _dim1 = inputA->Length();
    dim1 = _dim1;

    if (_dim1 > 0) {
      v8::Local<v8::Value> el = inputA->Get(0);
      if (el->IsArray()) {
        if (!allowTypeRec.allowMatrix) {
          returnTypeMismatch(isolate, argNumber);
          return false;
        }

        arrayType = typ_MATRIX;
        isSingleDim = false;
        isMatrix = true;
        nrdims = 2;
        matrixRows = new std::vector<v8localArray>(_dim1);

        for (size_t i = 0; i < _dim1; i++) {
          v8::Local<v8::Value> el = inputA->Get(i);
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
        dim2 = (*matrixRows)[0]->Length();
      }
    }

    if (!allowTypeRec.allowArray && nrdims == 1) {
      returnTypeMismatch(isolate, argNumber);
      return false;
    }

  } else if (src->IsTypedArray()) {
    if (!allowTypeRec.allowFloatArray) {
      returnTypeMismatch(isolate, argNumber);
      return false;
    }
    isTypedArray = true;
    arrayType =
        src->IsFloat32Array() ? typ_FLOATARRAY32 : typ_FLOATARRAY64;
    inputTA = v8::Local<v8::TypedArray>::Cast(src);
    dim1 = inputTA->Length();

  } else if (src->IsNumber()) {
    if (!allowTypeRec.allowNumber) {
      returnTypeMismatch(isolate, argNumber);
      return false;
    }
    isSingleDim = false;
    isNumber = true;
    nrdims = 0;
    dim1 = 1;
    numberValue = src->NumberValue();
  }

  else {
    returnTypeMismatch(isolate, argNumber);
    return false;
  }

  elCount = dim1 * dim2;
  return true;
}

double NJSInputArray::getDouble(size_t i) {
  v8::Local<v8::Value> el;

  switch (nrdims) {
  case 0:
    return numberValue;

  case 1:
    el = isTypedArray ? inputTA->Get(i) : inputA->Get(i);
    return el->NumberValue();

  case 2:
    v8localArray &row = (*matrixRows)[i / dim2];
    el = row->Get(i % dim2);
    return el->NumberValue();
  }
  return 0; // to avoid warning message
}

// ------------------------------------------------------------------------
//                               NJSOutputArray
// ------------------------------------------------------------------------

void NJSOutputArray::init(v8::Isolate *isolate, NJSArray_Type arrayType,
                          size_t _elCount, size_t _nrdims, size_t _dim1,
                          size_t _dim2) {

  elCount = _elCount;
  dim1 = _dim1;
  dim2 = _dim2;
  nrdims = _nrdims;

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

  case typ_FLOATARRAY32:
    recSize = 4;
    array_buffer = v8::ArrayBuffer::New(isolate, recSize * _elCount);
    res = v8::Float32Array::New(array_buffer, 0, _elCount);
    break;

  default:
    // case typ_FLOATARRAY64:
    recSize = 8;
    array_buffer = v8::ArrayBuffer::New(isolate, recSize * _elCount);
    res = v8::Float64Array::New(array_buffer, 0, _elCount);
    break;
  }
}

void NJSOutputArray::initFromInput(v8::Isolate *isolate,
                                   const NJSInputArray &inputArray) {
  init(isolate, inputArray.arrayType, inputArray.elCount,
             inputArray.nrdims, inputArray.dim1, inputArray.dim2);
}

void NJSOutputArray::setFromArray(v8::Isolate *isolate, const njsarray &values,
                                  const v8args &args) {

  size_t _elCount = elCount;
  size_t _dim2 = dim2;
  v8::Local<v8::Object> row;

  for (size_t i = 0; i < _elCount; i++) {
    v8::Local<v8::Number> v = v8::Number::New(isolate, values[i]);
    switch (nrdims) {
    case 1:
      // @TODO: Speed the process of setting each value
      res->Set(i, v);
      break;

    case 2: {
      size_t p1 = i / _dim2;
      size_t p2 = i % _dim2;
      if (p2 == 0) {
        row = v8::Array::New(isolate, _dim2);
        res->Set(p1, row);
      }
      row->Set(p2, v);
    } break;
    }
  }
  args.GetReturnValue().Set(res);
}

} // namespace numnjs