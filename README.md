# SYCL Hello World

Welcome, this is a little repository I set up to testout SYCL.
At the moment the program is really dumb and just adds or substracts
two lists in a parallel for-loop.

## Prerequisites

To build, you need to clone and build the [AdaptiveCpp](https://github.com/AdaptiveCpp/AdaptiveCpp) compiler
and also install [pixi](https://prefix.dev/).

## How to Build

I have created some commands in pixi to easily build and run the project

```bash
pixi run clean  # Removes build files
pixi run gen    # Generate make files 
pixi run build  # Compiles binary
pixi run add    # Runs binary with -add option
pixi run sub    # Runs binary with -sub option
```
