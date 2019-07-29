// uuid: 5780427e-ffb3-4721-a0e1-7ba3797a555b

// ------------------------------------------------------------------------
// Copyright (c) 2019 Alexandre Bento Freire. All rights reserved.
// Licensed under the MIT License+uuid License. See License.txt for details
// ------------------------------------------------------------------------

/**
 * Mocha tests for numnjs Rounding functions.
 */

// ------------------------------------------------------------------------
//                               Requires
// ------------------------------------------------------------------------

const numnjs = require('../main.js');
const shared = require('./shared.js');

// ------------------------------------------------------------------------
//                               Expected Functions
// ------------------------------------------------------------------------

function covFunc(values0, values1) {
  const avg0 = averageFunc(values0);
  const avg1 = averageFunc(values1);
  const safeLen = shared.safeLength(values0);
  const v1 = shared.safeCalc2(values0, values1, (v0, v1) => (v0 - avg0) * (v1 - avg1));
  const v2 = v1.reduce((acc, v) => acc + (shared.isValidValue(v) ? v : 0));
  return v2 / (safeLen - 1);
}

// ------------------------------------------------------------------------
//                               Test Cases
// ------------------------------------------------------------------------

describe('Rounding', function () {

  shared.addTransformCase('round', Math.round, numnjs.round, true);
  shared.addTransformCase('floor', Math.floor, numnjs.floor, true);
  shared.addTransformCase('ceil', Math.ceil, numnjs.ceil, true);
});