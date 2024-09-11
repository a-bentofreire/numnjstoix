// ------------------------------------------------------------------------
// Copyright (c) 2019-2024 Alexandre Bento Freire. All rights reserved.
// Licensed under the MIT License
// ------------------------------------------------------------------------

/**
 * Mocha tests for numnjstoix Miscellaneous functions.
 */

// ------------------------------------------------------------------------
//                               Requires
// ------------------------------------------------------------------------

import { numnjstoix } from '../main.js';
import * as shared from './shared.js';

// ------------------------------------------------------------------------
//                               Test Cases
// ------------------------------------------------------------------------

describe('Miscellaneous', function () {

  shared.addTransformCase(describe, 'sqrt', Math.sqrt, numnjstoix.sqrt, true);
  shared.addTransformCase(describe, 'cbrt', Math.cbrt, numnjstoix.cbrt, true);
  shared.addTransformCase(describe, 'square', (v) => v * v, numnjstoix.square, true);
  shared.addTransformCase(describe, 'sign', Math.sign, numnjstoix.sign, true);
  shared.addTransformCase(describe, 'abs', Math.abs, numnjstoix.abs, true);
  shared.addBinaryCase(describe, 'maximum', (v0, v1) => Math.max(v0, v1), numnjstoix.maximum, true, 'binary');
  shared.addBinaryCase(describe, 'minimum', (v0, v1) => Math.min(v0, v1), numnjstoix.minimum, true, 'binary');
  shared.addAggregateCase(describe, 'max', Math.max, numnjstoix.max, false, 'unary', Number.MIN_VALUE);
  shared.addAggregateCase(describe, 'min', Math.min, numnjstoix.min, false, 'unary', Number.MAX_VALUE);
});