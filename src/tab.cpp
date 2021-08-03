#include "tab.hpp"

KeyValuePair::KeyValuePair()
{
    this->enable = true;
    this->key = "key";
    this->value = "value";
    this->description = "descp";
    this->_id = (int)rand();
}

void KeyValuePair::setKey(const char *setKey)
{
    this->key = setKey;
}

void KeyValuePair::setKey(const std::string &setKey)
{
    this->key = setKey;
}

int Tab::getBodyType()
{
    return currentBodyType;
}

void Tab::setBodyType(const int bodyType)
{
    this->currentBodyType = bodyType;
}

const char *Tab::getResponse()
{
    return this->formattedBody.c_str();
}

void Tab::constructRequest()
{
    this->_params = Parameters{};
    this->payload = Payload{};
    this->_headers = Header{};

    for (auto i : this->queryParams)
    {
        if (i.enable)
            this->_params.Add({i.key, i.value});
    }

    for (auto i : this->headers)
    {
        if (i.enable)
        {
            this->_headers.insert({i.key, i.value});
        }
    }
    switch (this->currentHttpMethod)
    {
    case 0: //GET REQUEST

        break;
    case 1: //POST REQUEST
        for (auto i : this->formData)
        {
            if (i.enable)
                this->payload.Add({i.key, i.value});
        }

        if (this->rawBody.size() != 0)
        {
            this->_headers.insert({"content-type", "application/json"});
        }
        break;

    case 2: //PUT REQUEST
        for (auto i : this->formData)
        {
            if (i.enable)
                this->payload.Add({i.key, i.value});
        }
        break;

    case 3: //DELETE
        for (auto i : this->formData)
        {
            if (i.enable)
                this->payload.Add({i.key, i.value});
        }
        break;

    case 4: //HEAD
        break;

    case 5:
        break;
    };
}

void Tab::sendRequest()
{

    this->constructRequest();
    constants->db->insertUrl(this->url);

    switch (this->currentHttpMethod)
    {
    case 0:
        res = cpr::Get(Url{this->url.c_str()}, _params, constants->sslOpts, this->_headers, Timeout{constants->REQUEST_TIMEOUT});

        break;
    case 1: //POST REQUEST

        res = cpr::Post(Url{this->url.c_str()}, this->payload, constants->sslOpts, _params, this->_headers, cpr::Body({this->rawBody.c_str()}), Timeout{constants->REQUEST_TIMEOUT});

        break;

    case 2:

        res = cpr::Post(Url{this->url.c_str()}, this->payload, constants->sslOpts, _params, this->_headers, Timeout{constants->REQUEST_TIMEOUT});

    case 3:
        // DELETE

        res = cpr::Delete(Url{this->url.c_str()}, this->payload, constants->sslOpts, _params, this->_headers, Timeout{constants->REQUEST_TIMEOUT});
        break;

    case 4:
        // HEAD
        res = cpr::Head(Url{this->url.c_str()}, _params, constants->sslOpts, this->_headers, Timeout{constants->REQUEST_TIMEOUT});
        break;

    case 5:
        // OPTIONS
        res = cpr::Options(Url{this->url.c_str()}, _params, constants->sslOpts, this->_headers, Timeout{constants->REQUEST_TIMEOUT});
        break;
    };

    if (constants->jsonIndent && res.header["content-type"].find("application/json") != std::string::npos)
    {
        auto j = json::parse(res.text.c_str());
        this->formattedBody = j.dump(4);
    }
    else if (constants->htmlIndent && res.text.find("html") != std::string::npos)
    {
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
        if (rc > 1)                        // If error, force output.
            rc = (tidyOptSetBool(tdoc, TidyForceOutput, yes) ? rc : -1);
        if (rc >= 0)
            rc = tidySaveBuffer(tdoc, &output); // Pretty Print
        this->formattedBody = reinterpret_cast<char const *>(output.bp);
        tidyBufFree(&output);
        tidyBufFree(&errbuf);
        tidyRelease(tdoc);
    }
    else
    {
        this->formattedBody = res.text.c_str();
    }
}

void Tab::updateTitle()
{
    this->title = this->url + "##" + std::to_string(rand());
}
double Tab::getTimeElapsed()
{
    return res.elapsed;
}
int Tab::getStatusCode()
{
    return res.status_code;
}
Tab::Tab(size_t index)
{
    this->title = "Untitled" + std::to_string(index);
    this->url = "http://localhost:1234";
    isOpen = true;
    statusCode = 0;
    currentHttpMethod = 0;
    currentBodyType = 0;
    timeElapsed = 0;
    this->formattedBody = "";
}