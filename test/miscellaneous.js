// uuid: ea5e56e0-4d5b-45d2-b6cb-9e16318ecd97

// ------------------------------------------------------------------------
// Copyright (c) 2019 Alexandre Bento Freire. All rights reserved.
// Licensed under the MIT License+uuid License. See License.txt for details
// ------------------------------------------------------------------------

/**
 * Mocha tests for numnjs Miscellaneous functions.
 */

// ------------------------------------------------------------------------
//                               Requires
// ------------------------------------------------------------------------

const numnjs = require('../main.js');
const shared = require('./shared.js');

// ------------------------------------------------------------------------
//                               Test Cases
// ------------------------------------------------------------------------

describe('Miscellaneous', function () {

  shared.addTransformCase('sqrt', Math.sqrt, numnjs.sqrt, true);
  shared.addTransformCase('cbrt', Math.cbrt, numnjs.cbrt, true);
  shared.addTransformCase('square', (v) => v * v, numnjs.square, true);
  shared.addTransformCase('sign', Math.sign, numnjs.sign, true);
  shared.addTransformCase('abs', Math.abs, numnjs.abs, true);
  shared.addBinaryCase('maximum', (v0, v1) => Math.max(v0, v1), numnjs.maximum, true, 'binary');
  shared.addBinaryCase('minimum', (v0, v1) => Math.min(v0, v1), numnjs.minimum, true, 'binary');
  shared.addAggregateCase('max', Math.max, numnjs.max, false, 'unary', Number.MIN_VALUE);
  shared.addAggregateCase('min', Math.min, numnjs.min, false, 'unary', Number.MAX_VALUE);
});