#include "stdafx.h"

struct Pingable {
	virtual std::wstring ping(const std::wstring& message) = 0;
};

struct Pong : Pingable {
	std::wstring ping(const std::wstring& message) override { return message + L" pong"; };
};

#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
using namespace utility;                    // Common utilities like string conversions
using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features
using namespace concurrency::streams;       // Asynchronous streams

struct RemotePong : Pingable {
	std::wstring ping(const std::wstring& message) override {
		std::wstring result;
		http_client client(U("http://localhost:64959/"));
		uri_builder builder(U("/api/values/"));
		builder.append(message);

		auto task = client.request(methods::GET, builder.to_string()).then([=](http_response r) {
			return r.extract_string();
		});

		task.wait();
		return task.get();

	};
};

void tryit(Pingable& pp) {
	std::wcout << pp.ping(L"ping") << std::endl;
};

