// ------------------------------------------------------------------------
// Copyright (c) 2019-2024 Alexandre Bento Freire. All rights reserved.
// Licensed under the MIT License.
// ------------------------------------------------------------------------
"use strict";

import { createRequire } from 'node:module';
const numnjstoix = createRequire(import.meta.url)('./build/Release/numnjstoix');

numnjstoix.AUTO = 0;
numnjstoix.NUMBER = 1;
numnjstoix.ARRAY = 10;
numnjstoix.MATRIX = 11;
numnjstoix.FLOAT_ARRAY32 = 20;
numnjstoix.FLOAT_ARRAY64 = 21;

export { numnjstoix };