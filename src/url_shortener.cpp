#include "url_shortener.hpp"
#include <iostream>
#include <string>

const std::string alphabet = "abcdefghijklmnopqrstuvwxyz"
                             "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                             "0123456789";

std::string UrlShortener::gencode(int number)
{
    std::string code = "";

    do
    {
        code = alphabet[number % alphabet.size()] + code;
        number /= alphabet.size();
        number--;
    } while (number >= 0);

    return code;
}

UrlShortener::UrlShortener() : count_(0), maxlength_(20) {}

std::string UrlShortener::shorten(const std::string &Url)
{
    std::string exist;

    if (url_to_code_.get(Url, exist))
    {
        return exist;
    }

    std::string code = gencode(count_);

    if (code.length() > maxlength_)
    {
        return "";
    }
    count_++;

    code_to_url_[code] = Url;
    url_to_code_[Url] = code;

    return code;
}

std::string UrlShortener::getOrig(const std::string &scode)
{
    std::string Url;

    if (code_to_url_.get(scode, Url))
    {
        code_to_url_.increment(scode);
        return Url;
    }

    return "";
}

std::string UrlShortener::getcodebyUrl(const std::string &url)
{
    std::string code;
    if (url_to_code_.get(url, code))
        return code;

    return "";
}

bool UrlShortener::contains(const std::string &code)
{
    std::string pass;
    return code_to_url_.get(code, pass);
}

bool UrlShortener::changeUrl(const std::string &code, const std::string &url)
{
    std::string oldUrl;
    if (!code_to_url_.get(code, oldUrl))
        return false;

    std::string exist;

    if (url_to_code_.get(url, exist) && exist != code)
        return false;

    url_to_code_.remove(oldUrl);
    code_to_url_[code] = url;
    url_to_code_[url] = code;
    return true;
}

bool UrlShortener::remove(const std::string &code)
{
    std::string url;

    if (!code_to_url_.get(code, url))
    {
        return false;
    }

    code_to_url_.remove(code);
    url_to_code_.remove(url);

    return true;
}

void UrlShortener::print() const
{
    code_to_url_.print();
    return;
}

void UrlShortener::printMostPopular() const
{
    std::string key, value;
    int count;
    if (!code_to_url_.getMostPopular(key, value, count))
    {
        std::cout << "Нет Ни Одной Ссылки\n";
        return;
    }
    std::cout << "Самая Популярная Ссылка:\n" << key << " -> " << value << "| " << count << '\n';
    return;
}

std::vector<std::pair<std::string, std::string>> UrlShortener::find_by_word(const std::string &word)
{
    std::vector<std::pair<std::string, std::string>> found;
    found = code_to_url_.find_by_word(word);
    return found;
}
