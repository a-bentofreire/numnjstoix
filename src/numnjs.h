
// ------------------------------------------------------------------------
// Copyright (c) 2019-2024 Alexandre Bento Freire. All rights reserved.
// Licensed under the MIT License
// ------------------------------------------------------------------------

// ------------------------------------------------------------------------
//                               Includes
// ------------------------------------------------------------------------

#include <node.h>

namespace numnjs {

// ------------------------------------------------------------------------
//                               Typedefs
// ------------------------------------------------------------------------

typedef v8::FunctionCallbackInfo<v8::Value> v8args;
typedef v8::Local<v8::Object> v8exports;
typedef v8::Local<v8::Array> v8localArray;
typedef std::vector<double> njsarray;

// ------------------------------------------------------------------------
//                               NJS Array Management (njsarrays.cpp)
// ------------------------------------------------------------------------

enum NSJAllow_Type {
  ta_ARRAY_FLOATARRAY,
  ta_ARRAY_FLOATARRAY_MATRIX,
  ta_ARRAY_FLOATARRAY_MATRIX_NUMBER,
  ta_MATRIX,
};

struct njsallow_typerec {
  bool allowNumber;
  bool allowArray;
  bool allowMatrix;
  bool allowFloatArray;
};

enum NJSArray_Type {
  typ_AUTO = 0,
  typ_NUMBER = 1,
  typ_ARRAY = 10,
  typ_MATRIX,
  typ_FLOATARRAY32 = 20,
  typ_FLOATARRAY64
};

/**
 * Abstracts from handling v8 Array/TypedArray methods from input arguments
 */
class NJSInputArray {
private:
  v8::Local<v8::TypedArray> inputTA;
  v8localArray inputA;
  std::vector<v8localArray> *matrixRows = NULL;

public:
  ~NJSInputArray();
  bool isTypedArray = false;
  /** True if it's an Array or TypedArray */
  bool isSingleDim = true;
  bool isNumber = false;
  bool isMatrix = false;

  /** Input value in case the input type if a Number */
  double numberValue;

  NJSArray_Type arrayType;
  /** Number of dimensions: 0 - number, 1 - Array/TypedArray, 2 - Matrix */
  size_t nrdims = 1;
  /** Number of elements in the first dimension */
  size_t dim1;
  /** Number of elements in the second dimension */
  size_t dim2 = 1;
  size_t elCount;

  /**
   * Returns false, if the src isn't a v8 Array/TypedArray
   */
  bool init(v8::Isolate *isolate, const v8::Local<v8::Value> src,
            NSJAllow_Type allowType, size_t argNumber);

  double getDouble(size_t i);
};

/**
 * Abstracts from handling v8 Array/TypedArray methods used for outputting
 * results
 */
class NJSOutputArray {
private:
  v8::Local<v8::ArrayBuffer> array_buffer;

public:
  v8::Local<v8::Object> res;
  bool isTypedArray;
  /** Number of dimensions: 0 - number, 1 - Array/TypedArray, 2 - Matrix */
  size_t nrdims;
  /** Number of elements in the first dimension */
  size_t dim1;
  /** Number of elements in the second dimension */
  size_t dim2;
  size_t elCount;
  size_t recSize;

  void init(v8::Isolate *isolate, NJSArray_Type arrayType, size_t elCount,
            size_t nrdims, size_t dim1, size_t dim2);

  void initFromInput(v8::Isolate *isolate, const NJSInputArray &inputArray);

  inline void initAsMatrix(v8::Isolate *isolate, size_t _dim1, size_t _dim2) {
    init(isolate, typ_MATRIX, _dim1 * _dim2, 2, _dim1, _dim2);
  }

  inline void initAsArray(v8::Isolate *isolate, size_t dim,
                          NJSArray_Type arrayType) {
    init(isolate, arrayType, dim, 1, dim, 1);
  }

  void setFromArray(v8::Isolate *isolate, const njsarray &values,
                    const v8args &args);
};

// ------------------------------------------------------------------------
//                               Input Functions (inputs.cpp)
// ------------------------------------------------------------------------

/**
 * Checks if the number of Arguments is between reqMinArgCount and
 * reqMaxArgCount, if not sends an v8 exception with the errMsg.
 */
bool checkArgCount(v8::Isolate *isolate, const v8args &args,
                   size_t reqMinArgCount, size_t reqMaxArgCount);

bool getBoolInput(v8::Isolate *isolate, const v8args &args,
                  size_t argNumber, bool &outValue, bool required);

bool getIntInput(v8::Isolate *isolate, const v8args &args,
                 size_t argNumber, int &outValue, bool required);

bool getPositiveIntInput(v8::Isolate *isolate, const v8args &args,
                 size_t argNumber, int &outValue, bool required);

int64_t getArgsData(const v8args &args);

// ------------------------------------------------------------------------
//                               Return Functions (returns.cpp)
// ------------------------------------------------------------------------

void returnString(v8::Isolate *isolate, const char *value, const v8args &args);
void returnNumber(v8::Isolate *isolate, double value, const v8args &args);

// ------------------------------------------------------------------------
//                               Tools: tools.cpp
// ------------------------------------------------------------------------

void NODE_SET_METHOD_DATA(v8::Local<v8::Object> recv, const char *name,
                          v8::FunctionCallback callback, int dataValue);

/**
 * Returns true if it's not an infinite or NaN.
 */
bool isValidValue(double x);

inline bool isSingleDim(NJSArray_Type arrayType) {
  return arrayType == typ_ARRAY || arrayType == typ_FLOATARRAY32 ||
         arrayType == typ_FLOATARRAY64;
}

// ------------------------------------------------------------------------
//                                Exception Handling (errors.cpp)
// ------------------------------------------------------------------------

/**
 * Throws a v8 Type Mismatch exception but it doesn't throws a C++ exception.
 */
void returnTypeMismatch(v8::Isolate *isolate, size_t argNumber);

/**
 * Throws a v8 Input Must Be Positive exception but it doesn't throws a C++
 * exception.
 */
void returnMustBePositive(v8::Isolate *isolate, size_t argNumber);

/**
 * Throws a v8 Input Must Same Len exception but it doesn't throws a C++
 * exception.
 */
void returnInputMustSameLen(v8::Isolate *isolate);

/**
 * Throws a v8 Input Must Be Square Matrix exception but it doesn't throws a C++
 * exception.
 */
void returnMustBeSquareMatrix(v8::Isolate *isolate, size_t argNumber);

/**
 * Throws a v8 exception but it doesn't throws a C++ exception.
 */
void returnException(v8::Isolate *isolate, const char *msg, ...);

// ------------------------------------------------------------------------
//                                Handler Functions (handlers.cpp)
// ------------------------------------------------------------------------

struct aggregateParams {
  v8::Isolate *isolate;
  const v8args *args;
  size_t argsLen;
  size_t minParams;
  size_t maxParams;
  // for function usage
  bool boolValue1;
};

/**
 * Receives one array/matrix input, calls calc on each element,
 * and returns one value.
 */
void aggregate1Handler(const v8args &args, double acc,
                       bool(initialize)(aggregateParams &params),
                       double(calc)(double v, double acc),
                       double(finalize)(size_t validLen, double acc,
                                        njsarray &values,
                                        aggregateParams &params),
                       bool reqValues, NSJAllow_Type allowType);

/**
 * Receives two array/matrix input of same dimensions, calls calc on each
 * element, and returns a array/matrix input of the same type as the first
 * input.
 */
void binaryHandler(const v8args &args, double(calc)(double v0, double v1),
                   void(finalize)(size_t validLen, njsarray &values),
                   bool allowNumber0, bool allowNumber1);

#define binaryCalc1DblExpr(funcName, expr, allowNumber0, allowNumber1)         \
  void funcName(const v8args &args) {                                          \
    binaryHandler(args, [](double v0, double v1) { return expr; }, NULL,       \
                  allowNumber0, allowNumber1);                                 \
  }

/**
 * Receives one array/matrix input, calls calc on each element,
 * and returns a array/matrix input of the same type as the input.
 */
void transformHandler(const v8args &args, double(calc)(double v),
                      void(finalize)(size_t validLen, njsarray &values));

#define transfCalc1DblFunc(funcName, func)                                     \
  void funcName(const v8args &args) {                                          \
    transformHandler(args, [](double v) { return func(v); }, NULL);            \
  }

#define transfCalc1DblExpr(funcName, expr)                                     \
  void funcName(const v8args &args) {                                          \
    transformHandler(args, [](double v) { return expr; }, NULL);               \
  }

/**
 * Receives zero array/matrix inputs, and returns a array/matrix input.
 */
void generateHandler(const v8args &args, size_t minArgNumber,
                     size_t maxArgNumber,
                     bool(finalize)(v8::Isolate *isolate, const v8args &args,
                                    njsarray &values,
                                    NJSOutputArray &outArray));

class NArrayInputs {
public:
  v8::Isolate *isolate;
  size_t numInputs;
  const v8args *argsp;

  std::vector<v8::Local<v8::Value>> valueArgs;
  std::vector<NJSInputArray> inputs;
  std::vector<njsarray> valuesList;
  std::vector<size_t> validLenList;

  NArrayInputs(const v8args &args) { argsp = &args; }

  njsarray outValues;

  bool init(v8::Isolate *isolate, const v8args &args, size_t numInputs,
            NSJAllow_Type *allowTypes);
  void loadData();

  inline void returnAsNumber(double outValue) {
    returnNumber(isolate, outValue, *argsp);
  }

  inline void returnAsArray(const njsarray &outValues,
                            NJSArray_Type arrayType) {
    NJSOutputArray outArray;
    outArray.initAsArray(isolate, outValues.size(), arrayType);
    outArray.setFromArray(isolate, outValues, *argsp);
  }
};

/**
 * Receives N array/matrix input, calls op after all inputs are loaded,
 * and returns either the same as first input or defined in the retType.
 */
void nInputsHandler(const v8args &args, size_t numInputs, size_t extraArgs,
                    NSJAllow_Type *allowTypes,
                    bool(op)(NArrayInputs &naInputs));

// ------------------------------------------------------------------------
//                               Initialize Functions
// ------------------------------------------------------------------------

/**
 * Initializes Trigonometric functions.
 */
void initializeTrigonometric(v8exports exports);

/**
 * Initializes Hyperbolic functions.
 */
void initializeHyperbolic(v8exports exports);

/**
 * Initializes Rounding functions.
 */
void initializeRounding(v8exports exports);

/**
 * Initializes Sums, products, differences functions.
 */
void initializeSums(v8exports exports);

/**
 * Initializes Exponents and Logs functions.
 */
void initializeExpLogs(v8exports exports);

/**
 * Initializes Arithmetic functions.
 */
void initializeArithmetic(v8exports exports);

/**
 * Initializes Miscellaneous functions.
 */
void initializeMiscellaneous(v8exports exports);

/**
 * Initializes Matrix functions.
 */
void initializeMatrix(v8exports exports);

/**
 * Initializes Statistical functions.
 */
void initializeStatistics(v8exports exports);

} // namespace numnjs