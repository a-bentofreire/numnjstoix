// ------------------------------------------------------------------------
// Copyright (c) 2019-2024 Alexandre Bento Freire. All rights reserved.
// Licensed under the MIT License
// ------------------------------------------------------------------------

/**
 * Mocha tests for numnjstoix trigonometric functions.
 */

// ------------------------------------------------------------------------
//                               Requires
// ------------------------------------------------------------------------

import { numnjstoix } from '../main.js';
import * as shared from './shared.js';

// ------------------------------------------------------------------------
//                               Test Cases
// ------------------------------------------------------------------------

describe('Trigonometric', function () {

  shared.addTransformCase(describe, 'sin', Math.sin, numnjstoix.sin, true);
  shared.addTransformCase(describe, 'cos', Math.cos, numnjstoix.cos, true);
  shared.addTransformCase(describe, 'tan', Math.tan, numnjstoix.tan, true);

  shared.addTransformCase(describe, 'arcsin', Math.asin, numnjstoix.arcsin, true);
  shared.addTransformCase(describe, 'arccos', Math.acos, numnjstoix.arccos, true);
  shared.addTransformCase(describe, 'arctan', Math.atan, numnjstoix.arctan, true);

  shared.addTransformCase(describe, 'degrees', (v) => v * (180 / Math.PI), numnjstoix.degrees, true);
  shared.addTransformCase(describe, 'radians', (v) => v / (180 / Math.PI), numnjstoix.radians, true);
});