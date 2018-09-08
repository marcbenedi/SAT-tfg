# SAT-tfg

This project is an environment to work with Pseudo-Boolean optimisation problems and Boolean formulae.

## Example

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See deployment for notes on how to deploy the project on a live system.

### Prerequisites

For installing and running, there are two requisites:
* [cmake](https://cmake.org/install/)
* [picosat](http://fmv.jku.at/picosat/)
* [minisat](http://minisat.se/)
* [zlib1g-dev](https://packages.debian.org/search?keywords=zlib1g-dev)

The first three need to be accessible through the cml:
```sh
$ picosat --version
$ cmake --version
$ minisat
```

### Installing

Download the project.
It is recommended to download always stable versions:
```sh
$ wget https://github.com/marcbenedi/SAT-tfg/archive/v1.1.zip
$ unzip  v1.1.zip
```
This will create SAT-tfg-1.1 directory.

To install this project execute:
```sh
$ chmod +x installer.sh
$ ./installer.sh
```
This script will install all the required things:
* [Google Test](https://github.com/google/googletest)
* [PBLib](http://tools.computational-logic.org/content/pblib.php)
* [Cudd](https://github.com/ivmai/cudd)

Finally, it will execute the tests.

## Compile a file

## Built With

* [Google Test](https://github.com/google/googletest)
* [PBLib](http://tools.computational-logic.org/content/pblib.php)
* [Cudd](https://github.com/ivmai/cudd)

## Contributing

Please read [CONTRIBUTING.md](https://gist.github.com/PurpleBooth/b24679402957c63ec426) for details on our code of conduct, and the process for submitting pull requests to us.

## Versioning

For the versions available, see the [tags on this repository](https://github.com/marcbenedi/SAT-tfg/tags).

## Authors
* **[Jordi Cortadella](https://www.cs.upc.edu/~jordicf/)** - *Original idea and supervisor*
* **[Marc Benedí](http://marcb.pro/)** - *Creator*

See also the list of [contributors](https://github.com/marcbenedi/SAT-tfg/contributors) who participated in this project.

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

* [Jordi Cortadella](https://www.cs.upc.edu/~jordicf/)
