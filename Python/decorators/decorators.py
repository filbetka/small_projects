from functools import wraps


def debug(attrs=['__name__']):
    def decorator(func):
        @wraps(func) # copy `func` information into `wrapper` function
        def wrapper():
            print('Functions attributes:')
            for attr in attrs:
                print(f"{attr}: {func.__getattribute__(attr)}")
            func()
        return wrapper
    return decorator

