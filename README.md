# suffix-array-li2016

An implemenetation of (part of) the suffix array construction algorithm developed by Zhize Li *et al.* (2016). This algorithm is claimed by the authors to be in-place (i.e. **O(1)** space complexity) and runs in linear time (**O(n)** where `n` is the number of characters in the string). However in practice, the time complexity does not seem to be linear, as evident in the experimental results in their own paper and in experiments with my implementations.

## Performance

I provide both C++ and Rust implementations, which have similar performance. Li's algorithm is not faster than the naive algorithm (naive sorting of all suffixes, **which is also in-place**) with a 32-bit unsigned interger alphabet until `n` is greater than about 800,000. Here I am referring to the Rust implementation of the algorithm in section 3, which allows a mutable string and has a stronger constraint, i.e. `n >= alphabet_size`. The algorithm in section 4 (the main contribution of this paper, which operates on immutable strings and allows `alphabet_size > n`) is expected to be slower.

```
// test tests::bench_li_500_1000      ... bench:     168,711 ns/iter (+/- 27,549)
// test tests::bench_li_500_10000     ... bench:   1,356,838 ns/iter (+/- 79,133)       x 8.0  x   8.0
// test tests::bench_li_500_100000    ... bench:  14,359,321 ns/iter (+/- 1,307,696)    x10.6  x  85.1
// test tests::bench_li_500_1000000   ... bench: 180,594,903 ns/iter (+/- 13,631,112)   x12.6  x1070.4
// test tests::bench_naive_500_1000    ... bench:      90,554 ns/iter (+/- 5,723)
// test tests::bench_naive_500_10000   ... bench:   1,262,911 ns/iter (+/- 58,702)      x13.9  x  10.3
// test tests::bench_naive_500_100000  ... bench:  16,251,237 ns/iter (+/- 661,166)     x12.9  x 179.5
// test tests::bench_naive_500_1000000 ... bench: 220,851,474 ns/iter (+/- 6,532,465)   x13.6  x2438.9
```

Curiously, when testing with 10,000,000 or more characters, Li's algorithm becomes slower than the naive algorithm (the C++ implementation has similar performance). What could be the culprit?

```
test tests::bench_li_500_10000000    ... bench: 4,796,887,136 ns/iter (+/- 20,770,245)  x26.56  x28433
test tests::bench_naive_500_10000000 ... bench: 3,082,987,837 ns/iter (+/- 63,887,953)  x13.95  x34045
```