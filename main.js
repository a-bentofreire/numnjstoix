// uuid: 37dc16d4-220a-4209-9297-6a32e433f7f4

// ------------------------------------------------------------------------
// Copyright (c) 2019 Alexandre Bento Freire. All rights reserved.
// Licensed under the MIT License+uuid License. See License.txt for details
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