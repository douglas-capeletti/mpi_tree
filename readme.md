```bash
alias run='echo 4 ; ladrun -np 7 app4 ; echo 8 ; ladrun -np 15 app8 ; echo 16 ; ladrun -np 31 app16 ; echo 32 ; ladrun -np 63 app32 ; echo 64 ; ladrun -np 127 app64';
```

---

# 2 MÁQUINAS (8 Cores + HT)

## 200_000

```bash
cp03@grad01:~/duzentos$ run
4
Tempo de execucao: 15.5536 s
8
Tempo de execucao: 4.2405 s
16
Tempo de execucao: 2.0704 s
32
Tempo de execucao: 1.2151 s
64
Tempo de execucao: 0.7602 s
```

## 1_000_000

```bash
cp03@grad01:~/milhao$ run
4
Tempo de execucao: 379.7707 s
8
Tempo de execucao: 99.8372 s
16
Tempo de execucao: 42.0714 s
32
Tempo de execucao: 21.0131 s
64
Tempo de execucao: 11.2627 s
```

---

# 4 MÁQUINAS (8 Cores + HT)

## 200_000

```bash
cp03@grad01:~/duzentos$ run
4
Tempo de execucao: 15.6486 s
8
Tempo de execucao: 4.3916 s
16
Tempo de execucao: 1.4517 s
32
Tempo de execucao: 0.5510 s
64
Tempo de execucao: 0.4373 s
```

## 1_000_000

```bash
cp03@grad01:~/milhao$ run
4
Tempo de execucao: 378.3716 s
8
Tempo de execucao: 97.2454 s
16
Tempo de execucao: 25.4354 s
32
Tempo de execucao: 10.7881 s
64
Tempo de execucao: 5.8341 s
```
