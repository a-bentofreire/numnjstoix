// ------------------------------------------------------------------------
// Copyright (c) 2019-2024 Alexandre Bento Freire. All rights reserved.
// Licensed under the MIT License
// ------------------------------------------------------------------------

/**
 * Mocha tests for numnjstoix Exponents and logarithms functions.
 */

// ------------------------------------------------------------------------
//                               Requires
// ------------------------------------------------------------------------

import { numnjstoix } from '../main.js';
import * as shared from './shared.js';

// ------------------------------------------------------------------------
//                               Test Cases
// ------------------------------------------------------------------------

describe('Exponents and logarithms', function () {

  shared.addTransformCase(describe, 'exp', Math.exp, numnjstoix.exp, true);
  shared.addTransformCase(describe, 'expm1', Math.expm1, numnjstoix.expm1, true);
  shared.addTransformCase(describe, 'exp2', (v) => Math.pow(2, v), numnjstoix.exp2, true);

  shared.addTransformCase(describe, 'log', Math.log, numnjstoix.log, true);
  shared.addTransformCase(describe, 'log10', Math.log10, numnjstoix.log10, true);
  shared.addTransformCase(describe, 'log2', Math.log2, numnjstoix.log2, true);
});