# 🔥 Firepot-Challenge

**Simulador de Luminosidade**

Este projeto simula a **intensidade luminosa** recebida por pontos receptores em um plano 2D contendo **fontes de luz** e **obstáculos**.  
O cálculo considera **interseções geométricas** e **reduções de intensidade** conforme a opacidade de cada obstáculo.

---

## 📁 Estrutura do Projeto

```text
├── include/
│   ├── geometry.h        # Estruturas e classes geométricas (retângulo, círculo, linha)
│   ├── parser.h          # Declaração do parser e estrutura da cena
│   ├── simulation.h      # Funções de simulação
│
├── src/
│   ├── geometry.cpp      # Implementação dos cálculos geométricos
│   ├── parser.cpp        # Interpretação do arquivo de entrada
│   ├── simulation.cpp    # Lógica de propagação de luz
│   ├── export_scene.cpp  # Exportação da cena para visualização
│   ├── main.cpp          # Ponto de entrada do programa
│
├── plot_scene.py         # Script opcional de visualização
├── regiao.txt            # Arquivo de entrada (exemplo de cena)
├── scene_debug.txt       # Arquivo auxiliar gerado automaticamente
└── README.md
```

---

## ⚙️ Compilação e Execução

### 🪟 **Windows**

```bash
g++ src/*.cpp -Iinclude -o teste
teste.exe
```

### 🐧 **Linux / macOS**

```bash
g++ src/*.cpp -Iinclude -o teste
./teste
```

O programa lerá o arquivo `regiao.txt` e exibirá os resultados no formato:

```text
P0 = 1499.44
P1 = 2239.97
...
```

---

## 🔍 Visualização Gráfica (Opcional)

Você pode visualizar a cena exportada com o script Python:

```bash
python plot_scene.py
```

**Legenda:**

- 🟡 **Fonte** – origem da luz
- 🟣 **Receptor** – ponto onde a iluminação é medida
- 🟥 **Retângulo**, 🔵 **Círculo**, 🟩 **Linha** – obstáculos com redução de luz
- Linhas tracejadas amarelas representam a conexão entre fontes e receptores

---

## 📄 Formato do Arquivo de Entrada (`regiao.txt`)

Cada linha define um elemento da cena:

| Tipo | Significado  | Parâmetros                        |
| ---- | ------------ | --------------------------------- |
| `R`  | Retângulo    | id redução x y **altura largura** |
| `C`  | Círculo      | id redução x y raio               |
| `L`  | Linha        | id redução x1 y1 x2 y2            |
| `F`  | Fonte de luz | id intensidade x y                |
| `P`  | Receptor     | id x y                            |

---

## 🧮 Funcionamento

Cada fonte emite uma intensidade inicial.  
Para cada ponto receptor:

1. O algoritmo verifica se o segmento entre a fonte e o ponto cruza obstáculos.
2. A cada interseção, aplica-se um fator de redução proporcional ao valor de `reduction`.
3. O resultado final é a soma das intensidades atenuadas de todas as fontes.

---

## 🧠 Modelo Matemático da Iluminação

A intensidade \( I_p \) recebida em um ponto receptor é calculada pela soma das intensidades de todas as fontes após as reduções causadas pelos obstáculos:

\[
I*p = \sum*{i=1}^{N} \left( I*i \times \prod*{j=1}^{M_i} (1 - r_j) \right)
\]

Onde:

- \( I*i \) → intensidade inicial da fonte de luz \_i*
- \( r*j \) → fração de redução do obstáculo \_j* (exemplo: 0.25 para 25%)
- \( M*i \) → número de obstáculos que afetam a luz entre a fonte \_i* e o ponto receptor
- \( N \) → número total de fontes de luz

Se o caminho entre uma fonte e o ponto não for bloqueado, a luz chega sem atenuação.

---

## 🧩 Exemplos de Execução

### 🔹 **Entrada 1**

<div style="display: flex; align-items: center; justify-content: space-between;">
<pre>

R 0 65 116 1221 121 81
C 1 25 1106 1711 168
C 2 73 1456 1650 152
R 3 39 162 721 258 139
R 4 53 605 1791 236 155
F 1 934.83 1253 786
P 0 1364 1860

Saída esperada:
P0 = 68.15

</pre>
<img src="img/caso1.png" width="420"/>
</div>

---

### 🔹 **Entrada 2**

<div style="display: flex; align-items: center; justify-content: space-between;">
<pre>

L 0 11 1689 422 1353 258
L 1 76 1903 672 25 488
C 2 26 566 207 10
C 3 51 428 1509 47
L 4 82 385 795 1402 633
R 5 16 8 1248 310 294
R 6 86 484 1614 45 307
R 7 30 581 580 291 340
R 8 93 1601 987 364 118
C 9 95 193 1159 52
F 1 325.69 935 1778
F 2 626.40 780 1638
F 3 547.35 1508 833
P 0 1334 1486

Saída esperada:
P0 = 960.74

</pre>
<img src="img/caso2.png" width="420"/>
</div>

---

### 🔹 **Entrada 3**

<div style="display: flex; align-items: center; justify-content: space-between;">
<pre>
L 0 31 95 329 1889 1985
L 1 48 1162 1785 285 1355
L 2 34 680 157 1241 1131
C 3 36 633 113 48
L 4 15 45 1622 1294 1306
L 5 55 1786 82 1650 936
C 6 89 954 1036 42
C 7 22 1359 687 124
C 8 59 823 1394 144
R 9 82 751 141 173 113
C 10 45 1677 392 101
C 11 67 326 1037 77
R 12 100 165 394 89 366
R 13 63 872 1504 12 386
L 14 87 1227 422 1322 1251
L 15 32 975 1842 1276 393
R 16 10 848 1189 101 250
L 17 25 935 1619 815 1441
L 18 4 743 1147 440 122
R 19 23 277 557 115 73
L 20 73 1589 917 658 1198
R 21 99 55 347 387 145
L 22 92 45 1919 319 898
R 23 73 312 277 354 304
C 24 48 756 188 82
L 25 55 1 1694 1973 1650
R 26 25 212 636 13 206
R 27 97 1714 1238 220 300
C 28 85 832 1820 118
R 29 62 997 1454 302 208
C 30 36 232 1147 180
C 31 15 1233 1452 103
R 32 48 444 909 384 268
C 33 31 687 1386 179
L 34 89 770 1864 291 62
L 35 68 1561 701 1674 1433
L 36 29 50 1425 977 354
L 37 29 1453 1476 1928 1765
R 38 52 143 1385 72 99
R 39 11 85 407 183 34
R 40 99 23 11 326 356
C 41 74 60 689 12
C 42 84 750 1881 68
C 43 20 841 349 121
L 44 82 110 811 1161 1714
L 45 51 750 262 1410 1716
R 46 19 763 1244 268 290
C 47 93 501 687 145
L 48 51 1069 792 1689 1508
R 49 53 733 1420 181 335
F 1 620.65 756 608
F 2 652.72 212 1949
F 3 841.90 947 925
F 4 124.38 1407 327
F 5 480.66 2000 781
F 6 849.60 1865 1648
F 7 959.06 1120 1946
P 0 1860 1500
P 1 662 253
P 2 1676 1750

Saída esperada:
P0 = 1061.50
P1 = 1219.91
P2 = 978.43

</pre>
<img src="img/caso3.png" width="420"/>
</div>

---

### 🔹 **Entrada 4**

<div style="display: flex; align-items: center; justify-content: space-between;">
<pre>
L 0 76 1643 460 1285 1128
L 1 91 78 406 131 1527
F 1 697.18 633 23
F 2 705.24 394 1670
F 3 686.28 1685 1430
F 4 528.55 1480 1864
F 5 34.16 946 1851
F 6 496.01 698 1134
F 7 65.94 1510 1234
P 0 189 1931
P 1 1070 1059
P 2 1420 608
P 3 1118 1245
P 4 950 630
P 5 1920 642
P 6 1570 1138

Saída esperada:
P0 = 3213.36
P1 = 3213.36
P2 = 2239.97
P3 = 3213.36
P4 = 2641.67
P5 = 1770.55
P6 = 2683.50

</pre>
<img src="img/caso4.png" width="420"/>
</div>

### 🔹 **Entrada 5**

<div style="display: flex; align-items: center; justify-content: space-between;">
<pre>
C 0 35 1039 174 146
R 1 34 1057 89 239 148
R 2 11 1795 481 146 39
R 3 88 1704 119 236 21
C 4 24 482 185 127
R 5 4 1727 1104 167 129
C 6 18 1211 1808 192
R 7 73 1029 229 57 194
L 8 11 1462 84 1163 488
L 9 8 1579 1992 1676 402
L 10 89 788 490 1673 230
R 11 60 397 223 92 284
L 12 12 1278 7 1109 1139
R 13 49 1121 493 315 137
C 14 35 1759 1686 99
L 15 17 1953 571 85 1859
L 16 32 1734 1102 1036 1229
L 17 31 381 916 1287 158
C 18 37 572 455 112
C 19 33 399 135 56
C 20 18 1940 311 58
C 21 33 449 1323 144
C 22 76 1498 919 76
R 23 25 318 205 369 282
L 24 32 765 1556 1533 128
L 25 100 1674 186 1966 1529
C 26 16 1105 1623 85
C 27 16 1383 1396 112
C 28 70 156 251 24
C 29 60 1117 1202 140
C 30 73 460 1630 140
R 31 9 429 443 160 347
L 32 75 846 58 1603 1794
C 33 87 251 930 104
C 34 48 388 776 150
L 35 75 1767 387 1710 1219
L 36 12 390 1674 1854 1414
C 37 71 1748 1658 18
L 38 10 1519 93 1318 1383
C 39 93 648 1093 11
L 40 16 1171 1912 1694 339
R 41 44 1527 891 70 259
R 42 15 1317 809 361 370
C 43 82 603 659 148
L 44 29 4 608 722 1415
L 45 67 914 959 1952 272
C 46 89 1630 1090 184
L 47 80 89 1171 1526 1743
C 48 8 1781 249 101
L 49 57 268 1457 1937 182
L 50 50 848 715 1615 1986
C 51 21 370 179 95
L 52 73 842 1313 1429 298
L 53 86 1523 1317 577 1080
L 54 90 526 15 1847 968
C 55 31 1596 182 55
L 56 64 1461 153 562 175
R 57 75 1312 341 366 226
R 58 74 1037 910 41 23
C 59 2 108 484 48
L 60 49 119 1699 949 872
L 61 6 157 95 1548 1399
C 62 22 453 1239 97
C 63 71 1260 201 95
R 64 23 553 1227 182 332
L 65 16 1235 1058 564 1992
R 66 36 1544 584 317 175
R 67 21 304 922 184 40
L 68 96 1273 1523 420 1483
L 69 87 655 1810 51 1535
C 70 92 456 105 14
R 71 75 1816 1694 96 217
L 72 35 827 1946 1335 1495
R 73 41 185 1475 335 322
C 74 2 941 1130 114
C 75 100 182 1698 110
L 76 64 95 176 1772 1911
L 77 19 896 1006 1031 1952
R 78 88 1094 1 168 297
C 79 84 1616 509 116
C 80 38 1073 286 148
C 81 23 1169 685 11
R 82 88 1019 1243 399 74
L 83 22 221 173 246 1658
L 84 83 977 997 1695 1952
C 85 25 792 1140 9
R 86 17 1004 1741 248 122
R 87 7 334 1654 311 73
L 88 39 1597 520 1904 1969
L 89 70 444 548 267 1619
C 90 87 444 1648 37
C 91 91 1548 793 11
C 92 48 513 1481 124
L 93 88 1089 673 1433 1476
C 94 16 441 768 103
C 95 76 857 1256 181
L 96 8 1481 1744 1390 1779
C 97 87 1408 1447 90
L 98 20 465 76 311 1672
C 99 63 827 513 22
C 100 51 488 1268 162
R 101 54 1633 253 128 100
R 102 50 1548 337 319 283
R 103 23 1904 111 20 191
L 104 64 1069 833 1936 1663
C 105 87 1101 921 9
L 106 100 1782 1593 1164 329
L 107 29 1264 1269 188 1299
L 108 83 119 694 1692 1108
C 109 47 1847 347 100
L 110 78 1579 1685 799 41
C 111 28 1075 1158 111
C 112 67 514 988 152
L 113 95 1275 1927 870 309
C 114 76 552 1736 47
C 115 32 598 127 8
C 116 79 1725 1520 53
R 117 84 1496 468 45 264
R 118 70 1532 329 307 272
R 119 11 1781 35 181 350
R 120 81 1499 852 395 367
C 121 7 1380 1785 33
C 122 59 329 1342 9
C 123 83 480 1201 171
L 124 15 1263 1783 1277 1846
C 125 53 679 919 178
R 126 89 572 1046 251 340
R 127 81 637 1459 40 140
C 128 39 1214 527 106
C 129 82 1787 1022 133
C 130 49 930 1376 170
C 131 17 486 484 16
R 132 76 942 1607 140 26
R 133 5 1093 1697 39 80
C 134 64 556 314 56
C 135 38 1561 1082 178
L 136 71 1721 1247 1043 1933
R 137 72 1009 1032 195 35
R 138 26 489 1549 340 204
L 139 100 636 1132 1624 1886
R 140 77 532 318 388 207
R 141 51 1127 1379 362 146
C 142 53 1679 770 20
R 143 60 1376 217 87 188
R 144 56 248 400 356 342
L 145 37 1523 1241 429 1354
C 146 75 1562 1298 4
C 147 23 1654 659 162
R 148 3 1307 433 188 125
C 149 2 758 136 116
R 150 37 746 494 358 185
L 151 80 292 1946 120 1263
L 152 39 1164 385 1584 678
R 153 33 38 789 152 150
C 154 18 846 346 118
L 155 44 1509 1635 1130 506
L 156 31 470 92 1940 699
L 157 53 1061 753 1164 459
R 158 47 796 1276 230 40
L 159 40 90 223 993 215
R 160 76 755 879 43 131
L 161 80 117 706 788 299
C 162 88 1194 279 69
L 163 47 667 100 418 504
C 164 2 1162 586 34
C 165 24 385 764 119
L 166 15 1926 1609 149 657
R 167 29 1422 92 148 388
R 168 76 1726 1612 84 378
L 169 48 1275 1954 1638 525
R 170 55 481 544 321 134
L 171 45 901 64 1390 885
L 172 94 1051 528 1604 1242
C 173 69 1488 979 91
L 174 17 298 576 1468 1737
C 175 40 353 931 69
C 176 4 1732 1918 16
R 177 36 1061 50 342 243
C 178 3 1502 1642 36
L 179 67 1145 374 1496 900
R 180 40 1320 1225 244 359
L 181 32 1288 575 709 286
C 182 71 258 1513 87
R 183 82 744 35 86 36
C 184 100 840 1256 155
L 185 86 898 1466 1145 1309
L 186 71 144 731 718 1460
L 187 37 1643 376 1743 1651
L 188 39 1538 923 801 743
C 189 88 1820 1783 156
R 190 90 995 1821 245 9
L 191 83 737 96 273 28
L 192 33 1191 104 1654 85
C 193 51 652 1003 95
C 194 98 1630 1802 19
R 195 23 503 1461 316 398
C 196 79 1519 1067 106
L 197 32 640 1578 1370 641
C 198 54 966 1352 74
R 199 73 1602 434 165 298
F 1 820.22 645 41
F 2 44.03 988 791
F 3 914.10 708 1644
F 4 298.88 947 206
F 5 534.63 539 126
F 6 913.91 1571 1134
F 7 291.04 1332 1905
F 8 687.77 1098 1365
F 9 692.00 1637 1978
F 10 748.65 1339 702
F 11 948.52 481 11
F 12 495.81 750 1070
F 13 675.09 427 710
F 14 948.34 96 271
F 15 908.91 87 1715
F 16 449.94 1164 373
F 17 864.22 1742 1219
F 18 592.60 155 32
F 19 33.07 210 636
F 20 268.36 155 375
P 0 1002 17
P 1 29 1338
P 2 548 1243
P 3 1490 1760
P 4 1442 1115
P 5 483 1619
P 6 1400 464
P 7 1081 241
P 8 906 597
P 9 881 1956

Saída esperada:
P0 = 1784.44
P1 = 376.05
P2 = 0.03
P3 = 0.00
P4 = 0.00
P5 = 54.07
P6 = 0.00
P7 = 42.95
P8 = 16.96
P9 = 385.82

</pre>
<img src="img/caso5.png" width="420"/>
</div>

---

## 👨‍💻 Autor

Desenvolvido por **Arthur Aguiar**  
📅 2025 — Projeto de simulação geométrica e física da luz
