// ------------------------------------------------------------------------
// Copyright (c) 2019-2024 Alexandre Bento Freire. All rights reserved.
// Licensed under the MIT License
// ------------------------------------------------------------------------

/**
 * Mocha tests for numnjstoix version function.
 */

// ------------------------------------------------------------------------
//                               Requires
// ------------------------------------------------------------------------

import * as  fs from 'fs';
import { assert } from 'chai';
import { numnjstoix } from '../main.js';

// ------------------------------------------------------------------------
//                               Test Cases
// ------------------------------------------------------------------------

describe('Version', function () {

    describe('value', function () {

        it(`should match package.json version`, function (done) {
            const packageContent = fs.readFileSync('./package.json', 'utf8');
            const versionTokens = packageContent.match('"version"[^0-9]+([0-9\.]+)');
            const expected = versionTokens[1];
            const actual = numnjstoix.ver();
            assert.equal(expected, actual);
            done();
        });
    });
});