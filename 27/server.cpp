#include <exception>
#include <iostream>
#include <map>
#include <string>
#ifdef _WIN32
#include <fcntl.h>
#include <io.h>
#endif
#include <cpprest/http_listener.h>
#include <cpprest/json.h>

using namespace std;
using namespace utility;
using namespace web;
using namespace web::http;
using namespace web::http::
  experimental::listener;

#ifdef _WIN32
#define tcout std::wcout
#else
#define tcout std::cout
#endif

void handle_get(http_request req)
{
    auto& uri = req.request_uri();

    if (uri.path() != U("/sayHi")) {
        req.reply(status_codes::NotFound);
        return;
    }

    tcout << uri::decode(uri.query()) << endl;

    auto query = uri::split_query(uri.query());
    auto it = query.find(U("name"));
    if (it == query.end()) {
        req.reply(status_codes::BadRequest, U("Missing query info"));
        return;
  }

  auto answer = json::value::object(true);
  answer[U("msg")] =
      json::value(string_t(U("Hi, ")) + uri::decode(it->second) + U("!"));

  req.reply(status_codes::OK, answer);
}

int main()
{
#ifdef _WIN32
    _setmode(_fileno(stdout), _O_WTEXT);
#endif

    http_listener listener(U("http://127.0.0.1:8008/"));
    listener.support(methods::GET, handle_get);

    try {
        listener.open().wait();

        tcout << "Listening. Press ENTER to exit.\n";
        string line;
        getline(cin, line);

        listener.close().wait();
    }
    catch (const exception& e) {
        cerr << e.what() << endl;
        return 1;
    }
}
