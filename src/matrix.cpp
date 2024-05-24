// ------------------------------------------------------------------------
// Copyright (c) 2019-2024 Alexandre Bento Freire. All rights reserved.
// Licensed under the MIT License
// ------------------------------------------------------------------------

// Implements matrix functions as described in:
// [Matrix](https://docs.scipy.org/doc/numpy-1.15.1/reference/routines.matlib.html)
//

// ------------------------------------------------------------------------
//                               Includes
// ------------------------------------------------------------------------

#include "numnjs.h"
#include <math.h>
#include <vector>

namespace numnjs {

// ------------------------------------------------------------------------
//                               Actual Functions
// ------------------------------------------------------------------------

/**
 * Calculates the diagonal function.
 */
void diagonalFunc(const v8args &args) {

  NSJAllow_Type allowTypes[] = {ta_MATRIX};

  nInputsHandler(args, 1, 1, allowTypes, [](NArrayInputs &naInputs) {
    NJSInputArray &input = naInputs.inputs[0];
    size_t dim = input.dim1;

    if (input.dim2 != dim) {
      returnMustBeSquareMatrix(naInputs.isolate, 1);
      return false;
    }

    int arrayType = typ_ARRAY;
    if (naInputs.argsp->Length() == 2) {
      if (getIntInput(naInputs.isolate, *naInputs.argsp, 1, arrayType, false) &&
          !isSingleDim((NJSArray_Type)arrayType)) {

        returnTypeMismatch(naInputs.isolate, 2);
        return false;
      }
    }

    njsarray &values = naInputs.valuesList[0];
    njsarray outValues(dim);
    size_t at = 0;
    for (size_t i = 0; i < dim; i++) {
      outValues[i] = values[at + i];
      at += dim;
    }
    naInputs.returnAsArray(outValues, (NJSArray_Type)arrayType);
    return true;
  });
}

/**
 * Calculates the eye function.
 */
void eyeFunc(const v8args &args) {
  generateHandler(args, 1, 1,
                  [](v8::Isolate *isolate, const v8args &args, njsarray &values,
                     NJSOutputArray &outArray) {
                    int dim = 0;
                    if (!getPositiveIntInput(isolate, args, 0, dim, true)) {
                      return false;
                    }

                    outArray.initAsMatrix(isolate, (size_t)dim, (size_t)dim);
                    values.resize(outArray.elCount);
                    int at = 0;
                    for (int i = 0; i < dim; i++) {
                      for (int j = 0; j < dim; j++) {
                        values[at++] = i == j ? 1.0 : 0.0;
                      }
                    }
                    return true;
                  });
}

bool fillMatrix(v8::Isolate *isolate, const v8args &args, njsarray &values,
                NJSOutputArray &outArray, double value,
                double(callback)() = NULL) {

  int dim1 = 0;
  int dim2 = 0;
  if (!getPositiveIntInput(isolate, args, 0, dim1, true) ||
      !getPositiveIntInput(isolate, args, 1, dim2, true)) {
    return false;
  }

  outArray.initAsMatrix(isolate, (size_t)dim1, (size_t)dim2);
  size_t elCount = outArray.elCount;
  values.resize(elCount);
  for (size_t i = 0; i < elCount; i++) {
    values[i] = callback == NULL ? value : callback();
  }
  return true;
}

/**
 * Calculates the zeros function.
 */
void zerosFunc(const v8args &args) {
  generateHandler(args, 2, 2,
                  [](v8::Isolate *isolate, const v8args &args, njsarray &values,
                     NJSOutputArray &outArray) {
                    return fillMatrix(isolate, args, values, outArray, 0.0);
                  });
}

/**
 * Calculates the ones function.
 */
void onesFunc(const v8args &args) {
  generateHandler(args, 2, 2,
                  [](v8::Isolate *isolate, const v8args &args, njsarray &values,
                     NJSOutputArray &outArray) {
                    return fillMatrix(isolate, args, values, outArray, 1.0);
                  });
}

/**
 * Calculates the rand function.
 */
void randFunc(const v8args &args) {
  generateHandler(args, 2, 2,
                  [](v8::Isolate *isolate, const v8args &args, njsarray &values,
                     NJSOutputArray &outArray) {
                    return fillMatrix(isolate, args, values, outArray, 0, []() {
                      return ((double)rand() / (RAND_MAX));
                    });
                  });
}

// ------------------------------------------------------------------------
//                               Initialize
// ------------------------------------------------------------------------

void initializeMatrix(v8exports exports) {

  srand(time(NULL));
  NODE_SET_METHOD(exports, "diagonal", diagonalFunc);
  NODE_SET_METHOD(exports, "eye", eyeFunc);
  NODE_SET_METHOD(exports, "ones", onesFunc);
  NODE_SET_METHOD(exports, "rand", randFunc);
  NODE_SET_METHOD(exports, "zeros", zerosFunc);
}

} // namespace numnjs