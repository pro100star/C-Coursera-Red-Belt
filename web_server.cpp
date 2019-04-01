void Stats::AddMethod(string_view method) {
    if (this->method.find(method) != this->method.end()) {
        ++this->method[method];
    } else {
        ++this->method["UNKNOWN"];
    }
}

void Stats::AddUri(string_view uri) {
    if (this->uri.find(uri) != this->uri.end()) {
        ++this->uri[uri];
    } else {
        ++this->uri["unknown"];
    }
}

const map<string_view, int>& Stats::GetMethodStats() const {
    return method;
}

const map<string_view, int>& Stats::GetUriStats() const {
    return uri;
}

HttpRequest ParseRequest(string_view line) {
    HttpRequest tmp;
    vector<string_view> words = split(line);
    tmp.method = words[0];
    tmp.uri = words[1];
    tmp.protocol = words[2];
    return tmp;
}
