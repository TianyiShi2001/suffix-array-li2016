use li2016::{naive::SuffixArray, utils::random_uniform_vec};

fn main() {
    solve(500, 1_000_000);
}

fn solve(sigma: u32, len: usize) {
    let mut s = random_uniform_vec(1, sigma, len);
    s.push(0);
    let sa = SuffixArray::from_str_very_naive(&s).sa;
    assert!(!sa.is_empty());
}
