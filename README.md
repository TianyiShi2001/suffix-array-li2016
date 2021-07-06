# suffix-array-li2016

An implemenetation of (part of) the suffix array construction algorithm developed by Zhize Li *et al.* (2016). This algorithm is claimed by the authors to be in-place i.e. **O(1)** space complexity and runs in linear time **O(n)** where `n` is the number of characters in the string. However in practice, the time complexity more closely resembles **O(nlog(n))**, as evident in the experimental results in their own paper and in experiments with my implementations.

I provide both C++ and Rust implementations, which have similar performance. Li's algorithm is slower than the naive algorithm (naive sorting of all suffixes, **which is also in-place**) with a 32-bit unsigned interger alphabet when `n` is less than (at least) 300,000,000. The actual bound is slightly higher than this because my RAM is not enough to test longer strings.
