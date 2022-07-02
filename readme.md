## 200_000
```bash
cp03@grad01:~$ ladcomp -env mpicc tree4.c -o app4 ; ladrun -np 7 app4
mpicc tree.c -o app4
Tempo de execucao: 15.1497 s

cp03@grad01:~$ ladcomp -env mpicc tree8.c -o app8 ; ladrun -np 15 app8
mpicc tree.c -o app8
Tempo de execucao: 4.2210 s

cp03@grad01:~$ ladcomp -env mpicc tree16.c -o app16 ; ladrun -np 31 app16
mpicc tree.c -o app16
Tempo de execucao: 1.5252 s

cp03@grad01:~$ ladcomp -env mpicc tree32.c -o app32 ; ladrun -np 63 app32
mpicc tree.c -o app32
Tempo de execucao: 1.1053 s
```

## 1_000_000

```bash
cp03@grad01:~$ ladcomp -env mpicc tree4.c -o app4 ; ladrun -np 7 app4
mpicc tree4.c -o app4
Tempo de execucao: 377.6601 s

cp03@grad01:~$ ladcomp -env mpicc tree8.c -o app8 ; ladrun -np 15 app8
mpicc tree8.c -o app8
Tempo de execucao: 96.9268 s

cp03@grad01:~$ ladcomp -env mpicc tree16.c -o app16 ; ladrun -np 31 app16
mpicc tree16.c -o app16
Tempo de execucao: 25.7158 s

cp03@grad01:~$ ladcomp -env mpicc tree32.c -o app32 ; ladrun -np 63 app32
mpicc tree32.c -o app32
Tempo de execucao: 12.5894 s
```
