from invoke import task

@task
def clean_cmult(c):
    c.run('rm libcmult.so')

@task
def build_cmult(c):
    c.run('gcc -shared -o libcmult.so cmult.c')

@task
def test_ctypes(c):
    c.run('python ctypes_test.py')

