// ------------------------------------------------------------------------
// Copyright (c) 2019-2024 Alexandre Bento Freire. All rights reserved.
// Licensed under the MIT License
// ------------------------------------------------------------------------

/**
 * Mocha tests for numnjstoix aggregate functions.
 */

// ------------------------------------------------------------------------
//                               Requires
// ------------------------------------------------------------------------

import { numnjstoix } from '../main.js';
import * as shared from './shared.js';

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

  shared.addCase(describe, 'average', averageFunc, numnjstoix.average, false, 'statistics');
  shared.addCase(describe, 'var', varFunc, numnjstoix.var, false, 'statistics');
  shared.addCase(describe, 'std', stdFunc, numnjstoix.std, false, 'statistics');
  shared.addCase(describe, 'kurtosis', kurtosisFunc, numnjstoix.kurtosis, true, 'statistics');
  shared.addCase(describe, 'kurtosis-fisher',
    (v) => kurtosisFunc(v) - 3,
    (v) => numnjstoix.kurtosis(v, true),
    true, 'statistics');
  shared.addCase(describe, 'cov', covFunc, numnjstoix.cov, true, 'statistics-binary');

});