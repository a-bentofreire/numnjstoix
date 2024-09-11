// ------------------------------------------------------------------------
// Copyright (c) 2019-2024 Alexandre Bento Freire. All rights reserved.
// Licensed under the MIT License
// ------------------------------------------------------------------------

/**
 * Mocha tests for numnjstoix binary functions.
 */

// ------------------------------------------------------------------------
//                               Requires
// ------------------------------------------------------------------------

import { numnjstoix } from '../main.js';
import * as shared from './shared.js';

// ------------------------------------------------------------------------
//                               Test Cases
// ------------------------------------------------------------------------

describe('Arithmetic', function () {

  shared.addBinaryCase(describe, 'add', (v0, v1) => v0 + v1, numnjstoix.add, true, 'binary');
  shared.addTransformCase(describe, 'reciprocal', (v) => 1 / v, numnjstoix.reciprocal, true);
  shared.addTransformCase(describe, 'negative', (v) => -v, numnjstoix.negative, true);
  shared.addBinaryCase(describe, 'multiply', (v0, v1) => v0 * v1, numnjstoix.multiply, true, 'multiply');
  shared.addBinaryCase(describe, 'divide', (v0, v1) => v0 / v1, numnjstoix.divide, true, 'divide');
  shared.addBinaryCase(describe, 'power', (v0, v1) => Math.pow(v0, v1), numnjstoix.power, true, 'binary');
  shared.addBinaryCase(describe, 'subtract', (v0, v1) => v0 - v1, numnjstoix.subtract, true, 'binary');
  shared.addBinaryCase(describe, 'mod', (v0, v1) => v0 % v1, numnjstoix.mod, true, 'binary');

});