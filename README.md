## Project: arrow-pybind

Mini-repo to build simple Apache Arrow python module using pybind11. It expects a [miniconda](https://docs.conda.io/en/latest/miniconda.html) installation and creates an environment named arrow-pybind to build and execute within.

___

### Build:

This repo can be built using [./build.sh](https://github.com/ajdonich/arrow-pybind/blob/main/build.sh), which will clone Apache Arrow (if needed), build and install arrow-cpp (in *./arrow/cpp/arrow-build* and *./arrow/cpp/arrow-install* respectively), and build a python module using pybind11 (in *./_build*). Specifically, execute the following steps:

```
$ git clone https://github.com/ajdonich/arrow-pybind.git
$ cd arrow-pybind
$ conda env create -f arrow-pybind.yml
$ conda activate arrow-pybind
$ ./build.sh
```
___

### Execution:

To run the command-line test (which if successful, will create parquet file: *./_build/pybindtest.parquet*):
```
$ cd _build
$ python pybindtest.py
```
___

### Troubleshooting Bus Error/Segmentation Fault:

In my development on MacOS, installation of **pyarrow** (or any modules/packages that depend on **pyarrow**) from conda/conda-forge induced Bus Error/Seg Faults when running [./pybindtest.py](https://github.com/ajdonich/arrow-pybind/blob/main/pybindtest.py). To address this issue simply, pip can be used to install **pyarrow** (as in [./arrow-pybind.yml](https://github.com/ajdonich/arrow-pybind/blob/main/arrow-pybind.yml)). The issue may relate to a MacOS licensing issue mentioned in [Arrow Python Build Docs](https://arrow.apache.org/docs/developers/python.html) that states:  
>*Using conda to build Arrow on macOS is complicated by the fact that the conda-forge compilers require an older macOS SDK. Conda offers some installation instructions; the alternative would be to use Homebrew and pip instead.*
