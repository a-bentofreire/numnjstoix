// ------------------------------------------------------------------------
// Copyright (c) 2019-2024 Alexandre Bento Freire. All rights reserved.
// Licensed under the MIT License
// ------------------------------------------------------------------------

/**
 * Sample p0 to be provided as input for mocha tests.
 */

exports.input = [{
    label: "positives Float32Array",
    p0: new Float32Array([34.4, 56.7, 89.6, 67.5, 66.7, 30.4, 54.6, 43.5]),
    tags: ['unary', 'statistics']
  },
  {
    label: "positives & negatives",
    p0: new Float32Array([34.4, -56.7, 89.6, 67.5, -66.7]),
    tags: ['unary', 'statistics']
  },
  {
    label: "Array",
    p0: [34.4, -56.7, 89.6, 67.5, -66.7],
    tags: ['unary', 'statistics']
  },
  {
    label: "Float64Array",
    p0: new Float64Array([-34.4, 56.7, -89.6, 67.5, 66.7]),
    tags: ['unary', 'statistics']
  },
  {
    label: "Matrix",
    p0: [
      [34.4, -56.7],
      [3.44, 89.6],
      [67.5, 64.55]
    ],
    tags: ['unary']
  },
  {
    label: "Square Matrix",
    p0: [
      [34.4, -56.7, 43.3],
      [3.44, 89.6, 54.3],
      [67.5, 64.55, -156.3]
    ],
    tags: ['diagonal']
  },
  {
    label: "Matrix with invalid values",
    p0: [
      [34.4, -56.7],
      [NaN, 89.6],
      [67.5, 64.55]
    ],
    tags: ['unary']
  },
  {
    label: "large values",
    p0: new Float32Array([1e5, -144445.55, 89.6, 64447.55555555, -66.7]),
    tags: ['unary', 'statistics']
  },
  // {
  //   label: "integer values",
  //   p0: new Int32Array([33444, -144445, 89])
  // },
  {
    label: "with NaN",
    p0: new Float32Array([34.4, -56.7, NaN, 89.6, 67.5]),
    tags: ['unary', 'statistics']
  },
  {
    label: "with Infinity",
    p0: new Float32Array([34.4, -56.7, Infinity, 89.6, 67.5]),
    tags: ['unary', 'statistics']
  },
  {
    label: "with Undefined",
    p0: new Float32Array([34.4, -56.7, undefined, 89.6, 67.5]),
    tags: ['unary', 'statistics']
  },
  {
    label: "binary Array",
    p0: [34.4, -56.7, -16.6, 89.6, 67.5],
    p1: [434.4, 656.7, 757.5, -589.6, 767.5],
    tags: ['binary', 'multiply', 'divide', 'statistics-binary']
  },
  {
    label: "binary Array with undefined",
    p0: [34.4, -56.7, undefined, 89.6, 67.5],
    p1: [434.4, 656.7, undefined, -589.6, 767.5],
    tags: ['binary', 'multiply', 'divide', 'statistics-binary']
  },
  {
    label: "binary Float32Array",
    p0: new Float32Array([34.4, -56.7, -16.6, 89.6, 67.5]),
    p1: new Float32Array([434.4, 656.7, 757.5, -589.6, 767.5]),
    tags: ['binary', 'multiply', 'divide', 'statistics-binary']
  },
  {
    label: "binary Float32Array with undefined",
    p0: new Float32Array([34.4, -56.7, undefined, 89.6, 67.5]),
    p1: new Float32Array([434.4, 656.7, undefined, -589.6, 767.5]),
    tags: ['binary', 'multiply', 'divide', 'statistics-binary']
  },
  {
    label: "binary Array+Float32Array with undefined",
    p0: [0.334, -56.7, undefined, 89.6, 67.5],
    p1: new Float32Array([-434.4, 656.7, undefined, -589.6, 767.5]),
    tags: ['binary', 'multiply', 'divide', 'statistics-binary']
  },
  {
    label: "binary Matrix",
    p0: [
      [34.4, -56.7],
      [3.44, 89.6],
      [67.5, 64.55]
    ],
    p1: [
      [434.4, 656.7],
      [8.6, -589.6],
      [767.5, -444.87]
    ],
    tags: ['binary', 'multiply', 'divide']
  },
  {
    label: "binary Matrix with invalid values",
    p0: [
      [34.4, -56.7],
      [NaN, 89.6],
      [67.5, 64.55]
    ],
    p1: [
      [434.4, 656.7],
      [undefined, -589.6],
      [767.5, -444.87]
    ],
    tags: ['binary', 'multiply', 'divide']
  },
  {
    label: "value op Matrix",
    p0: 10,
    p1: [
      [434.4, 656.7],
      [8.6, -589.6],
      [767.5, -444.87]
    ],
    tags: ['multiply']
  },
  {
    label: "Matrix op value",
    p0: [
      [434.4, 656.7],
      [8.6, -589.6],
      [767.5, -444.87]
    ],
    p1: 10,
    tags: ['divide']
  },
  {
    label: "square Matrix",
    p0: [
      [34.4, -56.7, 55.4, 65.4],
      [3.44, 89.6, -23.455, 12.33],
      [67.5, -64.55, 222.55, 56.44],
      [-80.33, -44.5, 555.34, -553.2]
    ],
    tags: ['diagonal']
  },
  {
    label: "single dimension",
    p0: 5,
    tags: ['eye']
  }, {
    label: "double dimension",
    p0: 5,
    p1: 6,
    tags: ['dim2']
  },
];