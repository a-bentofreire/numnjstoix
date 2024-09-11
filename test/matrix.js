// ------------------------------------------------------------------------
// Copyright (c) 2019-2024 Alexandre Bento Freire. All rights reserved.
// Licensed under the MIT License
// ------------------------------------------------------------------------

/**
 * Mocha tests for numnjstoix trigonometric functions.
 */

// ------------------------------------------------------------------------
//                               Requires
// ------------------------------------------------------------------------

import { numnjstoix } from '../main.js';
import * as shared from './shared.js';

function diagonalFunc(values) {
    const outValues = [];
    values.forEach((row, i) => {
        outValues.push(row[i]);
    });
    return outValues;
}

function buildMatrix(d1, d2, f) {
    const out = [];
    for (let i = 0; i < d1; i++) {
        const row = [];
        for (let j = 0; j < d2; j++) {
            row.push(f(i, j));
        }
        out.push(row);
    }
    return out;
}

function eyeFunc(d) {
    return buildMatrix(d, d, (i, j) => i === j ? 1 : 0);
}

function onesFunc(d) {
    return buildMatrix(d, d, (_i, _j) => 1);
}

function zerosFunc(d) {
    return buildMatrix(d, d, (_i, _j) => 0);
}

// ------------------------------------------------------------------------
//                               Test Cases
// ------------------------------------------------------------------------

describe('Matrix', function () {

    shared.addCase(describe, 'diagonal', diagonalFunc, numnjstoix.diagonal, true, 'diagonal');
    shared.addCase(describe, 'eye', eyeFunc, numnjstoix.eye, true, 'dim1');
    shared.addCase(describe, 'ones', onesFunc, numnjstoix.ones, true, 'dim2');
    shared.addCase(describe, 'zeros', zerosFunc, numnjstoix.zeros, true, 'dim2');
});