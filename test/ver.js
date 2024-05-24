// ------------------------------------------------------------------------
// Copyright (c) 2019-2024 Alexandre Bento Freire. All rights reserved.
// Licensed under the MIT License
// ------------------------------------------------------------------------

/**
 * Mocha tests for numnjs version function.
 */

// ------------------------------------------------------------------------
//                               Requires
// ------------------------------------------------------------------------

const numnjs = require('../main.js');
const fs = require('fs');
const assert = require('chai').assert;

// ------------------------------------------------------------------------
//                               Test Cases
// ------------------------------------------------------------------------

describe('Version', function () {

  describe('value', function () {

    it(`should match package.json version`, function (done) {
      const packageContent = fs.readFileSync('./package.json', 'utf8');
      const versionTokens = packageContent.match('"version"[^0-9]+([0-9\.]+)');
      const expected = versionTokens[1];
      const actual = numnjs.ver();
      assert.equal(expected, actual);
      done();
    });
  });
});