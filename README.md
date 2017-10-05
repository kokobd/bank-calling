# BankCalling
Build status

|CI Site|Status|
|:-:|:-:|
|AppVeyor|![build-appveyor](https://ci.appveyor.com/api/projects/status/github/zelinf/bank-calling?branch=master)|

This is a bank-calling simulation program. Download pre-built binaries from
GitHub releases.

During every logical second, random number of customers are generated, while each customer
requires random expected service time. The random numbers conform normal distribution.
Relevant parameters can be changed.

## Build Guide
If you want to build this project, note that it is a standard CMake project.
```sh
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
```
You may choose the generator with `-G` option.\
If you are on windows and using the Visual Studio generators, you
will find a visual studio solution.\
If you are on linux, using a makefile-based generator, you then run
```sh
make
make test
```
The main executable will be placed in `build/src/app-cli/bank-calling-app`