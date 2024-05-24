// ------------------------------------------------------------------------
// Copyright (c) 2019-2024 Alexandre Bento Freire. All rights reserved.
// Licensed under the MIT License
// ------------------------------------------------------------------------

/**
 * Mocha tests for numnjs binary functions.
 */

// ------------------------------------------------------------------------
//                               Requires
// ------------------------------------------------------------------------

const numnjs = require('../main.js');
const shared = require('./shared.js');

// ------------------------------------------------------------------------
//                               Test Cases
// ------------------------------------------------------------------------

describe('Arithmetic', function () {

  shared.addBinaryCase('add', (v0, v1) => v0 + v1, numnjs.add, true, 'binary');
  shared.addTransformCase('reciprocal', (v) => 1 / v, numnjs.reciprocal, true);
  shared.addTransformCase('negative', (v) => -v, numnjs.negative, true);
  shared.addBinaryCase('multiply', (v0, v1) => v0 * v1, numnjs.multiply, true, 'multiply');
  shared.addBinaryCase('divide', (v0, v1) => v0 / v1, numnjs.divide, true, 'divide');
  shared.addBinaryCase('power', (v0, v1) => Math.pow(v0, v1), numnjs.power, true, 'binary');
  shared.addBinaryCase('subtract', (v0, v1) => v0 - v1, numnjs.subtract, true, 'binary');
  shared.addBinaryCase('mod', (v0, v1) => v0 % v1, numnjs.mod, true, 'binary');

});