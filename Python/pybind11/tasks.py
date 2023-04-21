from invoke import task

@task
def install_dependencies(c):
    c.run('pip3 install pybind11')

@task
def clean(c):
    c.run('rm *.so')

@task
def build(c):
    c.run('g++ -shared -std=c++11 -fPIC cppmult.cpp -o libcppmult.so')
    c.run('g++ -shared -std=c++11 -fPIC `python3 -m pybind11 --includes` -I /usr/include/python3.8 -I . pybind11_wrapper.cpp -o pybind11_example`python3.8-config --extension-suffix` -L. -lcppmult -Wl,-rpath,.')

@task
def run(c):
    c.run('python3 pybind11_test.py')
