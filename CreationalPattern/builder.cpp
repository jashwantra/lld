#include <bits/stdc++.h>
using namespace std;

class HttpRequest {
private:
    // Required
    string url;

    // Optional
    string method;
    map<string, string> headers;
    map<string, string> queryParams;
    string body;
    int timeout;

    // Private constructor, only accessible by the Builder
    HttpRequest(const string& url,
                const string& method,
                const map<string, string>& headers,
                const map<string, string>& queryParams,
                const string& body,
                int timeout)
        : url(url), method(method), headers(headers),
          queryParams(queryParams), body(body), timeout(timeout) {}

public:
    // Output details
    void print() {
        cout << "HttpRequest{" << endl;
        cout << "  url: " << url << endl;
        cout << "  method: " << method << endl;
        cout << "  headers: " << headers.size() << " item(s)" << endl;
        cout << "  queryParams: " << queryParams.size() << " item(s)" << endl;
        cout << "  body: " << (body.empty() ? "<empty>" : body) << endl;
        cout << "  timeout: " << timeout << " ms" << endl;
        cout << "}" << endl;
    }

    // Builder nested class
    class Builder {
    private:
        string url;
        string method = "GET";
        map<string, string> headers;
        map<string, string> queryParams;
        string body;
        int timeout = 30000;

    public:
        explicit Builder(const string& url) : url(url) {}

        Builder& setMethod(const string& m) {
            method = m;
            return *this;
        }

        Builder& addHeader(const string& key, const string& value) {
            headers[key] = value;
            return *this;
        }

        Builder& addQueryParam(const string& key, const string& value) {
            queryParams[key] = value;
            return *this;
        }

        Builder& setBody(const string& b) {
            body = b;
            return *this;
        }

        Builder& setTimeout(int t) {
            timeout = t;
            return *this;
        }

        HttpRequest build() const {
            return HttpRequest(url, method, headers, queryParams, body, timeout);
        }
    };
};
int main(){
    HttpRequest request1 = HttpRequest::Builder("https://api.example.com/data")
        .build();

    HttpRequest request2 = HttpRequest::Builder("https://api.example.com/submit")
        .setMethod("POST")
        .setBody("{\"key\":\"value\"}")
        .setTimeout(15000)
        .build();

    HttpRequest request3 = HttpRequest::Builder("https://api.example.com/config")
        .setMethod("PUT")
        .addHeader("X-API-Key", "secret")
        .addQueryParam("env", "prod")
        .setBody("config_payload")
        .setTimeout(5000)
        .build();

    request1.print();
    request2.print();
    request3.print();
    return 0;
}