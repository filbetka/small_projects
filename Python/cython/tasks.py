from invoke import task

@task
def install(c):
    c.run('pip3 install cython')

@task
def clean(c):
    pass

@task
def build(c):
    c.run('g++ -shared -std=c++11 -fPIC cppmult.cpp -o libcppmult.so')
    c.run('cython --cplus -3 cython_example.pyx -o cython_wrapper.cpp')
    c.run('g++ -shared -std=c++11 -fPIC `python3 -m pybind11 --includes` -I /usr/include/python3.8 -I . cython_wrapper.cpp -o cython_example`python3.8-config --extension-suffix` -L. -lcppmult -Wl,-rpath,.')

