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
<table>
    <tr><th></th><th>0</th><th>1</th><th>2</th><th>3</th><th>4</th><th>5</th><th>6</th><th>7</th><th>8</th><th>9</th><th>A</th><th>B</th><th>C</th><th>D</th><th>E</th><th>F</th></tr>
    <tr><th>0</th><td>9C</td><td>F2</td><td>14</td><td>C1</td><td>8E</td><td>CB</td><td>B2</td><td>65</td><td>97</td><td>7A</td><td>60</td><td>17</td><td>92</td><td>F9</td><td>78</td><td>41</td></tr>
    <tr><th>1</th><td>07</td><td>4C</td><td>67</td><td>6D</td><td>66</td><td>4A</td><td>30</td><td>7D</td><td>53</td><td>9D</td><td>B5</td><td>BC</td><td>C3</td><td>CA</td><td>F1</td><td>04</td></tr>
    <tr><th>2</th><td>03</td><td>EC</td><td>D0</td><td>38</td><td>B0</td><td>ED</td><td>AD</td><td>C4</td><td>DD</td><td>56</td><td>42</td><td>BD</td><td>A0</td><td>DE</td><td>1B</td><td>81</td></tr>
    <tr><th>3</th><td>55</td><td>44</td><td>5A</td><td>E4</td><td>50</td><td>DC</td><td>43</td><td>63</td><td>09</td><td>5C</td><td>74</td><td>CF</td><td>0E</td><td>AB</td><td>1D</td><td>3D</td></tr>
    <tr><th>4</th><td>6B</td><td>02</td><td>5D</td><td>28</td><td>E7</td><td>C6</td><td>EE</td><td>B4</td><td>D9</td><td>7C</td><td>19</td><td>3E</td><td>5E</td><td>6C</td><td>D6</td><td>6E</td></tr>
    <tr><th>5</th><td>2A</td><td>13</td><td>A5</td><td>08</td><td>B9</td><td>2D</td><td>BB</td><td>A2</td><td>D4</td><td>96</td><td>39</td><td>E0</td><td>BA</td><td>D7</td><td>82</td><td>33</td></tr>
    <tr><th>6</th><td>0D</td><td>5F</td><td>26</td><td>16</td><td>FE</td><td>22</td><td>AF</td><td>00</td><td>11</td><td>C8</td><td>9E</td><td>88</td><td>8B</td><td>A1</td><td>7B</td><td>87</td></tr>
    <tr><th>7</th><td>27</td><td>E6</td><td>C7</td><td>94</td><td>D1</td><td>5B</td><td>9B</td><td>F0</td><td>9F</td><td>DB</td><td>E1</td><td>8D</td><td>D2</td><td>1F</td><td>6A</td><td>90</td></tr>
    <tr><th>8</th><td>F4</td><td>18</td><td>91</td><td>59</td><td>01</td><td>B1</td><td>FC</td><td>34</td><td>3C</td><td>37</td><td>47</td><td>29</td><td>E2</td><td>64</td><td>69</td><td>24</td></tr>
    <tr><th>9</th><td>0A</td><td>2F</td><td>73</td><td>71</td><td>A9</td><td>84</td><td>8C</td><td>A8</td><td>A3</td><td>3B</td><td>E3</td><td>E9</td><td>58</td><td>80</td><td>A7</td><td>D3</td></tr>
    <tr><th>A</th><td>B7</td><td>C2</td><td>1C</td><td>95</td><td>1E</td><td>4D</td><td>4F</td><td>4E</td><td>FB</td><td>76</td><td>FD</td><td>99</td><td>C5</td><td>C9</td><td>E8</td><td>2E</td></tr>
    <tr><th>B</th><td>8A</td><td>DF</td><td>F5</td><td>49</td><td>F3</td><td>6F</td><td>8F</td><td>E5</td><td>EB</td><td>F6</td><td>25</td><td>D5</td><td>31</td><td>C0</td><td>57</td><td>72</td></tr>
    <tr><th>C</th><td>AA</td><td>46</td><td>68</td><td>0B</td><td>93</td><td>89</td><td>83</td><td>70</td><td>EF</td><td>A4</td><td>85</td><td>F8</td><td>0F</td><td>B3</td><td>AC</td><td>10</td></tr>
    <tr><th>D</th><td>62</td><td>CC</td><td>61</td><td>40</td><td>F7</td><td>FA</td><td>52</td><td>7F</td><td>FF</td><td>32</td><td>45</td><td>20</td><td>79</td><td>CE</td><td>EA</td><td>BE</td></tr>
    <tr><th>E</th><td>CD</td><td>15</td><td>21</td><td>23</td><td>D8</td><td>B6</td><td>0C</td><td>3F</td><td>54</td><td>1A</td><td>BF</td><td>98</td><td>48</td><td>3A</td><td>75</td><td>77</td></tr>
    <tr><th>F</th><td>2B</td><td>AE</td><td>36</td><td>DA</td><td>7E</td><td>86</td><td>35</td><td>51</td><td>05</td><td>12</td><td>B8</td><td>A6</td><td>9A</td><td>2C</td><td>06</td><td>4B</td></tr>
</table>

### SBOX-Decryption Table
<table>
    <tr><th></th><th>0</th><th>1</th><th>2</th><th>3</th><th>4</th><th>5</th><th>6</th><th>7</th><th>8</th><th>9</th><th>A</th><th>B</th><th>C</th><th>D</th><th>E</th><th>F</th></tr>
    <tr><th>0</th><td>67</td><td>84</td><td>41</td><td>20</td><td>1F</td><td>F8</td><td>FE</td><td>10</td><td>53</td><td>38</td><td>90</td><td>C3</td><td>E6</td><td>60</td><td>3C</td><td>CC</td></tr>
    <tr><th>1</th><td>CF</td><td>68</td><td>F9</td><td>51</td><td>02</td><td>E1</td><td>63</td><td>0B</td><td>81</td><td>4A</td><td>E9</td><td>2E</td><td>A2</td><td>3E</td><td>A4</td><td>7D</td></tr>
    <tr><th>2</th><td>DB</td><td>E2</td><td>65</td><td>E3</td><td>8F</td><td>BA</td><td>62</td><td>70</td><td>43</td><td>8B</td><td>50</td><td>F0</td><td>FD</td><td>55</td><td>AF</td><td>91</td></tr>
    <tr><th>3</th><td>16</td><td>BC</td><td>D9</td><td>5F</td><td>87</td><td>F6</td><td>F2</td><td>89</td><td>23</td><td>5A</td><td>ED</td><td>99</td><td>88</td><td>3F</td><td>4B</td><td>E7</td></tr>
    <tr><th>4</th><td>D3</td><td>0F</td><td>2A</td><td>36</td><td>31</td><td>DA</td><td>C1</td><td>8A</td><td>EC</td><td>B3</td><td>15</td><td>FF</td><td>11</td><td>A5</td><td>A7</td><td>A6</td></tr>
    <tr><th>5</th><td>34</td><td>F7</td><td>D6</td><td>18</td><td>E8</td><td>30</td><td>29</td><td>BE</td><td>9C</td><td>83</td><td>32</td><td>75</td><td>39</td><td>42</td><td>4C</td><td>61</td></tr>
    <tr><th>6</th><td>0A</td><td>D2</td><td>D0</td><td>37</td><td>8D</td><td>07</td><td>14</td><td>12</td><td>C2</td><td>8E</td><td>7E</td><td>40</td><td>4D</td><td>13</td><td>4F</td><td>B5</td></tr>
    <tr><th>7</th><td>C7</td><td>93</td><td>BF</td><td>92</td><td>3A</td><td>EE</td><td>A9</td><td>EF</td><td>0E</td><td>DC</td><td>09</td><td>6E</td><td>49</td><td>17</td><td>F4</td><td>D7</td></tr>
    <tr><th>8</th><td>9D</td><td>2F</td><td>5E</td><td>C6</td><td>95</td><td>CA</td><td>F5</td><td>6F</td><td>6B</td><td>C5</td><td>B0</td><td>6C</td><td>96</td><td>7B</td><td>04</td><td>B6</td></tr>
    <tr><th>9</th><td>7F</td><td>82</td><td>0C</td><td>C4</td><td>73</td><td>A3</td><td>59</td><td>08</td><td>EB</td><td>AB</td><td>FC</td><td>76</td><td>00</td><td>19</td><td>6A</td><td>78</td></tr>
    <tr><th>A</th><td>2C</td><td>6D</td><td>57</td><td>98</td><td>C9</td><td>52</td><td>FB</td><td>9E</td><td>97</td><td>94</td><td>C0</td><td>3D</td><td>CE</td><td>26</td><td>F1</td><td>66</td></tr>
    <tr><th>B</th><td>24</td><td>85</td><td>06</td><td>CD</td><td>47</td><td>1A</td><td>E5</td><td>A0</td><td>FA</td><td>54</td><td>5C</td><td>56</td><td>1B</td><td>2B</td><td>DF</td><td>EA</td></tr>
    <tr><th>C</th><td>BD</td><td>03</td><td>A1</td><td>1C</td><td>27</td><td>AC</td><td>45</td><td>72</td><td>69</td><td>AD</td><td>1D</td><td>05</td><td>D1</td><td>E0</td><td>DD</td><td>3B</td></tr>
    <tr><th>D</th><td>22</td><td>74</td><td>7C</td><td>9F</td><td>58</td><td>BB</td><td>4E</td><td>5D</td><td>E4</td><td>48</td><td>F3</td><td>79</td><td>35</td><td>28</td><td>2D</td><td>B1</td></tr>
    <tr><th>E</th><td>5B</td><td>7A</td><td>8C</td><td>9A</td><td>33</td><td>B7</td><td>71</td><td>44</td><td>AE</td><td>9B</td><td>DE</td><td>B8</td><td>21</td><td>25</td><td>46</td><td>C8</td></tr>
    <tr><th>F</th><td>77</td><td>1E</td><td>01</td><td>B4</td><td>80</td><td>B2</td><td>B9</td><td>D4</td><td>CB</td><td>0D</td><td>D5</td><td>A8</td><td>86</td><td>AA</td><td>64</td><td>D8</td></tr>
</table>

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
