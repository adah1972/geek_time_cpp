/*
 * MIT License
 *
 * Copyright (c) 2021 Netcan
 * Copyright (c) 2021-2022 Wu Yongwei
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
 * NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#ifndef METAMACRO_H
#define METAMACRO_H

#define PP_THIRD_ARG(a, b, c, ...) c
#define VA_OPT_SUPPORTED_I(...) PP_THIRD_ARG(__VA_OPT__(, ), 1, 0, )
#define VA_OPT_SUPPORTED VA_OPT_SUPPORTED_I(?)

// Traditional MSVC requires a special EXPAND phase
#if (defined(_MSC_VER) && !defined(_MSVC_TRADITIONAL)) ||                  \
    (defined(_MSVC_TRADITIONAL) && _MSVC_TRADITIONAL)

#define GET_ARG_COUNT(...)                                                 \
    INTERNAL_EXPAND_ARGS_PRIVATE(INTERNAL_ARGS_AUGMENTER(__VA_ARGS__))

#define INTERNAL_ARGS_AUGMENTER(...) unused, __VA_ARGS__
#define INTERNAL_EXPAND(x) x
#define INTERNAL_EXPAND_ARGS_PRIVATE(...)                                  \
    INTERNAL_EXPAND(INTERNAL_GET_ARG_COUNT_PRIVATE(                        \
        __VA_ARGS__, 100, 99, 98, 97, 96, 95, 94, 93, 92, 91, 90, 89, 88,  \
        87, 86, 85, 84, 83, 82, 81, 80, 79, 78, 77, 76, 75, 74, 73, 72,    \
        71, 70, 69, 68, 67, 66, 65, 64, 63, 62, 61, 60, 59, 58, 57, 56,    \
        55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40,    \
        39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24,    \
        23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7,   \
        6, 5, 4, 3, 2, 1, 0))

#else  // Other compilers

#if VA_OPT_SUPPORTED  // Standardized in C++20
#define GET_ARG_COUNT(...)                                                 \
    INTERNAL_GET_ARG_COUNT_PRIVATE(                                        \
        unused __VA_OPT__(, ) __VA_ARGS__, 100, 99, 98, 97, 96, 95, 94,    \
        93, 92, 91, 90, 89, 88, 87, 86, 85, 84, 83, 82, 81, 80, 79, 78,    \
        77, 76, 75, 74, 73, 72, 71, 70, 69, 68, 67, 66, 65, 64, 63, 62,    \
        61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46,    \
        45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30,    \
        29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14,    \
        13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)
#elif defined(__GNUC__)  // Extension in GCC/Clang
#define GET_ARG_COUNT(...)                                                 \
    INTERNAL_GET_ARG_COUNT_PRIVATE(                                        \
        unused, ##__VA_ARGS__, 100, 99, 98, 97, 96, 95, 94, 93, 92, 91,    \
        90, 89, 88, 87, 86, 85, 84, 83, 82, 81, 80, 79, 78, 77, 76, 75,    \
        74, 73, 72, 71, 70, 69, 68, 67, 66, 65, 64, 63, 62, 61, 60, 59,    \
        58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43,    \
        42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27,    \
        26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11,    \
        10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)
#else  // GET_ARG_COUNT() may return 1 here
#define GET_ARG_COUNT(...)                                                 \
    INTERNAL_GET_ARG_COUNT_PRIVATE(                                        \
        unused, __VA_ARGS__, 100, 99, 98, 97, 96, 95, 94, 93, 92, 91, 90,  \
        89, 88, 87, 86, 85, 84, 83, 82, 81, 80, 79, 78, 77, 76, 75, 74,    \
        73, 72, 71, 70, 69, 68, 67, 66, 65, 64, 63, 62, 61, 60, 59, 58,    \
        57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42,    \
        41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26,    \
        25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, \
        8, 7, 6, 5, 4, 3, 2, 1, 0)
#endif

#endif

#define INTERNAL_GET_ARG_COUNT_PRIVATE(                                    \
    e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15,  \
    e16, e17, e18, e19, e20, e21, e22, e23, e24, e25, e26, e27, e28, e29,  \
    e30, e31, e32, e33, e34, e35, e36, e37, e38, e39, e40, e41, e42, e43,  \
    e44, e45, e46, e47, e48, e49, e50, e51, e52, e53, e54, e55, e56, e57,  \
    e58, e59, e60, e61, e62, e63, e64, e65, e66, e67, e68, e69, e70, e71,  \
    e72, e73, e74, e75, e76, e77, e78, e79, e80, e81, e82, e83, e84, e85,  \
    e86, e87, e88, e89, e90, e91, e92, e93, e94, e95, e96, e97, e98, e99,  \
    e100, count, ...)                                                      \
    count

#define REPEAT_0(func, i, arg)
#define REPEAT_1(func, i, arg)        func(i, arg)
#define REPEAT_2(func, i, arg, ...)   func(i, arg) REPEAT_1(func, i + 1, __VA_ARGS__)
#define REPEAT_3(func, i, arg, ...)   func(i, arg) REPEAT_2(func, i + 1, __VA_ARGS__)
#define REPEAT_4(func, i, arg, ...)   func(i, arg) REPEAT_3(func, i + 1, __VA_ARGS__)
#define REPEAT_5(func, i, arg, ...)   func(i, arg) REPEAT_4(func, i + 1, __VA_ARGS__)
#define REPEAT_6(func, i, arg, ...)   func(i, arg) REPEAT_5(func, i + 1, __VA_ARGS__)
#define REPEAT_7(func, i, arg, ...)   func(i, arg) REPEAT_6(func, i + 1, __VA_ARGS__)
#define REPEAT_8(func, i, arg, ...)   func(i, arg) REPEAT_7(func, i + 1, __VA_ARGS__)
#define REPEAT_9(func, i, arg, ...)   func(i, arg) REPEAT_8(func, i + 1, __VA_ARGS__)
#define REPEAT_10(func, i, arg, ...)  func(i, arg) REPEAT_9(func, i + 1, __VA_ARGS__)
#define REPEAT_11(func, i, arg, ...)  func(i, arg) REPEAT_10(func, i + 1, __VA_ARGS__)
#define REPEAT_12(func, i, arg, ...)  func(i, arg) REPEAT_11(func, i + 1, __VA_ARGS__)
#define REPEAT_13(func, i, arg, ...)  func(i, arg) REPEAT_12(func, i + 1, __VA_ARGS__)
#define REPEAT_14(func, i, arg, ...)  func(i, arg) REPEAT_13(func, i + 1, __VA_ARGS__)
#define REPEAT_15(func, i, arg, ...)  func(i, arg) REPEAT_14(func, i + 1, __VA_ARGS__)
#define REPEAT_16(func, i, arg, ...)  func(i, arg) REPEAT_15(func, i + 1, __VA_ARGS__)
#define REPEAT_17(func, i, arg, ...)  func(i, arg) REPEAT_16(func, i + 1, __VA_ARGS__)
#define REPEAT_18(func, i, arg, ...)  func(i, arg) REPEAT_17(func, i + 1, __VA_ARGS__)
#define REPEAT_19(func, i, arg, ...)  func(i, arg) REPEAT_18(func, i + 1, __VA_ARGS__)
#define REPEAT_20(func, i, arg, ...)  func(i, arg) REPEAT_19(func, i + 1, __VA_ARGS__)
#define REPEAT_21(func, i, arg, ...)  func(i, arg) REPEAT_20(func, i + 1, __VA_ARGS__)
#define REPEAT_22(func, i, arg, ...)  func(i, arg) REPEAT_21(func, i + 1, __VA_ARGS__)
#define REPEAT_23(func, i, arg, ...)  func(i, arg) REPEAT_22(func, i + 1, __VA_ARGS__)
#define REPEAT_24(func, i, arg, ...)  func(i, arg) REPEAT_23(func, i + 1, __VA_ARGS__)
#define REPEAT_25(func, i, arg, ...)  func(i, arg) REPEAT_24(func, i + 1, __VA_ARGS__)
#define REPEAT_26(func, i, arg, ...)  func(i, arg) REPEAT_25(func, i + 1, __VA_ARGS__)
#define REPEAT_27(func, i, arg, ...)  func(i, arg) REPEAT_26(func, i + 1, __VA_ARGS__)
#define REPEAT_28(func, i, arg, ...)  func(i, arg) REPEAT_27(func, i + 1, __VA_ARGS__)
#define REPEAT_29(func, i, arg, ...)  func(i, arg) REPEAT_28(func, i + 1, __VA_ARGS__)
#define REPEAT_30(func, i, arg, ...)  func(i, arg) REPEAT_29(func, i + 1, __VA_ARGS__)
#define REPEAT_31(func, i, arg, ...)  func(i, arg) REPEAT_30(func, i + 1, __VA_ARGS__)
#define REPEAT_32(func, i, arg, ...)  func(i, arg) REPEAT_31(func, i + 1, __VA_ARGS__)
#define REPEAT_33(func, i, arg, ...)  func(i, arg) REPEAT_32(func, i + 1, __VA_ARGS__)
#define REPEAT_34(func, i, arg, ...)  func(i, arg) REPEAT_33(func, i + 1, __VA_ARGS__)
#define REPEAT_35(func, i, arg, ...)  func(i, arg) REPEAT_34(func, i + 1, __VA_ARGS__)
#define REPEAT_36(func, i, arg, ...)  func(i, arg) REPEAT_35(func, i + 1, __VA_ARGS__)
#define REPEAT_37(func, i, arg, ...)  func(i, arg) REPEAT_36(func, i + 1, __VA_ARGS__)
#define REPEAT_38(func, i, arg, ...)  func(i, arg) REPEAT_37(func, i + 1, __VA_ARGS__)
#define REPEAT_39(func, i, arg, ...)  func(i, arg) REPEAT_38(func, i + 1, __VA_ARGS__)
#define REPEAT_40(func, i, arg, ...)  func(i, arg) REPEAT_39(func, i + 1, __VA_ARGS__)
#define REPEAT_41(func, i, arg, ...)  func(i, arg) REPEAT_40(func, i + 1, __VA_ARGS__)
#define REPEAT_42(func, i, arg, ...)  func(i, arg) REPEAT_41(func, i + 1, __VA_ARGS__)
#define REPEAT_43(func, i, arg, ...)  func(i, arg) REPEAT_42(func, i + 1, __VA_ARGS__)
#define REPEAT_44(func, i, arg, ...)  func(i, arg) REPEAT_43(func, i + 1, __VA_ARGS__)
#define REPEAT_45(func, i, arg, ...)  func(i, arg) REPEAT_44(func, i + 1, __VA_ARGS__)
#define REPEAT_46(func, i, arg, ...)  func(i, arg) REPEAT_45(func, i + 1, __VA_ARGS__)
#define REPEAT_47(func, i, arg, ...)  func(i, arg) REPEAT_46(func, i + 1, __VA_ARGS__)
#define REPEAT_48(func, i, arg, ...)  func(i, arg) REPEAT_47(func, i + 1, __VA_ARGS__)
#define REPEAT_49(func, i, arg, ...)  func(i, arg) REPEAT_48(func, i + 1, __VA_ARGS__)
#define REPEAT_50(func, i, arg, ...)  func(i, arg) REPEAT_49(func, i + 1, __VA_ARGS__)
#define REPEAT_51(func, i, arg, ...)  func(i, arg) REPEAT_50(func, i + 1, __VA_ARGS__)
#define REPEAT_52(func, i, arg, ...)  func(i, arg) REPEAT_51(func, i + 1, __VA_ARGS__)
#define REPEAT_53(func, i, arg, ...)  func(i, arg) REPEAT_52(func, i + 1, __VA_ARGS__)
#define REPEAT_54(func, i, arg, ...)  func(i, arg) REPEAT_53(func, i + 1, __VA_ARGS__)
#define REPEAT_55(func, i, arg, ...)  func(i, arg) REPEAT_54(func, i + 1, __VA_ARGS__)
#define REPEAT_56(func, i, arg, ...)  func(i, arg) REPEAT_55(func, i + 1, __VA_ARGS__)
#define REPEAT_57(func, i, arg, ...)  func(i, arg) REPEAT_56(func, i + 1, __VA_ARGS__)
#define REPEAT_58(func, i, arg, ...)  func(i, arg) REPEAT_57(func, i + 1, __VA_ARGS__)
#define REPEAT_59(func, i, arg, ...)  func(i, arg) REPEAT_58(func, i + 1, __VA_ARGS__)
#define REPEAT_60(func, i, arg, ...)  func(i, arg) REPEAT_59(func, i + 1, __VA_ARGS__)
#define REPEAT_61(func, i, arg, ...)  func(i, arg) REPEAT_60(func, i + 1, __VA_ARGS__)
#define REPEAT_62(func, i, arg, ...)  func(i, arg) REPEAT_61(func, i + 1, __VA_ARGS__)
#define REPEAT_63(func, i, arg, ...)  func(i, arg) REPEAT_62(func, i + 1, __VA_ARGS__)
#define REPEAT_64(func, i, arg, ...)  func(i, arg) REPEAT_63(func, i + 1, __VA_ARGS__)
#define REPEAT_65(func, i, arg, ...)  func(i, arg) REPEAT_64(func, i + 1, __VA_ARGS__)
#define REPEAT_66(func, i, arg, ...)  func(i, arg) REPEAT_65(func, i + 1, __VA_ARGS__)
#define REPEAT_67(func, i, arg, ...)  func(i, arg) REPEAT_66(func, i + 1, __VA_ARGS__)
#define REPEAT_68(func, i, arg, ...)  func(i, arg) REPEAT_67(func, i + 1, __VA_ARGS__)
#define REPEAT_69(func, i, arg, ...)  func(i, arg) REPEAT_68(func, i + 1, __VA_ARGS__)
#define REPEAT_70(func, i, arg, ...)  func(i, arg) REPEAT_69(func, i + 1, __VA_ARGS__)
#define REPEAT_71(func, i, arg, ...)  func(i, arg) REPEAT_70(func, i + 1, __VA_ARGS__)
#define REPEAT_72(func, i, arg, ...)  func(i, arg) REPEAT_71(func, i + 1, __VA_ARGS__)
#define REPEAT_73(func, i, arg, ...)  func(i, arg) REPEAT_72(func, i + 1, __VA_ARGS__)
#define REPEAT_74(func, i, arg, ...)  func(i, arg) REPEAT_73(func, i + 1, __VA_ARGS__)
#define REPEAT_75(func, i, arg, ...)  func(i, arg) REPEAT_74(func, i + 1, __VA_ARGS__)
#define REPEAT_76(func, i, arg, ...)  func(i, arg) REPEAT_75(func, i + 1, __VA_ARGS__)
#define REPEAT_77(func, i, arg, ...)  func(i, arg) REPEAT_76(func, i + 1, __VA_ARGS__)
#define REPEAT_78(func, i, arg, ...)  func(i, arg) REPEAT_77(func, i + 1, __VA_ARGS__)
#define REPEAT_79(func, i, arg, ...)  func(i, arg) REPEAT_78(func, i + 1, __VA_ARGS__)
#define REPEAT_80(func, i, arg, ...)  func(i, arg) REPEAT_79(func, i + 1, __VA_ARGS__)
#define REPEAT_81(func, i, arg, ...)  func(i, arg) REPEAT_80(func, i + 1, __VA_ARGS__)
#define REPEAT_82(func, i, arg, ...)  func(i, arg) REPEAT_81(func, i + 1, __VA_ARGS__)
#define REPEAT_83(func, i, arg, ...)  func(i, arg) REPEAT_82(func, i + 1, __VA_ARGS__)
#define REPEAT_84(func, i, arg, ...)  func(i, arg) REPEAT_83(func, i + 1, __VA_ARGS__)
#define REPEAT_85(func, i, arg, ...)  func(i, arg) REPEAT_84(func, i + 1, __VA_ARGS__)
#define REPEAT_86(func, i, arg, ...)  func(i, arg) REPEAT_85(func, i + 1, __VA_ARGS__)
#define REPEAT_87(func, i, arg, ...)  func(i, arg) REPEAT_86(func, i + 1, __VA_ARGS__)
#define REPEAT_88(func, i, arg, ...)  func(i, arg) REPEAT_87(func, i + 1, __VA_ARGS__)
#define REPEAT_89(func, i, arg, ...)  func(i, arg) REPEAT_88(func, i + 1, __VA_ARGS__)
#define REPEAT_90(func, i, arg, ...)  func(i, arg) REPEAT_89(func, i + 1, __VA_ARGS__)
#define REPEAT_91(func, i, arg, ...)  func(i, arg) REPEAT_90(func, i + 1, __VA_ARGS__)
#define REPEAT_92(func, i, arg, ...)  func(i, arg) REPEAT_91(func, i + 1, __VA_ARGS__)
#define REPEAT_93(func, i, arg, ...)  func(i, arg) REPEAT_92(func, i + 1, __VA_ARGS__)
#define REPEAT_94(func, i, arg, ...)  func(i, arg) REPEAT_93(func, i + 1, __VA_ARGS__)
#define REPEAT_95(func, i, arg, ...)  func(i, arg) REPEAT_94(func, i + 1, __VA_ARGS__)
#define REPEAT_96(func, i, arg, ...)  func(i, arg) REPEAT_95(func, i + 1, __VA_ARGS__)
#define REPEAT_97(func, i, arg, ...)  func(i, arg) REPEAT_96(func, i + 1, __VA_ARGS__)
#define REPEAT_98(func, i, arg, ...)  func(i, arg) REPEAT_97(func, i + 1, __VA_ARGS__)
#define REPEAT_99(func, i, arg, ...)  func(i, arg) REPEAT_98(func, i + 1, __VA_ARGS__)
#define REPEAT_100(func, i, arg, ...)  func(i, arg) REPEAT_99(func, i + 1, __VA_ARGS__)

#define CONCAT(x, y) x##y
#define PASTE(x, y) CONCAT(x, y)

#define STR(x) #x
#define STRING(x) STR(x)

#define PARE(...) __VA_ARGS__
#define EAT(...)
#define PAIR(x) PARE x  // PAIR((int) x) => PARE(int) x => int x
#define STRIP(x) EAT x  // STRIP((int) x) => EAT(int) x => x

#endif // METAMACRO_H
