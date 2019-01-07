# SAT-tfg

This project is an environment to work with Pseudo-Boolean optimisation problems and Boolean formulae.

## Code example
```cpp
Formula a = BoolFunc::newLit("a");
Formula b = BoolFunc::newLit("b");

Formula c = a + b;
Cnf tseitin = CnfConverter::tseitin(c);
tseitin.print();
```

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

## Table of contents
* Installation
* Usage
* Built With
* Contributing
* Versioning
* Authors
* License
* Acknowledgments

## Installation

### Requirements

For installing and running, there are four requirements. **This must be present in the system:**
* **[cmake](https://cmake.org/install/):**  CMake is used to control the software compilation process using simple platform and compiler independent configuration files, and generate native makefiles and workspaces that can be used in the compiler environment of your choice.
* **[picosat](http://fmv.jku.at/picosat/):** A SAT solvers
* **[minisat](http://minisat.se/):** A SAT solver
* **[zlib1g-dev](https://packages.debian.org/search?keywords=zlib1g-dev):** zlib is a library implementing the deflate compression method found in gzip and PKZIP

The first three need to be accessible through the cml:
```sh
$ picosat --version
$ cmake --version
$ minisat
```

### How to download it and install it

Download the project.
It is recommended to download always stable versions:
```sh
$ wget https://github.com/marcbenedi/SAT-tfg/archive/v1.2.zip
$ unzip  v1.2.zip
```
This will create SAT-tfg-1.2 directory.

To install this project execute:
```sh
$ chmod +x installer.sh
$ ./installer.sh
```
This script will install the following libraries:
* [Google Test](https://github.com/google/googletest)
* [PBLib](http://tools.computational-logic.org/content/pblib.php)
* [Cudd](https://github.com/ivmai/cudd)

Finally, it will execute the tests.

## Usage

Check the [Wiki page](https://github.com/marcbenedi/SAT-tfg/wiki).


## Built With

* [Google Test](https://github.com/google/googletest)
* [PBLib](http://tools.computational-logic.org/content/pblib.php)
* [Cudd](https://github.com/ivmai/cudd)

## Contributing

Please read [CONTRIBUTING.md](https://gist.github.com/PurpleBooth/b24679402957c63ec426) for details on our code of conduct, and the process for submitting pull requests to us.

## Versioning

For the versions available, see the [tags on this repository](https://github.com/marcbenedi/SAT-tfg/tags).
It is always recommended to use the latest version.

## Authors
* **[Jordi Cortadella](https://www.cs.upc.edu/~jordicf/)** - *Original idea and supervisor*
* **[Marc Benedí](http://marcb.pro/)** - *Author and developer*

See also the list of [contributors](https://github.com/marcbenedi/SAT-tfg/contributors) who participated in this project.

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

```
MIT License

Copyright (c) 2018 Marc Benedí

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```
## Acknowledgments

* [Jordi Cortadella](https://www.cs.upc.edu/~jordicf/)
