// ------------------------------------------------------------------------
// Copyright (c) 2019-2024 Alexandre Bento Freire. All rights reserved.
// Licensed under the MIT License
// ------------------------------------------------------------------------

/**
 * Mocha tests for numnjstoix Sums, products, differences functions.
 */

// ------------------------------------------------------------------------
//                               Requires
// ------------------------------------------------------------------------

import { numnjstoix } from '../main.js';
import * as shared from './shared.js';

// ------------------------------------------------------------------------
//                               Test Cases
// ------------------------------------------------------------------------

describe('Sums, products, differences', function () {

  shared.addAggregateCase(describe, 'sum', (t, v) => t + v, numnjstoix.sum, false, 'unary', 0);
});