#include "tab.hpp"

KeyValuePair::KeyValuePair() {
  this->enable = true;
  this->key = "key";
  this->value = "value";
  this->description = "descp";
  this->_id = (int)rand();
}

void KeyValuePair::setKey(const char *setKey) { this->key = setKey; }

void Tab::loadTabFromHistory(const request &h) {
  this->url = h.url;
  this->currentHttpMethod = h.method;
}

void KeyValuePair::setKey(const std::string &setKey) { this->key = setKey; }

int Tab::getBodyType() { return currentBodyType; }

void Tab::setBodyType(const int bodyType) { this->currentBodyType = bodyType; }

const char *Tab::getResponse() { return this->formattedBody.c_str(); }

void Tab::constructRequest() {
  Logger *logger = Logger::getInstance();
  this->_params = Parameters{};
  this->payload = Payload{};
  this->_headers = Header{};

  for (auto i : this->queryParams) {
    if (i.enable)
      this->_params.Add({i.key, i.value});
  }

  for (auto i : this->headers) {
    if (i.enable) {
      this->_headers.insert({i.key, i.value});
    }
  }
  switch (this->currentHttpMethod) {
  case 0: // GET REQUEST
    logger->info("constructing GET request");

    break;
  case 1: // POST REQUEST
    logger->info("constructing POST request");

    for (auto i : this->formData) {
      if (i.enable)
        this->payload.Add({i.key, i.value});
    }

    if (this->rawBody.size() != 0) {
      this->_headers.insert({"content-type", "application/json"});
    }
    break;

  case 2: // PUT REQUEST
    logger->info("constructing PUT request");

    for (auto i : this->formData) {
      if (i.enable)
        this->payload.Add({i.key, i.value});
    }
    break;

  case 3: // DELETE
    logger->info("constructing DELETE request");

    for (auto i : this->formData) {
      if (i.enable)
        this->payload.Add({i.key, i.value});
    }
    break;

  case 4: // HEAD
    logger->info("constructing HEAD request");

    break;

  case 5:
    break;
  };
}

void Tab::sendRequest() {
  this->constructRequest();
  Logger *logger = Logger::getInstance();
  logger->info("sending request to ", {url.c_str()});
  int method;
  switch (this->currentHttpMethod) {
  case 0:
  // GET REQUEST
    method = 0;
    res =
        cpr::Get(Url{this->url.c_str()}, _params, constants->sslOpts, Verbose{},
                 this->_headers, Timeout{constants->REQUEST_TIMEOUT});
    break;
  case 1: // POST REQUEST
    method = 1;
    res = cpr::Post(Url{this->url.c_str()}, this->payload, constants->sslOpts,
                    Verbose{}, _params, this->_headers,
                    cpr::Body({this->rawBody.c_str()}),
                    Timeout{constants->REQUEST_TIMEOUT});
    break;

  case 2:
    method = 2;
    res = cpr::Put(Url{this->url.c_str()}, this->payload, constants->sslOpts,
                   Verbose{}, _params, this->_headers,
                   Timeout{constants->REQUEST_TIMEOUT});
    break;

  case 3:
    // DELETE
    method = 3;
    res = cpr::Delete(Url{this->url.c_str()}, this->payload, constants->sslOpts,
                      Verbose{}, _params, this->_headers,
                      Timeout{constants->REQUEST_TIMEOUT});

    break;

  case 4:
    // HEAD
    method = 4;
    res = cpr::Head(Url{this->url.c_str()}, _params, constants->sslOpts,
                    Verbose{}, this->_headers,
                    Timeout{constants->REQUEST_TIMEOUT});

    break;

  case 5:
    // OPTIONS
    method = 5;
    res = cpr::Options(Url{this->url.c_str()}, _params, constants->sslOpts,
                       Verbose{}, this->_headers,
                       Timeout{constants->REQUEST_TIMEOUT});

    break;
  };
  logger->info("received response from", {url.c_str()});

  constants->db->insertUrl(this->url, method);

  if(res.error){
    this->formattedBody = res.error.message;
    this->statusCode = 0;
    return;
  }

  if (constants->jsonIndent && res.header["content-type"].find(
                                   "application/json") != std::string::npos) {
    logger->info("formatting JSON");

    // auto j = json::parse(res.text.c_str());
    auto parsedJsonFuture = pool.enqueue([&]{
      auto parsedJson =  json::parse(res.text.c_str());
      this->formattedBody = parsedJson.dump(4);
      });
  } else if (constants->htmlIndent &&
             res.text.find("html") != std::string::npos) {
    logger->info("formatting HTML");

    pool.enqueue([&]{
      TidyBuffer output = {0};
    TidyBuffer errbuf = {0};
    int rc = -1;
    Bool ok;

    TidyDoc tdoc = tidyCreate(); // Initialize "document"
    // printf("Tidying:\t%s\n", input);

    ok = tidyOptSetBool(tdoc, TidyXhtmlOut, yes); // Convert to XHTML
    tidyOptSetInt(tdoc, TidyIndentContent, TidyAutoState);
    if (ok)
      rc = tidySetErrorBuffer(tdoc, &errbuf); // Capture diagnostics
    if (rc >= 0)
      rc = tidyParseString(tdoc, res.text.c_str()); // Parse the input
    if (rc >= 0)
      rc = tidyCleanAndRepair(tdoc); // Tidy it up!
    if (rc >= 0)
      rc = tidyRunDiagnostics(tdoc); // Kvetch
    if (rc > 1)                      // If error, force output.
      rc = (tidyOptSetBool(tdoc, TidyForceOutput, yes) ? rc : -1);
    if (rc >= 0)
      rc = tidySaveBuffer(tdoc, &output); // Pretty Print
    this->formattedBody = reinterpret_cast<char const *>(output.bp);
    tidyBufFree(&output);
    tidyBufFree(&errbuf);
    tidyRelease(tdoc);
    });
  } else {
    this->formattedBody = res.text.c_str();
  }
}

void Tab::updateTitle() {
  this->title = this->url + "##" + std::to_string(rand());
}
double Tab::getTimeElapsed() { return res.elapsed; }
int Tab::getStatusCode() { return res.status_code; }
Tab::Tab(size_t index) {
  this->title = "Untitled" + std::to_string(index);
  this->url = "https://google.com";
  isOpen = true;
  statusCode = 0;
  currentHttpMethod = 0;
  currentBodyType = 0;
  timeElapsed = 0;
  this->formattedBody = "";
}