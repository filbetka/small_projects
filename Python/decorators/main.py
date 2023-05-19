from decorators import debug


@debug()
def one():
    print("do one")

    
@debug(attrs=['__name__', '__code__', '__globals__', '__doc__'])
def two():
    print("do two")


if __name__ == '__main__':
    print('Name of first function: ', one.__name__)
    print('Name of second function: ', two.__name__)

    print('\nCall first function: ')
    one()

    print('\nCall second function: ')
    two()

