#ifndef get_hxx_included
#define get_hxx_included

#include <string>
#include <sstream>
#include <iostream>
#include <curl/curl.h>

class Get {

    private:

        std::string url;
        std::size_t length;
        std::string params;
        std::string cookies;
        std::string headers;
        std::string response;
        std::size_t status_code;

        static std::size_t Callback(void* contents, std::size_t size, std::size_t nmemb, std::string* output) {
            std::size_t total_size = size * nmemb;
            output->append(static_cast<char*>(contents), total_size);
            return total_size;
        }

    public:

        Get( const std::string& url ){
            this->url = url;
        }

        void fetch () {

            curl_global_init(CURL_GLOBAL_DEFAULT);

            CURL* curl = curl_easy_init();

            if (curl) {

                curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

                curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, Callback);
                curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

                if ( cookies.length() >= 1 ){
                    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &cookies);
                }

                curl_easy_setopt(curl, CURLOPT_HEADERDATA, &headers);

                CURLcode res = curl_easy_perform(curl);

                curl_easy_cleanup(curl);

            }

            this->length = response.length();
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &status_code);

            curl_global_cleanup();
        }

        auto setParams(const std::string& query, const std::string& params) -> void {
            this->url.append("?");
            this->url.append(query);
            this->url.append("=");
            this->url.append(params);
        }

        auto setHeaders(const std::string& key, const std::string& value) -> void {
            this->headers.append("\n");
            this->headers.append(key);
            this->headers.append(":");
            this->headers.append(value);
        }

        auto setCookies ( const std::string& jsonCookies ) -> void {

            this->cookies = jsonCookies;
        }

        auto getResponse() -> std::string& {

            return response;
        }

        auto getLength() -> std::size_t {

            return length;
        }

        auto getStatusCode() -> std::size_t {

            return status_code;
        }

        auto getHeaders() -> std::string& {

            return headers;
        }


};

#endif