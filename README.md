## Project: arrow-pybind

Mini-repo to build simple Apache Arrow python module using pybind11. It expects a [miniconda](https://docs.conda.io/en/latest/miniconda.html) installation and creates an environment named arrow-pybind to build and execute within.

___

### Build:

This repo can be built using [./build.sh](https://github.com/ajdonich/arrow-pybind/blob/main/build.sh), which will clone Apache Arrow (if needed), build and install arrow-cpp (in *./arrow/cpp/arrow-build* and *./arrow/cpp/arrow-install* respectively), and finally build the python module using pybind11 (in *./_build*). Specifically, execute the following steps:

```
$ git clone https://github.com/ajdonich/arrow-pybind.git
$ cd arrow-pybind
$ conda env create -f arrow-pybind.yml
$ conda activate arrow-pybind
$ ./build.sh
```
___

### Execution:

To run the test from command-line (if successful, this will create parquet file: *./_build/pybindtest.parquet*):
```
$ cd _build
$ python pybindtest.py
```

### Bus Error/Segmentation Fault:

Installation of the conda **pyarrow** module can (consistently) result in Bus Error/Segmentation Faults when running [./pybindtest.py](https://github.com/ajdonich/arrow-pybind/blob/main/pybindtest.py). I suspect this results from some difference in arrow-cpp build configuration relative to conda-forge. So, if you want to use **pyarrow**, rather than installing it from conda-forge, it's probably necessary to build it from source (which is not being performed currently by this project). Thus, to induce the error: uncomment **pyarrow** in [./arrow-pybind.yml](https://github.com/ajdonich/arrow-pybind/blob/main/arrow-pybind.yml), then execute:

```
$ cd ..
$ conda env update -n arrow-pybind -f arrow-pybind.yml
$ ./build.sh
$ cd _build
$ python pybindtest.py
```

Note also that to re-correct the error, it may be necessary to entirely remove and re-create the conda environment rather than just update it. Thus after commenting out **pyarrow** in [./arrow-pybind.yml](https://github.com/ajdonich/arrow-pybind/blob/main/arrow-pybind.yml), execute:

```
$ cd ..
$ conda deactivate
$ conda remove --name arrow-pybind --all
$ conda env create -f arrow-pybind.yml
$ conda activate arrow-pybind
$ ./build.sh
$ cd _build
$ python pybindtest.py
```