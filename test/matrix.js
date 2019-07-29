// uuid: a15747ee-4b4b-4019-9585-0a7961aa0a0b

// ------------------------------------------------------------------------
// Copyright (c) 2019 Alexandre Bento Freire. All rights reserved.
// Licensed under the MIT License+uuid License. See License.txt for details
// ------------------------------------------------------------------------

/**
 * Mocha tests for numnjs trigonometric functions.
 */

// ------------------------------------------------------------------------
//                               Requires
// ------------------------------------------------------------------------

const numnjs = require('../main.js');
const shared = require('./shared.js');

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
  return buildMatrix(d, d, (_i, _j) =>  1);
}

function zerosFunc(d) {
  return buildMatrix(d, d, (_i, _j) =>  0);
}

// ------------------------------------------------------------------------
//                               Test Cases
// ------------------------------------------------------------------------

describe('Matrix', function () {

  shared.addCase('diagonal', diagonalFunc, numnjs.diagonal, true, 'diagonal');
  shared.addCase('eye', eyeFunc, numnjs.eye, true, 'dim1');
  shared.addCase('ones', onesFunc, numnjs.ones, true, 'dim2');
  shared.addCase('zeros', zerosFunc, numnjs.zeros, true, 'dim2');
});