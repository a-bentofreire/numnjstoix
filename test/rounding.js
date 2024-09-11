// ------------------------------------------------------------------------
// Copyright (c) 2019-2024 Alexandre Bento Freire. All rights reserved.
// Licensed under the MIT License
// ------------------------------------------------------------------------

/**
 * Mocha tests for numnjstoix Rounding functions.
 */

// ------------------------------------------------------------------------
//                               Requires
// ------------------------------------------------------------------------

import { numnjstoix } from '../main.js';
import * as shared from './shared.js';

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

  shared.addTransformCase(describe, 'round', Math.round, numnjstoix.round, true);
  shared.addTransformCase(describe, 'floor', Math.floor, numnjstoix.floor, true);
  shared.addTransformCase(describe, 'ceil', Math.ceil, numnjstoix.ceil, true);
});