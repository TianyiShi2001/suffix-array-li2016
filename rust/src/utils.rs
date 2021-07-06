use rand::{
    distributions::uniform::{SampleBorrow, SampleUniform, Uniform},
    thread_rng, Rng,
};
pub(crate) fn random_uniform_vec<T, X>(lo: T, hi: T, len: usize) -> Vec<X>
where
    X: SampleUniform,
    T: SampleBorrow<X> + Sized,
{
    thread_rng()
        .sample_iter(Uniform::new_inclusive(lo, hi))
        .take(len)
        .collect()
}