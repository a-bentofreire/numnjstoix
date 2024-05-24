// ------------------------------------------------------------------------
// Copyright (c) 2019-2024 Alexandre Bento Freire. All rights reserved.
// Licensed under the MIT License
// ------------------------------------------------------------------------

/**
 * Common helper functions to be used mocha test files.
 */

const ROUND_FACTOR = 100/* 0000 */;

// ------------------------------------------------------------------------
//                               Requires
// ------------------------------------------------------------------------

const assert = require('chai').assert;
const sampleData = require('./sample-data.js');

// ------------------------------------------------------------------------
//                               Tools
// ------------------------------------------------------------------------

/**
 * Returns true, if it's not infinite, NaN or undefined.
 */
exports.isValidValue = function (v) {
  return (v !== undefined) && isFinite(v) && !isNaN(v);
};

/**
 * Rounds a value based `ROUND_FACTOR` if it's a valid value.
 */
exports.safeRound = function (v) {
  return exports.isValidValue(v) ? Math.round(v * ROUND_FACTOR) / ROUND_FACTOR : v;
}

/**
 * Rounds inplace each value of Array, TypedArray or Matrix.
 */
exports.roundNjsArray = function (a) {
  const len = a.length;
  if (!exports.isMatrix(a)) {
    for (var i = 0; i < len; i++) {
      a[i] = exports.safeRound(a[i]);
    }
  } else {
    const dim2 = a[0].length;
    for (var i = 0; i < len; i++) {
      for (var j = 0; j < dim2; j++) {
        a[i][j] = exports.safeRound(a[i][j]);
      }
    }
  }
};

/**
 * Returns True if `a` is Array, TypedArray or Matrix (Array of Array).
 */
exports.isNjsArray = function (a) {
  return a !== undefined && (Array.isArray(a) ||
    (typeof a === 'object' && a.BYTES_PER_ELEMENT !== undefined));
};

/**
 * Returns True if `a` is Array or TypedArray.
 */
exports.isSingleDim = function (a) {
  return a !== exports.isNjsArray(a) && !exports.isMatrix(a);
};

/**
 * Returns True if it's a Matrix (Array of Array).
 */
exports.isMatrix = function (a) {
  return a !== undefined && Array.isArray(a) && a.length > 0 && Array.isArray(a[0]);
};

exports.aggregate1Handler = function (values, f, initialValue) {
  const len = values.length;
  if (!exports.isMatrix(values)) {
    return values.reduce((acc, v) => exports.isValidValue(v) ? f(acc, v) : acc, initialValue);
  } else {
    const dim2 = values[0].length;
    let acc = 0;
    for (var i = 0; i < len; i++) {
      for (var j = 0; j < dim2; j++) {
        let v = values[i][j];
        acc = exports.isValidValue(v) ? f(acc, v) : acc, initialValue;
      }
    }
    return acc;
  }
}

// ------------------------------------------------------------------------
//                               Runners
// ------------------------------------------------------------------------

exports.safeLength = function (values) {
  return values.reduce((t, v) => exports.isValidValue(v) ? t + 1 : t, 0);
}

exports.safeCallF = function (v0, v1, f) {
  return exports.isValidValue(v0) && exports.isValidValue(v1) ? f(v0, v1) : v0;
}

exports.safeCalc = function (values, f) {
  return values.map((v) => exports.isValidValue(v) ? f(v) : v);
}

exports.safeCalc2 = function (values0, values1, f) {
  const isMatrix = exports.isMatrix(values0) || exports.isMatrix(values1);
  const isNumber0 = typeof values0 == 'number';
  const isNumber1 = typeof values1 == 'number';

  return !isNumber0 ?
    values0.map((v0, i) => !isMatrix ?
      exports.safeCallF(v0, !isNumber1 ? values1[i] : values1, f, i) :
      exports.safeCalc2(v0, !isNumber1 ? values1[i] : values1, f)
    ) :
    values1.map((v1) => !isMatrix ?
      exports.safeCallF(values0, v1, f) : exports.safeCalc2(values0, v1, f)
    );
}

// ------------------------------------------------------------------------
//                               Mocha Test Functions
// ------------------------------------------------------------------------

exports.addTransformCase = function (label, expectValueFunc, actualFunc, toRound, tag = 'unary') {
  exports.addCase(label, (values) => {
    return exports.safeCalc(values, (v) => expectValueFunc(v));
  }, actualFunc, toRound, tag);
}

exports.addBinaryCase = function (label, actualValueFunc, expectFunc, toRound, tag) {
  exports.addCase(label, (values0, values1) => {
    return exports.safeCalc2(values0, values1, (v0, v1) => actualValueFunc(v0, v1));
  }, expectFunc, toRound, tag);
}

exports.addAggregateCase = function (label, actualValueFunc, expectFunc, toRound, tag, acc) {
  exports.addCase(label, (values) => {
    return exports.aggregate1Handler(values, (t, v) => actualValueFunc(t, v), acc)
  }, expectFunc, toRound, tag);
}

// exports.nInputsCase = function (label, actualValueFunc, expectFunc, toRound, tag, acc) {
//   exports.addCase(label, (values) => {
//     return exports.aggregate1Handler(values, (t, v) => actualValueFunc(t, v), acc)
//   }, expectFunc, toRound, tag);
// }


/**
 * Adds a mocha test case, where the each input value is tested.
 */
exports.addCase = function (label, actualFunc, expectFunc, toRound, tag) {
  describe(label, function () {

    sampleData.input.forEach(sample => {

      if (sample.tags.indexOf(tag) === -1) {
        return;
      }

      it(`should pass ${label} ${sample.label}`, function (done) {
        let expect;
        let actual;
        const p = [];
        let argNr = 0;
        while(true) {
          const v = sample[`p${argNr}`];
          if (v === undefined) {
            break;
          }
          p.push(v);
          argNr++;
        };
        expect = actualFunc(...p);
        actual = expectFunc(...p);

        // since mocha equal won't match Array with TypedArray elements,
        // therefore it must be matched individual elements
        if (exports.isNjsArray(expect)) {

          const len = expect.length;
          for (var i = 0; i < len; i++) {
            let ei = expect[i];
            let ai = actual[i];
            if (toRound) {
              ei = exports.safeRound(ei);
              ai = exports.safeRound(ai);
            }
            if (exports.isValidValue(ei)) {
              assert.equal(ei, ai, `Index ${i} failed`);
            } else {
              assert.isOk(!exports.isValidValue(ai), `Index ${i} failed`);
            }
          }

        } else {
          if (toRound) {
            expect = exports.safeRound(expect);
            actual = exports.safeRound(actual);
          }
          assert.equal(expect, actual);
        }
        done();
      });
    });


    it(`should throw Exception on zeroParams`, function (done) {
      assert.Throw(expectFunc);
      done();
    });

    it(`should throw Exception on string param`, function (done) {
      assert.Throw(() => expectFunc('hello'));
      done();
    });
  });
}