// uuid: d21ecb5d-3961-4a04-bd5d-71fd6a6825b2

// ------------------------------------------------------------------------
// Copyright (c) 2019 Alexandre Bento Freire. All rights reserved.
// Licensed under the MIT License+uuid License. See License.txt for details
// ------------------------------------------------------------------------

/**
 * Mocha tests for numnjs aggregate functions.
 */

// ------------------------------------------------------------------------
//                               Requires
// ------------------------------------------------------------------------

const numnjs = require('../main.js');
const shared = require('./shared.js');

// ------------------------------------------------------------------------
//                               Expected Functions
// ------------------------------------------------------------------------

function averageFunc(values) {
  return shared.aggregate1Handler(values, (t, v) => t + v, 0) / shared.safeLength(values);
}

function subCalcMoment(values, power) {
  const avg = averageFunc(values);
  return shared.aggregate1Handler(values, (t, v) => t + Math.pow(v - avg, power), 0) / shared.safeLength(values);
}

function varFunc(values) {
  return subCalcMoment(values, 2);
}

function stdFunc(values) {
  return Math.sqrt(subCalcMoment(values, 2));
}

function kurtosisFunc(values) {
  return subCalcMoment(values, 4) / Math.pow(varFunc(values), 2);
}

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

describe('Statistics', function () {

  shared.addCase('average', averageFunc, numnjs.average, false, 'statistics');
  shared.addCase('var', varFunc, numnjs.var, false, 'statistics');
  shared.addCase('std', stdFunc, numnjs.std, false, 'statistics');
  shared.addCase('kurtosis', kurtosisFunc, numnjs.kurtosis, true, 'statistics');
  shared.addCase('kurtosis-fisher',
    (v) => kurtosisFunc(v) - 3,
    (v) => numnjs.kurtosis(v, true),
    true, 'statistics');
  shared.addCase('cov', covFunc, numnjs.cov, true, 'statistics-binary');

});