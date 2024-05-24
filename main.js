// ------------------------------------------------------------------------
// Copyright (c) 2019-2024 Alexandre Bento Freire. All rights reserved.
// Licensed under the MIT License.
// ------------------------------------------------------------------------
"use strict";

const numnjs = require('./build/Release/numnjs');
module.exports = numnjs;

numnjs.AUTO = 0;
numnjs.NUMBER = 1;
numnjs.ARRAY = 10;
numnjs.MATRIX = 11;
numnjs.FLOATARRAY32 = 20;
numnjs.FLOATARRAY64 = 21;