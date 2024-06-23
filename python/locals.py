#!/usr/bin/env python

# python 3
from pprint import pprint
a = 10
b = 20

def foo():
    x = 30 # x and y are local variables
    y = 40
    print("locals() = {0}".format(locals()))

pprint(locals()) # same as calling globals()
print('*' * 80)
print("locals() == globals()? ", locals() == globals())
print('*' * 80)
foo()

# output:
# {'__builtins__': <module 'builtins' (built-in)>,
# '__cached__': None,
# '__doc__': None,
# '__file__': 'module1.py',
# '__loader__': <_frozen_importlib_external.SourceFileLoader object at 0x7fa18790a828>,
# '__name__': '__main__',
# '__package__': None,
# '__spec__': None,
# 'a': 10,
# 'b': 20,
# 'foo': <function foo at 0x7fa1878752f0>,
# 'pprint': <function pprint at 0x7fa1878756a8>}

# ********************************************************************************

# locals() == globals()? True

# ********************************************************************************

# locals() = {'y': 40, 'x': 30}
