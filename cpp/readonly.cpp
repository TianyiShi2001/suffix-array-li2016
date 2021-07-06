#include <algorithm>
#include <cstddef>
#include <iostream>
#include <span>
#include <tuple>
#include <cmath>
#include <random>
#include <vector>

using namespace std;

using Character = uint32_t;

template <class T>
class Solver
{
public:
    span<T, dynamic_extent> t;
    span<size_t, dynamic_extent> sa;
    T sigma;
    size_t n;
    T d;
    Solver(span<T, dynamic_extent> t, span<size_t, dynamic_extent> sa, T sigma) : t(t), sa(sa), sigma(sigma)
    {
        n = t.size();
        d = ceil(static_cast<float>(sigma) / static_cast<float>(n));
    }
    tuple<bool, size_t, size_t, size_t> count_l_s_lms_lml()
    {
        size_t l = 1;   // the char before sentinel must be L (index is n-2)
        size_t s = 1;   // sentinel at n-1
        size_t lms = 1; // sentinel
        size_t lml = 0;
        bool t_i_is_s = false; // `t[n - 2]` must be L, because it is greater than the sentinel at `s[n - 1]`
        bool t_im1_is_s;
        size_t t_i = t[n - 2];
        size_t t_im1;
        for (size_t i_minus_1 = n - 2; i_minus_1-- > 0;)
        {

            t_im1 = t[i_minus_1];
            t_im1_is_s = t_im1 < t_i || (t_im1 == t_i && t_i_is_s);
            if (t_im1_is_s)
            {
                s += 1;
                if (!t_i_is_s)
                {
                    // `t[i]` is LML
                    lml += 1;
                }
            }
            else
            {
                // `t[i-1]` is L
                l += 1;
                if (t_i_is_s)
                {
                    // `t[i]` is LMS
                    lms += 1;
                }
            }

            t_i = t_im1;
            t_i_is_s = t_im1_is_s;
        }
        if (l <= s)
        {
            return tuple{true, lms, l, s};
        }
        else
        {
            return tuple{false, lml, l, s};
        }
    }

    void sort_lms_chars(size_t n1)
    {
        T lo_char = 1;
        T hi_char;
        T range;
        size_t output_curr_head = n - n1 + 1;
        T half_n = n / 2 + 1;
        if (n % 2 == 1)
        {
            half_n += 1;
        }
        while (true)
        {
            hi_char = lo_char + half_n;
            range = hi_char - lo_char;
            bool t_i_is_s = false; // t[n-2] must be L
            bool t_im1_is_s;
            T t_i = t[n - 2];
            T t_im1;
            for (size_t im1 = n - 2; im1-- > 0;)
            {
                t_im1 = t[im1];
                t_im1_is_s = t_im1 < t_i || (t_im1 == t_i && t_i_is_s);
                if (!t_im1_is_s && t_i_is_s)
                {
                    // LMS
                    if (lo_char <= t_i && t_i < hi_char)
                    {
                        // if in range
                        sa[t_i - lo_char] += 1;
                    }
                }
                t_i = t_im1;
                t_i_is_s = t_im1_is_s;
            }
            // accumulation
            size_t prev = sa[0];
            size_t *curr;
            for (size_t i = 1; i < range; i++)
            {
                curr = &sa[i];
                *curr += prev;
                prev = *curr;
            }
            // `prev` is the total number of LMS chars in this interval,
            // and will be added to `output_curr_head` after processing
            // this interval
            t_i_is_s = false;
            t_i = t[n - 2];
            size_t i = n - 2;
            for (size_t im1 = n - 2; im1-- > 0;)
            {
                t_im1 = t[im1];
                t_im1_is_s = t_im1 < t_i || (t_im1 == t_i && t_i_is_s);
                if (!t_im1_is_s && t_i_is_s)
                {
                    // LMS
                    if (lo_char <= t_i && t_i < hi_char)
                    {
                        // if in range
                        size_t *idx_in_output_without_offset = &sa[t_i - lo_char];
                        *idx_in_output_without_offset -= 1;
                        sa[output_curr_head + *idx_in_output_without_offset] = i;
                    }
                }
                i = im1;
                t_i = t_im1;
                t_i_is_s = t_im1_is_s;
            }
            fill(sa.begin(), sa.begin() + range, 0);
            if (hi_char > sigma)
            {
                break;
            }
            lo_char = hi_char;
            output_curr_head += prev;
        }
        sa[n - n1] = n - 1;
    }

    void sort_lml_chars(size_t n1)
    {
        T lo_char = 1;
        T hi_char;
        T range;
        size_t output_curr_head = n - n1;
        T half_n = n / 2 + 1;
        if (n % 2 == 0)
        {
            half_n += 1;
        }
        while (true)
        {
            hi_char = lo_char + half_n;
            range = hi_char - lo_char;
            bool t_i_is_s = false; // t[n-2] must be L
            bool t_im1_is_s;
            T t_i = t[n - 2];
            T t_im1;
            for (size_t im1 = n - 2; im1-- > 0;)
            {
                t_im1 = t[im1];
                t_im1_is_s = t_im1 < t_i || (t_im1 == t_i && t_i_is_s);
                if (t_im1_is_s && !t_i_is_s)
                {
                    // LML
                    if (lo_char <= t_i && t_i < hi_char)
                    {
                        // if in range
                        sa[t_i - lo_char] += 1;
                    }
                }
                t_i = t_im1;
                t_i_is_s = t_im1_is_s;
            }
            // accumulation
            size_t prev = sa[0];
            size_t *curr;
            for (size_t i = 1; i < range; i++)
            {
                curr = &sa[i];
                *curr += prev;
                prev = *curr;
            }
            // `prev` is the total number of LMS chars in this interval,
            // and will be added to `output_curr_head` after processing
            // this interval
            t_i_is_s = false;
            t_i = t[n - 2];
            size_t i = n - 2;
            for (size_t im1 = n - 2; im1-- > 0;)
            {
                t_im1 = t[im1];
                t_im1_is_s = t_im1 < t_i || (t_im1 == t_i && t_i_is_s);
                if (t_im1_is_s && !t_i_is_s)
                {
                    // LML
                    if (lo_char <= t_i && t_i < hi_char)
                    {
                        // if in range
                        size_t *idx_in_output_without_offset = &sa[t_i - lo_char];
                        *idx_in_output_without_offset -= 1;
                        sa[output_curr_head + *idx_in_output_without_offset] = i;
                    }
                }
                i = im1;
                t_i = t_im1;
                t_i_is_s = t_im1_is_s;
            }
            fill(sa.begin(), sa.begin() + range, 0);
            if (hi_char > sigma)
            {
                break;
            }
            lo_char = hi_char;
            output_curr_head += prev;
        }
    }

    void print_sa()
    {
        for (auto &&i : sa)
        {
            cout << i << " ";
        }
        cout << "\n"
             << endl;
    }
};

int main()
{
    for (size_t i = 0; i < 10; i++)
    {
        uint16_t sigma = 500;
        size_t n = 10;
        std::random_device rd;                                 // only used once to initialise (seed) engine
        std::mt19937 rng(rd());                                // random-number engine used (Mersenne-Twister in this case)
        std::uniform_int_distribution<uint16_t> uni(1, sigma); // guaranteed unbiased

        vector<uint16_t> t(n);
        for (size_t i = 0; i < n; i++)
        {
            t[i] = uni(rng);
        }
        t.push_back(0);

        vector<size_t> sa(10, 0);

        auto solver = Solver(span(t), span(sa), sigma);
        for (auto &&c : t)
        {
            cout << c << " ";
        }
        cout << endl;

        auto [a, b, c, d] = solver.count_l_s_lms_lml();
        cout << a << " " << b << " " << c << " " << d << endl;
        if (a)
        {
            solver.sort_lms_chars(b);
        }
        else
        {
            solver.sort_lml_chars(b);
        }

        solver.print_sa();
    }
}