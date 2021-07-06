use li2016::{mutable::Li2016, utils::random_uniform_vec};

fn main() {
    solve(500, 1_000_000);
}

fn solve(sigma: u32, len: usize) {
    let mut s = random_uniform_vec(1, sigma, len);
    s.push(0);
    let mut sa = vec![0; s.len()];
    let mut solver = Li2016::init(&mut s, &mut sa, Some(sigma as usize));
    solver.solve(true);
    assert!(!sa.is_empty());
}
