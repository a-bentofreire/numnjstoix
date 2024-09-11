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

import { assert } from 'chai';
import sampleData from './sample-data.js';

// ------------------------------------------------------------------------
//                               Tools
// ------------------------------------------------------------------------

/**
 * Returns true, if it's not infinite, NaN or undefined.
 */
function isValidValue(v) {
    return (v !== undefined) && isFinite(v) && !isNaN(v);
};

/**
 * Rounds a value based `ROUND_FACTOR` if it's a valid value.
 */
function safeRound(v) {
    return isValidValue(v) ? Math.round(v * ROUND_FACTOR) / ROUND_FACTOR : v;
}

/**
 * Rounds inplace each value of Array, TypedArray or Matrix.
 */
function roundNjsArray(a) {
    const len = a.length;
    if (!isMatrix(a)) {
        for (var i = 0; i < len; i++) {
            a[i] = safeRound(a[i]);
        }
    } else {
        const dim2 = a[0].length;
        for (var i = 0; i < len; i++) {
            for (var j = 0; j < dim2; j++) {
                a[i][j] = safeRound(a[i][j]);
            }
        }
    }
};

/**
 * Returns True if `a` is Array, TypedArray or Matrix (Array of Array).
 */
function isNjsArray(a) {
    return a !== undefined && (Array.isArray(a) ||
        (typeof a === 'object' && a.BYTES_PER_ELEMENT !== undefined));
};

/**
 * Returns True if `a` is Array or TypedArray.
 */
function isSingleDim(a) {
    return a !== isNjsArray(a) && !isMatrix(a);
};

/**
 * Returns True if it's a Matrix (Array of Array).
 */
function isMatrix(a) {
    return a !== undefined && Array.isArray(a) && a.length > 0 && Array.isArray(a[0]);
};

function aggregate1Handler(values, f, initialValue) {
    const len = values.length;
    if (!isMatrix(values)) {
        return values.reduce((acc, v) => isValidValue(v) ? f(acc, v) : acc, initialValue);
    } else {
        const dim2 = values[0].length;
        let acc = 0;
        for (var i = 0; i < len; i++) {
            for (var j = 0; j < dim2; j++) {
                let v = values[i][j];
                acc = isValidValue(v) ? f(acc, v) : acc, initialValue;
            }
        }
        return acc;
    }
}

// ------------------------------------------------------------------------
//                               Runners
// ------------------------------------------------------------------------

function safeLength(values) {
    return values.reduce((t, v) => isValidValue(v) ? t + 1 : t, 0);
}

function safeCallF(v0, v1, f) {
    return isValidValue(v0) && isValidValue(v1) ? f(v0, v1) : v0;
}

function safeCalc(values, f) {
    return values.map((v) => isValidValue(v) ? f(v) : v);
}

function safeCalc2(values0, values1, f) {
    const isMatrix2 = isMatrix(values0) || isMatrix(values1);
    const isNumber0 = typeof values0 == 'number';
    const isNumber1 = typeof values1 == 'number';

    return !isNumber0 ?
        values0.map((v0, i) => !isMatrix2 ?
            safeCallF(v0, !isNumber1 ? values1[i] : values1, f, i) :
            safeCalc2(v0, !isNumber1 ? values1[i] : values1, f)
        ) :
        values1.map((v1) => !isMatrix2 ?
            safeCallF(values0, v1, f) : safeCalc2(values0, v1, f)
        );
}

// ------------------------------------------------------------------------
//                               Mocha Test Functions
// ------------------------------------------------------------------------

function addTransformCase(describe, label, expectValueFunc, actualFunc, toRound, tag = 'unary') {
    addCase(describe, label, (values) => {
        return safeCalc(values, (v) => expectValueFunc(v));
    }, actualFunc, toRound, tag);
}

function addBinaryCase(describe, label, actualValueFunc, expectFunc, toRound, tag) {
    addCase(describe, label, (values0, values1) => {
        return safeCalc2(values0, values1, (v0, v1) => actualValueFunc(v0, v1));
    }, expectFunc, toRound, tag);
}

function addAggregateCase(describe, label, actualValueFunc, expectFunc, toRound, tag, acc) {
    addCase(describe, label, (values) => {
        return aggregate1Handler(values, (t, v) => actualValueFunc(t, v), acc)
    }, expectFunc, toRound, tag);
}

// function nInputsCase (label, actualValueFunc, expectFunc, toRound, tag, acc) {
//   addCase(describe, label, (values) => {
//     return aggregate1Handler(values, (t, v) => actualValueFunc(t, v), acc)
//   }, expectFunc, toRound, tag);
// }


/**
 * Adds a mocha test case, where the each input value is tested.
 */
function addCase(describe, label, actualFunc, expectFunc, toRound, tag) {
    describe(label, function () {

        sampleData.forEach(sample => {

            if (sample.tags.indexOf(tag) === -1) {
                return;
            }

            it(`should pass ${label} ${sample.label}`, function (done) {
                let expect;
                let actual;
                const p = [];
                let argNr = 0;
                while (true) {
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
                if (isNjsArray(expect)) {

                    const len = expect.length;
                    for (var i = 0; i < len; i++) {
                        let ei = expect[i];
                        let ai = actual[i];
                        if (toRound) {
                            ei = safeRound(ei);
                            ai = safeRound(ai);
                        }
                        if (isValidValue(ei)) {
                            assert.equal(ei, ai, `Index ${i} failed`);
                        } else {
                            assert.isOk(!isValidValue(ai), `Index ${i} failed`);
                        }
                    }

                } else {
                    if (toRound) {
                        expect = safeRound(expect);
                        actual = safeRound(actual);
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

export {
    isValidValue,
    safeRound,
    roundNjsArray,
    isNjsArray,
    isSingleDim,
    isMatrix,
    aggregate1Handler,
    safeLength,
    safeCallF,
    safeCalc,
    safeCalc2,
    addTransformCase,
    addBinaryCase,
    addAggregateCase,
    // nInputsCase,
    addCase
};