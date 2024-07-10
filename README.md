# Description

[numnjs](https://www.devpieces.com/en/projects/numnjs) is a lightweight numerical analysis C++ add-on for nodejs.  
Although, numnjs has been tested, it's still in a development phase, and its API can change in future versions.  
At the moment, numnjs doesn't implement any major speed optimizations to archive maximum speed.  
It's biggest speed gain derives from the fact that it's implemented in C++ as opposed to JavaScript.  
However, future versions might be significantly faster by adding of speed optimizations.  
Many numnjs functions handle `NaN` and `Inf` gracefully by bypassing their calculations. Although, this behavior might change in order to speed up the calculations.

Use `numnjs` when:

- You don't need a full-blown numerical analysis package.
- You want a functionality similar to [numpy](http://www.numpy.org/).
- Your data contains `NaN` and `Inf`.
- Your data can be Arrays, TypedArray (Float32Array and Float64Array), or matrices (Array of Array).

## Installation

`[sudo] npm install -g numnjs`

## Requirements

numnjs v0.2+ requires node 22.2 or above.

`numnjs` uses `node-gyp` to compile the C++ addon to binary format.  
So read the [node-gyp](https://www.npmjs.com/package/node-gyp) requirements section to determined what is the required software for your platform.  
  
`numnjs` is implemented in [C++11](https://en.wikipedia.org/wiki/C%2B%2B11), therefore the C++ compiler must support C++11 compilation.

## Data Types

- **a**: Array, TypedArray(Float32Array or Float64Array).
- **m**: Matrix(Array of Array).
- **v**: Real Number.
- **k**: Scalar (Real Number).
- **d**: Dimensions (Positive number).
- **T**: Output Data Type:
  - numnjs.AUTO = 0;
  - numnjs.NUMBER = 1;
  - numnjs.ARRAY = 10;
  - numnjs.MATRIX = 11;
  - numnjs.FLOATARRAY32 = 20;
  - numnjs.FLOATARRAY64 = 21;

## Functions Categories

numnjs is organized into files to resemble the numpy method's organization, as defined in these documents:

- [Mathematical](https://docs.scipy.org/doc/numpy-1.15.4/reference/routines.math.html).
- [Matrix](https://docs.scipy.org/doc/numpy-1.15.4/reference/routines.matlib.html).
- [Statistics](https://docs.scipy.org/doc/numpy-1.15.4/reference/routines.statistics.html).
- [Linear algebra](https://docs.scipy.org/doc/numpy-1.15.4/reference/routines.linalg.html).

But internally, numnjs functions are organized according to their data inputs and outputs:

| Category | Description |  
| ------------- | ------------- |  
| Aggregator | Input: Array/TypedArray or Matrix.<br>Output: Real Number. |
| Transform | Input: Array/TypedArray or Matrix.<br>Output: Same type as input. |
| Binary | Input: two Array/TypedArray or Matrices of same dimension and length.<br>Output: Same type as the first input, except if 1st input is a scalar. |
| nInputs | Input: n Array/TypedArray or Matrices<br>Output: Real Number, Array/TypedArray or Matrix. |
| Generator | Input: zero Data<br>Output: Array/TypedArray or Matrix. |

Note: For TypedArray different from Float32Array or Float64Array, it returns Float64Array.

## Invalid Data

`Inf` and `NaN` are ignored in the calculations.  
When there is more than one data input, if at least one is invalid, it returns the value of the first input if this invalid other the 2nd input.  
  
Example:  
`avr([5.5,NaN,6.5,Inf])==avr([5.5,6.5])`.  
`add([4,Inf,6,NaN],[6,NaN,Inf,Inf])=[10,Inf,Inf,Nan]`.  

## Functions

### Information

| Function | Description |  
| ------------- | ------------- |  
| s = **ver**() | Returns the numnjs version in semver format |

### Trigonometric

| Function | Description |  
| ------------- | ------------- |  
| am = **sin**(am) | Returns the sine of each element of the input |
| am = **cos**(am) | Returns the cosine of each element of the input |
| am = **tan**(am) | Returns the tangent of each element of the input |
| am = **arcsin**(am) | Returns the inverse sine of each element of the input |
| am = **arccos**(am) | Returns the inverse cosine of each element of the input |
| am = **arctan**(am) | Returns the inverse tangent of each element of the input |
| am = **degrees**(am) | Returns the `xi * (180 / PI)` of each element of the input |
| am = **radians**(am) | Returns the `xi / (180 / PI)` of each element of the input |

### Hyperbolic

| Function | Description |  
| ------------- | ------------- |  
| am = **sinh**(am) | Returns the hyperbolic sine of each element of the input |
| am = **cosh**(am) | Returns the hyperbolic cosine of each element of the input |
| am = **tanh**(am) | Returns the hyperbolic tangent of each element of the input |
| am = **arcsinh**(am) | Returns the inverse hyperbolic sine of each element of the input |
| am = **arccosh**(am) | Returns the inverse hyperbolic cosine of each element of the input |
| am = **arctanh**(am) | Returns the inverse hyperbolic tangent of each element of the input |

### Rounding

| Function | Description |  
| ------------- | ------------- |  
| am = **round**(am) | Returns the the input rounded to the nearest number |
| am = **floor**(am) | Returns the the input rounded to the lowerest number |
| am = **ceil**(am) | Returns the the input rounded to the highest number |

### Sums, products, differences

| Function | Description |  
| ------------- | ------------- |  
| v = **sum**(am) | Returns the sum of all the values |

### Exponents and logarithms

| Function | Description |  
| ------------- | ------------- |  
| am = **exp**(am) | Returns the exponential of each element of the input |
| am = **expm1**(am) | Returns the `exp(xi) -1` of each element of the input |
| am = **exp2**(am) | Returns the natural logarithm of each element of the input |
| am = **log**(am) | Returns the natural logarithm of each element of the input |
| am = **log10**(am) | Returns the base 10 logarithm of each element of the input |
| am = **log2**(am) | Returns the base 2 logarithm of each element of the input |

### Arithmetic

| Function | Description |  
| ------------- | ------------- |  
| am = **add**(am1, am2) | Returns the sum between the two inputs for each element |
| am = **reciprocal**(am) | Returns the `1/xi` of each element of the input |
| am = **negative**(am) | Returns the negative value of each element of the input |
| am = **multiply**(_kam1_, am2) | Returns the multiplication between the two inputs for each element |
| am = **divide**(am1, _kam2_) | Returns the division between the two inputs for each element |
| am = **power**(am1, am2) | Returns the power of the first raised by the second for each element |
| am = **subtract**(am1, am2) | Returns the subtraction between the two inputs for each element |
| am = **mod**(am1, am2) | Returns the modulus between the two inputs for each element<br>It uses C++ `fmod`, and for negative values,<br>It has same behavior as JavaScript `x%y` but different from numpy `np.mod` |

### Miscellaneous

| Function | Description |  
| ------------- | ------------- |  
| am = **sqrt**(am) | Returns the sqrt of each element of the input |
| am = **cbrt**(am) | Returns the cubic root of each element of the input |
| am = **square**(am) | Returns the square of each element of the input |
| am = **sign**(am) | Returns the sign of each element of the input |
| am = **abs**(am) | Returns the absolute value of each element of the input |
| am = **maximum**(am1, am2) | Returns the maximum value between the two inputs of each element of the input |
| am = **minimum**(am1, am2) | Returns the minimum value between the two inputs of each element of the input |
| am = **max**(am) | Returns the maximum value |
| am = **min**(am) | Returns the minimum value |

### Matrix

| Function | Description |  
| ------------- | ------------- |  
| v = **det**(m) | Returns the determinant of matrix m |
| a = **diagonal**(m{, T}) | Returns the diagonal of matrix m. The return value is of type T.<br>if T is missing it returns an array |
| m = **eye**(d) | Returns a matrix (dxd) with zero and diagonal with ones |
| m = **ones**(d1,d2) | Returns the matrix (d1xd2) with ones |
| m = **rand**(d1,d2) | Returns the matrix (d1xd2) with random values [0,1] |
| m = **zeros**(d1,d2) | Returns the matrix (d1xd2) with zeros |

### Statistics

| Function | Description |  
| ------------- | ------------- |  
| v = **avg**(a) | Returns the average value |
| v = **var**(a) | Returns the variance |
| v = **std**(a) | Returns the standard deviation |
| v = **skew**(a) | Returns the skewness |
| v = **kurtosis**(a<br>{, fisher}) | Returns the kurtosis (default is Pearson's definition)<br>If the 2nd parameter is True, uses Fisher’s definition<br>The default it's the opposite of numpy |
| v = **cov**(a1, a2) | Returns the covariance measure<br>Uses an unbiased estimate (N-1 denominator)<br>`numpy.cov(x,y)=[[numnjs.cov(x,x),numnjs.cov(x,y)],[numnjs.cov(y,x),numnjs.cov(y,y)]]`  |

## Example

```js
  const numnjs = require('numnjs');
  const input1 = [4.5, 6.5, -5.6, NaN];
  const output1 = numnjs.min(input1);
  console.log(output1); // -5.6

  const input2 = new Float64Array([4.5, 6.5, Inf, -6]);
  const output2 = numnjs.negate(input2);
  console.log(output2); // Float64Array([-4.5, -6.5, Inf, 6])

  const input3a = [[4.5, 6.5],[89, 9.7],[76, Inf]];
  const input3b = [[14.5, -16.5],[-189, 9.7],[-76, Inf]];
  const output3 = numnjs.multiply(input3a, input3b);
  console.log(output3);
```

## License

MIT License

## Copyrights

(c) 2019-2024 [Alexandre Bento Freire](https://www.a-bentofreire.com)
