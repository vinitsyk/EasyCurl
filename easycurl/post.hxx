#ifndef post_hxx_included
#define post_hxx_included

#include <string>
#include <curl/curl.h>


class Post {

    private:

        std::string url;
        std::string data;
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

        Post ( const std::string& url ) {
            this->url = url;
        }

        auto fetch() -> void {

            CURL* curl;
            CURLcode res;

            curl_global_init(CURL_GLOBAL_DEFAULT);

            curl = curl_easy_init();

            if (curl) {

                curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

                curl_easy_setopt(curl, CURLOPT_POST, 1L);

                curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

                if ( data.length() >= 1 ){
                    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
                    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, data.length());
                }
    
                if ( cookies.length() >= 1 ){

                    curl_easy_setopt(curl, CURLOPT_COOKIE, cookies);
                }

                curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, Callback);
                curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

                res = curl_easy_perform(curl);

                if (res != CURLE_OK) {

                    response.append( std::string( curl_easy_strerror(res) ));

                }   
            }

            this->length = response.length();
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &status_code);

            curl_easy_cleanup(curl);

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

        auto setData( const std::string& data ) -> void {

            this->data = data;
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