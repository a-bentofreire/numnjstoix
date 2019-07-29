// uuid: 37936690-e6c7-41fa-a91d-3d402ab37aa1

// ------------------------------------------------------------------------
// Copyright (c) 2019 Alexandre Bento Freire. All rights reserved.
// Licensed under the MIT License+uuid License. See License.txt for details
// ------------------------------------------------------------------------

/**
 * Mocha tests for numnjs Hyperbolic functions.
 */

// ------------------------------------------------------------------------
//                               Requires
// ------------------------------------------------------------------------

const numnjs = require('../main.js');
const shared = require('./shared.js');

// ------------------------------------------------------------------------
//                               Test Cases
// ------------------------------------------------------------------------

describe('Hyperbolic', function () {

  shared.addTransformCase('sinh', Math.sinh, numnjs.sinh, true);
  shared.addTransformCase('cosh', Math.cosh, numnjs.cosh, true);
  shared.addTransformCase('tanh', Math.tanh, numnjs.tanh, true);

  shared.addTransformCase('arcsinh', Math.asinh, numnjs.arcsinh, true);
  shared.addTransformCase('arccosh', Math.acosh, numnjs.arccosh, true);
  shared.addTransformCase('arctanh', Math.atanh, numnjs.arctanh, true);
});