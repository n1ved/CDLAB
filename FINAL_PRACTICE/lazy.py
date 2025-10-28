import os

import sys

filename = sys.argv[1]
os.system(f"yacc -d {filename}.y")
os.system(f"lex {filename}.l")
os.system("gcc y.tab.c lex.yy.c")
os.system("./a.out")
