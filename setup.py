from setuptools import setup, Extension
import pybind11
import os

# Get the absolute path of the directory where setup.py is located
root_path = os.path.abspath(os.path.dirname(__file__))

ext_modules = [
    Extension(
        'hlv_engine',
        ['src/hlv_engine.cpp'],
        include_dirs=[
            os.path.join(root_path, 'src'),
            # ✅ ADDED: The specific path where your .hpp files live
            os.path.join(root_path, 'src', 'cpp_core'), 
            pybind11.get_include(),
            # Standard Apple Silicon Eigen paths
            '/opt/homebrew/include/eigen3', 
            '/usr/local/include/eigen3',
            '/opt/homebrew/include',
        ],
        language='c++',
        extra_compile_args=['-std=c++17', '-O3', '-march=native'],
    ),
]

setup(ext_modules=ext_modules)
