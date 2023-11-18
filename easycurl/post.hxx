#ifndef post_hxx_included
#define post_hxx_included

#include <string>
#include <curl/curl.h>


class post {

    private:

        std::string url;

    public:

        post ( const std::string& url ) {
            this->url = url;
        }
};


#endif