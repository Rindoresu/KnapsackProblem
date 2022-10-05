import pandas as pd

n_ini = 5
n_fin = 30
prim_columna = [n_ini]
sec_columna = [n_fin]

for i in range(n_ini, n_fin+1):
    prim_columna.append(i)
    sec_columna.append(2**i)
    for j in range(i-1):
        prim_columna.append(1)
        sec_columna.append(1)
    prim_columna.append(2**i)
    sec_columna.append(2**i - 1)

tests = {'A': prim_columna,
         'B': sec_columna}

df = pd.DataFrame(tests)

path = '/home/leandro/CLionProjects/algoritmos3-tp1/Python/'
file = 'MaloBacktrackingPseudopolinomial.csv'

df.to_csv(path_or_buf=path+file, index=False, header=False, sep=' ')


n_ini = 5
n_fin = 30
prim_columna = [n_ini]
sec_columna = [n_fin]

for i in range(n_ini, n_fin+1):
    prim_columna.append(i)
    sec_columna.append(i+1)
    for j in range(i-1):
        prim_columna.append(1)
        sec_columna.append(1)
    prim_columna.append(i+1)
    sec_columna.append(i)

tests = {'A': prim_columna,
         'B': sec_columna}

df = pd.DataFrame(tests)

path = '/home/leandro/CLionProjects/algoritmos3-tp1/Python/'
file = 'MaloBacktrackingLineal.csv'

df.to_csv(path_or_buf=path+file, index=False, header=False, sep=' ')
