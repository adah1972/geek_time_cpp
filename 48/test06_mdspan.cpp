#include <version>   // __cpp_lib_mdspan

#if __cpp_lib_mdspan >= 202207L

#include <array>     // std::array
#include <cstddef>   // std::size_t
#include <cstdint>   // std::uint32_t
#include <iostream>  // std::cout
#include <mdspan>    // std::mdspan/dextents/layout_stride
#include <numeric>   // std::iota
#include <vector>    // std::vector

using namespace std;

template <typename T, typename Extents, typename Layout, typename Accessor>
void print_mdspan(mdspan<T, Extents, Layout, Accessor> m)
{
    static_assert(m.rank() == 2, "print_mdspan only supports 2D mdspans.");
    using index_type = Extents::index_type;

    for (index_type r = 0; r < m.extent(0); ++r) {
        for (index_type c = 0; c < m.extent(1); ++c) {
            cout << m[r, c] << '\t';
        }
        cout << '\n';
    }
}

using Exts2d = dextents<uint32_t, 2>;

int main()
{
    constexpr size_t src_height = 4;
    constexpr size_t src_width = 5;
    vector<float> source_data(src_height * src_width);

    // Fill with data: 1, 2, ...
    iota(source_data.begin(), source_data.end(), 1.0F);

    // This mdspan has layout_right
    mdspan<float, Exts2d> ms{source_data.data(), src_height, src_width};

    cout << "Original 4x5 data:\n";
    print_mdspan(ms);
    cout << '\n';

    constexpr size_t view_height = 2;
    constexpr size_t view_width = 2;
    Exts2d extents_subview{view_height, view_width};
    array<size_t, 2> strides{src_width, 1};
    layout_stride::mapping<Exts2d> map{extents_subview, strides};

    // This mdspan has layout_stride
    mdspan subview{&ms[1, 2], map};

    cout << "2x2 subview created with custom stride (5, 1):\n";
    print_mdspan(subview);

    cout << "\nVerification: subview[1, 1] = " << subview[1, 1] << '\n';
}

#else

#include <iostream>  // std::cout

int main()
{
    std::cout << "std::mdspan is not supported in your environment\n";
}

#endif
