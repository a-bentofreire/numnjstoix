// ------------------------------------------------------------------------
// Copyright (c) 2019-2024 Alexandre Bento Freire. All rights reserved.
// Licensed under the MIT License
// ------------------------------------------------------------------------

/**
 * Mocha tests for numnjstoix Hyperbolic functions.
 */

// ------------------------------------------------------------------------
//                               Requires
// ------------------------------------------------------------------------

import { numnjstoix } from '../main.js';
import * as shared from './shared.js';

// ------------------------------------------------------------------------
//                               Test Cases
// ------------------------------------------------------------------------

describe('Hyperbolic', function () {

  shared.addTransformCase(describe, 'sinh', Math.sinh, numnjstoix.sinh, true);
  shared.addTransformCase(describe, 'cosh', Math.cosh, numnjstoix.cosh, true);
  shared.addTransformCase(describe, 'tanh', Math.tanh, numnjstoix.tanh, true);

  shared.addTransformCase(describe, 'arcsinh', Math.asinh, numnjstoix.arcsinh, true);
  shared.addTransformCase(describe, 'arccosh', Math.acosh, numnjstoix.arccosh, true);
  shared.addTransformCase(describe, 'arctanh', Math.atanh, numnjstoix.arctanh, true);
});