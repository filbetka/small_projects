# ctypes_test.py
import ctypes
import pathlib

if __name__ == "__main__":
    # Load the shared library into ctypes
    libname = pathlib.Path().absolute() / "libcmult.so"
    c_lib = ctypes.CDLL(libname)
    c_lib.cmult.restype = ctypes.c_float
    print(c_lib.cmult(5, ctypes.c_float(5.5)))
