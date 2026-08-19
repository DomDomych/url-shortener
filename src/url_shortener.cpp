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

UrlShortener::UrlShortener() : count(0), maxlength(20) {}

std::string UrlShortener::shorten(const std::string &Url)
{
    std::string exist;

    if (UrlToCode.get(Url, exist))
    {
        return exist;
    }

    std::string code = gencode(count);

    if (code.length() > maxlength)
    {
        return "";
    }
    count++;

    CodeToUrl[code] = Url;
    UrlToCode[Url] = code;

    return code;
}

std::string UrlShortener::getOrig(const std::string &scode)
{
    std::string Url;

    if (CodeToUrl.get(scode, Url))
    {
        CodeToUrl.increment(scode);
        return Url;
    }

    return "";
}

std::string UrlShortener::getcodebyUrl(const std::string &url)
{
    std::string code;
    if (UrlToCode.get(url, code))
        return code;

    return "";
}

bool UrlShortener::contains(const std::string &code)
{
    std::string pass;
    return CodeToUrl.get(code, pass);
}

bool UrlShortener::changeUrl(const std::string &code, const std::string &url)
{
    std::string oldUrl;
    if (!CodeToUrl.get(code, oldUrl))
        return false;

    std::string exist;

    if (UrlToCode.get(url, exist) && exist != code)
        return false;

    UrlToCode.remove(oldUrl);
    CodeToUrl[code] = url;
    UrlToCode[url] = code;
    return true;
}

bool UrlShortener::remove(const std::string &code)
{
    std::string url;

    if (!CodeToUrl.get(code, url))
    {
        return false;
    }

    CodeToUrl.remove(code);
    UrlToCode.remove(url);

    return true;
}

void UrlShortener::print() const
{
    CodeToUrl.print();
    return;
}

void UrlShortener::printMostPopular() const
{
    std::string key, value;
    int count;
    if (!CodeToUrl.getMostPopular(key, value, count))
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
    found = CodeToUrl.find_by_word(word);
    return found;
}
