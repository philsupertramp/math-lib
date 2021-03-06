# math-lib [![CircleCI](https://circleci.com/gh/philsupertramp/math-lib.svg?style=svg)](https://circleci.com/gh/philsupertramp/math-lib)

a collection of functions I need(ed) to study during my mathematics bachelor

## requirements

```bash
cmake>=3.15.2
gnuplot>=5.2 patchlevel 7
```

## build
run `./build.sh`

it will ask you if you want to run tests or the regular programm.
answer with `Y` to execute tests

### TOC
- `vector.h`
  - struct to store information about a vector
- `stat.h`:
  - support for `vector` and `double*`
  - functions:
    - abs
    - pow
    - min
    - max
    - mean
    - cov
    - var
    - lm
    - getExponent
    - coefficientOfDetermination
    - for `double*` with `_d` extension
  - structs:
    - lmMod:
      - stores the resuldial coefficients of a simple linear regression (`beta_0`, `beta_1`)
- `plot.h`:
  - functions
    - scatterPlot
    - getBoundaries
  - structs:
    - boundary:
      - keeps track of axis boundaries
      - contains `min` and `max` value
    - plotAttributes
      - keeps track of text based plot attributes
      - `title`
      - `xAxis`
      - `yAxis`
