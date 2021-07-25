#include <iostream>        // std::cout/cerr/endl/wcout
#include <utility>         // std::move
#include <assert.h>        // assert
#include <stdint.h>        // uint64_t
#ifdef _WIN32
#include <fcntl.h>         // _O_WTEXT
#include <io.h>            // _setmode
#include <stdio.h>         // _fileno/stdout
#endif
#include <cpprest/json.h>  // web::json

using namespace std;
using namespace utility;
using namespace web;

#ifdef _WIN32
#define tcout std::wcout
#else
#define tcout std::cout
#endif

int main()
{
#ifdef _WIN32
    _setmode(_fileno(stdout), _O_WTEXT);
#endif

    // 测试的 JSON 字符串
    string_t json_str = U(R"(
    {
      "s": "你好，世界",
      "t": true,
      "f": false,
      "n": null,
      "i": 123,
      "d": 3.1416,
      "a": [1, 2, 3]
    })");
    tcout << "Original JSON:" << json_str << endl;

    // 保持元素顺序并分析 JSON 字符串
    json::keep_object_element_order(true);
    auto document = json::value::parse(json_str);

    // 遍历对象成员并输出类型
    static const char* type_names[] = {
        "Number", "Boolean", "String", "Object", "Array", "Null",
    };
    for (auto&& value : document.as_object()) {
        tcout << "Type of member " << value.first << " is "
              << type_names[value.second.type()] << endl;
    }

    // 检查 document 是对象
    assert(document.is_object());

    // 检查 document["s"] 是字符串
    assert(document.has_field(U("s")));
    assert(document[U("s")].is_string());
    tcout << "s = " << document[U("s")] << endl;

    // 检查 document["t"] 是字符串
    assert(document[U("t")].is_boolean());
    tcout << "t = " << (document[U("t")].as_bool() ? "true" : "false")
          << endl;

    // 检查 document["f"] 是字符串
    assert(document[U("f")].is_boolean());
    tcout << "f = " << (document[U("f")].as_bool() ? "true" : "false")
          << endl;

    // 检查 document["f"] 是空值
    tcout << "n = " << (document[U("n")].is_null() ? "null" : "?") << endl;

    // 检查 document["i"] 是整数
    assert(document[U("i")].is_number());
    assert(document[U("i")].is_integer());
    tcout << "i = " << document[U("i")] << endl;

    // 检查 document["d"] 是浮点数
    assert(document[U("d")].is_number());
    assert(document[U("d")].is_double());
    tcout << "d = " << document[U("d")] << endl;

    {
        // 检查 document["a"] 是数组
        auto& a = document[U("a")];
        assert(a.is_array());

        // 测试读取数组元素并转换成整数
        int y = a[0].as_integer();
        (void)y;

        // 遍历数组成员并输出
        tcout << "a = ";
        for (auto&& value : a.as_array()) {
            tcout << value << ' ';
        }
        tcout << endl;
    }

    // 修改 document["i"] 为长整数
    {
        uint64_t bignum = 65000;
        bignum *= bignum;
        bignum *= bignum;
        document[U("i")] = bignum;

        assert(!document[U("i")].as_number().is_int32());
        assert(document[U("i")].as_number().to_uint64() == bignum);
        tcout << "i is changed to " << document[U("i")] << endl;
    }

    // 在数组里添加数值
    {
        auto& a = document[U("a")];
        a[3] = 4;
        a[4] = 5;
        tcout << "a is changed to " << document[U("a")] << endl;
    }

    // 在 JSON 文档里添加布尔值：等号
    // 右侧 json::value 不能省
    document[U("b")] = json::value(true);

    // 构造新对象，保持多个值的顺序
    auto temp = json::value::object(true);
    // 在新对象里添加字符串：等号右侧
    // json::value 不能省
    temp[U("from")] = json::value(U("rapidjson"));
    temp[U("changed for")] = json::value(U("geekbang"));

    // 把对象赋到文档里；json::value
    // 内部使用 unique_ptr，因而使用
    // move 可以减少拷贝
    document[U("adapted")] = std::move(temp);

    // 完整输出目前的 JSON 对象
    tcout << document << endl;
}
