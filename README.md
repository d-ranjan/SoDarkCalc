# SoDark Cipher Calculator

Implementation of SoDark-3 and SoDark-6 cypher algorithms.

## SoDark Cipher

The SoDark cipher is used to protect transmitted frames in the second and
third generation automatic link establishment (ALE) standards for high frequency
(HF) radios. The cipher is primarily meant to prevent unauthorized linking and
attacks on the availability of HF radio networks.

The SoDark-3 Algorithm is designed specifically encryption of 24-bit ALE words. It uses a
56-bit key (7 bytes), and the 64-bit seed (8 byte).

The SoDark-6 Algorithm is designed for encryption of 48-bit words. It also uses a
56-bit key (7 bytes), and the 64-bit seed (8 byte).
## High Level Algorithms

### SBOX-Encryption Table
| |0|1|2|3|4|5|6|7|8|9|A|B|C|D|E|F
|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|
0|9C|F2|14|C1|8E|CB|B2|65|97|7A|60|17|92|F9|78|41
1|07|4C|67|6D|66|4A|30|7D|53|9D|B5|BC|C3|CA|F1|04
2|03|EC|D0|38|B0|ED|AD|C4|DD|56|42|BD|A0|DE|1B|81
3|55|44|5A|E4|50|DC|43|63|09|5C|74|CF|0E|AB|1D|3D
4|6B|02|5D|28|E7|C6|EE|B4|D9|7C|19|3E|5E|6C|D6|6E
5|2A|13|A5|08|B9|2D|BB|A2|D4|96|39|E0|BA|D7|82|33
6|0D|5F|26|16|FE|22|AF|00|11|C8|9E|88|8B|A1|7B|87
7|27|E6|C7|94|D1|5B|9B|F0|9F|DB|E1|8D|D2|1F|6A|90
8|F4|18|91|59|01|B1|FC|34|3C|37|47|29|E2|64|69|24
9|0A|2F|73|71|A9|84|8C|A8|A3|3B|E3|E9|58|80|A7|D3
A|B7|C2|1C|95|1E|4D|4F|4E|FB|76|FD|99|C5|C9|E8|2E
B|8A|DF|F5|49|F3|6F|8F|E5|EB|F6|25|D5|31|C0|57|72
C|AA|46|68|0B|93|89|83|70|EF|A4|85|F8|0F|B3|AC|10
D|62|CC|61|40|F7|FA|52|7F|FF|32|45|20|79|CE|EA|BE
E|CD|15|21|23|D8|B6|0C|3F|54|1A|BF|98|48|3A|75|77
F|2B|AE|36|DA|7E|86|35|51|05|12|B8|A6|9A|2C|06|4B

### SBOX-Decryption Table
| |0|1|2|3|4|5|6|7|8|9|A|B|C|D|E|F
|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|
0|67|84|41|20|1F|F8|FE|10|53|38|90|C3|E6|60|3C|CC
1|CF|68|F9|51|02|E1|63|0B|81|4A|E9|2E|A2|3E|A4|7D
2|DB|E2|65|E3|8F|BA|62|70|43|8B|50|F0|FD|55|AF|91
3|16|BC|D9|5F|87|F6|F2|89|23|5A|ED|99|88|3F|4B|E7
4|D3|0F|2A|36|31|DA|C1|8A|EC|B3|15|FF|11|A5|A7|A6
5|34|F7|D6|18|E8|30|29|BE|9C|83|32|75|39|42|4C|61
6|0A|D2|D0|37|8D|07|14|12|C2|8E|7E|40|4D|13|4F|B5
7|C7|93|BF|92|3A|EE|A9|EF|0E|DC|09|6E|49|17|F4|D7
8|9D|2F|5E|C6|95|CA|F5|6F|6B|C5|B0|6C|96|7B|04|B6
9|7F|82|0C|C4|73|A3|59|08|EB|AB|FC|76|00|19|6A|78
A|2C|6D|57|98|C9|52|FB|9E|97|94|C0|3D|CE|26|F1|66
B|24|85|06|CD|47|1A|E5|A0|FA|54|5C|56|1B|2B|DF|EA
C|BD|03|A1|1C|27|AC|45|72|69|AD|1D|05|D1|E0|DD|3B
D|22|74|7C|9F|58|BB|4E|5D|E4|48|F3|79|35|28|2D|B1
E|5B|7A|8C|9A|33|B7|71|44|AE|9B|DE|B8|21|25|46|C8
F|77|1E|01|B4|80|B2|B9|D4|CB|0D|D5|A8|86|AA|64|D8

### SoDark-3 Encryption
```
I: byte representation of input(32 bit integer)
K: byte representation of key(64 bit integer)
S: byte representation of seed(64 bit integer)
A=I[1], B=I[2], C=I[3]
r: 1...rounds
    A(r) = SBOX_E[A(r-1) xor B(r-1) xor K[(3 * r - 3) % 7 + 1] xor S[(3 * r - 3) % 8]]
    C(r) = SBOX_E[C(r-1) xor B(r-1) xor K[(3 * r - 2) % 7 + 1] xor S[(3 * r - 2) % 8]]
    B(r) = SBOX_E[B(r-1) xor A(r) xor C(r) xor K[(3 * r - 1) % 7 + 1] xor S[(3 * r - 1) % 8]]
O={0,A,B,C}
```
### SoDark-3 Decryption
```
I: byte representation of input(32 bit integer)
K: byte representation of key(64 bit integer)
S: byte representation of seed(64 bit integer)
A=I[1], B=I[2], C=I[3]
r: rounds...1
    B(r) = SBOX_D[B(r-1)] xor A(r-1) xor C(r-1) xor K[(3 * r - 1) % 7 + 1] xor S[(3 * r - 1) % 8]
    C(r) = SBOX_D[C(r-1)] xor B(r) xor K[(3 * r - 2) % 7 + 1] xor S[(3 * r - 2) % 8]
    A(r) = SBOX_D[A(r-1)] xor B(r) xor K[(3 * r - 3) % 7 + 1] xor S[(3 * r - 3) % 8]
O={0,A,B,C}
```

### SoDark-6 Encryption
```
I: byte representation of input(64 bit integer)
K: byte representation of key(64 bit integer)
S: byte representation of seed(64 bit integer)
A=I[2], B=I[3], C=I[4], D=I[5], E=I[6], F=I[7]
r: 1...rounds
    A(r) = EBOX[A(r-1) xor B(r-1) xor F(r-1) xor K[(6 * r - 6) % 7 + 1] xor S[(6 * r - 6) % 8]]
    C(r) = EBOX[C(r-1) xor B(r-1) xor D(r-1) xor K[(6 * r - 5) % 7 + 1] xor S[(6 * r - 5) % 8]]
    E(r) = EBOX[E(r-1) xor D(r-1) xor F(r-1) xor K[(6 * r - 4) % 7 + 1] xor S[(6 * r - 4) % 8]]
    B(r) = EBOX[B(r-1) xor A(r) xor C(r) xor K[(6 * r - 3) % 7 + 1] xor S[(6 * r - 3) % 8]]
    D(r) = EBOX[D(r-1) xor C(r) xor E(r) xor K[(6 * r - 2) % 7 + 1] xor S[(6 * r - 2) % 8]]
    F(r) = EBOX[F(r-1) xor A(r) xor E(r) xor K[(6 * r - 1) % 7 + 1] xor S[(6 * r - 1) % 8]]
O={0,0,A,B,C,D,E,F}
```

### SoDark-6 Decryption
```    
I: byte representation of input(64 bit integer)
K: byte representation of key(64 bit integer)
S: byte representation of seed(64 bit integer)
A=I[2], B=I[3], C=I[4], D=I[5], E=I[6], F=I[7]
r: rounds...1
    B(r) = DBOX[B(r-1)] xor A(r-1) xor C(r-1) xor K[(6 * r - 3) % 7 + 1] xor S[(6 * r - 3) % 8]
    D(r) = DBOX[D(r-1)] xor C(r-1) xor E(r-1) xor K[(6 * r - 2) % 7 + 1] xor S[(6 * r - 2) % 8]
    F(r) = DBOX[F(r-1)] xor A(r-1) xor E(r-1) xor K[(6 * r - 1) % 7 + 1] xor S[(6 * r - 1) % 8]
    E(r) = DBOX[E(r-1)] xor D(r) xor F(r) xor K[(6 * r - 4) % 7 + 1] xor S[(6 * r - 4) % 8]
    C(r) = DBOX[C(r-1)] xor B(r) xor D(r) xor K[(6 * r - 5) % 7 + 1] xor S[(6 * r - 5) % 8]
    A(r) = DBOX[A(r-1)] xor B(r) xor F(r) xor K[(6 * r - 6) % 7 + 1] xor S[(6 * r - 6) % 8]
O={0,0,A,B,C,D,E,F}
```
