use num_traits::{PrimInt, Unsigned};
use std::fmt::{Debug, Display};
pub struct SuffixArray<'a, T: PrimInt + Unsigned + Display + Debug> {
    pub text: &'a [T],
    pub sa: Vec<usize>,
    pub lcp: Vec<usize>,
}

impl<'a, T> SuffixArray<'a, T>
where
    T: PrimInt + Unsigned + Display + Debug,
{
    pub fn from_str_very_naive(s: &'a [T]) -> Self {
        let mut sa = (0..s.len()).collect::<Vec<_>>();
        sa.sort_by(|&a, &b| s[a..].cmp(&s[b..]));
        // let lcp = Self::lcp(&sa, s);
        Self {
            sa,
            text: s,
            lcp: Vec::new(),
        }
    }
    fn lcp(sa: &[usize], text: &[T]) -> Vec<usize> {
        fn _lcp<T: PrimInt + Unsigned>(a: &[T], b: &[T]) -> usize {
            a.iter()
                .zip(b.iter())
                .take_while(|(ca, cb)| ca == cb)
                .count()
        }
        let mut lcps = vec![0usize; sa.len()];
        for (i, win) in sa.windows(2).enumerate() {
            lcps[i + 1] = _lcp(&text[win[0]..], &text[win[1]..]);
        }
        lcps
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use lazy_static::lazy_static;
    lazy_static! {
        static ref ABRACADABRA_STR: &'static str = "abracadabra";
        static ref ABRACADABRA: &'static [u8] = b"abracadabra";
    }
    #[test]
    fn suffix_array() {
        let sa = SuffixArray::from_str_very_naive(&*ABRACADABRA);
        assert_eq!(&sa.sa, &[10, 7, 0, 3, 5, 8, 1, 4, 6, 9, 2]);
        // assert_eq!(&sa.lcp, &[0, 1, 4, 1, 1, 0, 3, 0, 0, 0, 2]);
        // idx   sorted suffix     lcp
        // 10    a                 0
        //  7    abra              1
        //  0    abracadabra       4
        //  3    acadabra          1
        //  5    adabra            1
        //  8    bra               0
        //  1    bracadabra        3
        //  4    cadabra           0
        //  6    dabra             0
        //  9    ra                0
        //  2    racadabra         2
    }
}
