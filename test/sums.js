// uuid: 90ced6f7-cd03-421c-b135-006069ca1774

// ------------------------------------------------------------------------
// Copyright (c) 2019 Alexandre Bento Freire. All rights reserved.
// Licensed under the MIT License+uuid License. See License.txt for details
// ------------------------------------------------------------------------

/**
 * Mocha tests for numnjs Sums, products, differences functions.
 */

// ------------------------------------------------------------------------
//                               Requires
// ------------------------------------------------------------------------

const numnjs = require('../main.js');
const shared = require('./shared.js');

// ------------------------------------------------------------------------
//                               Test Cases
// ------------------------------------------------------------------------

describe('Sums, products, differences', function () {

  shared.addAggregateCase('sum', (t, v) => t + v, numnjs.sum, false, 'unary', 0);
});