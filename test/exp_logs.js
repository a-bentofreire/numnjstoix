// uuid: bc13a9a3-10b0-4df8-90e9-27ca1088d255

// ------------------------------------------------------------------------
// Copyright (c) 2019 Alexandre Bento Freire. All rights reserved.
// Licensed under the MIT License+uuid License. See License.txt for details
// ------------------------------------------------------------------------

/**
 * Mocha tests for numnjs Exponents and logarithms functions.
 */

// ------------------------------------------------------------------------
//                               Requires
// ------------------------------------------------------------------------

const numnjs = require('../main.js');
const shared = require('./shared.js');

// ------------------------------------------------------------------------
//                               Test Cases
// ------------------------------------------------------------------------

describe('Exponents and logarithms', function () {

  shared.addTransformCase('exp', Math.exp, numnjs.exp, true);
  shared.addTransformCase('expm1', Math.expm1, numnjs.expm1, true);
  shared.addTransformCase('exp2', (v) => Math.pow(2, v), numnjs.exp2, true);

  shared.addTransformCase('log', Math.log, numnjs.log, true);
  shared.addTransformCase('log10', Math.log10, numnjs.log10, true);
  shared.addTransformCase('log2', Math.log2, numnjs.log2, true);
});