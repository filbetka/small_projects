from invoke import task

@task
def clean(c):
    c.run('rm libcmult.so')
    print('cleaned solution')

@task
def build(c):
    c.run('gcc -shared -o libcmult.so cmult.c')
    print('builded libcmult.so')

@task
def test(c):
    c.run('python ctypes_test.py')
    print('finished test')

