#include "url_shortener.hpp"
#include <iostream>
#include <vector>

int main()
{
    UrlShortener shortener;

    std::cout << "1. Добавление ссылок\n";

    std::string code1 =
        shortener.shorten("https://github.com/DomDomych/Stkn_Alg_Fourth_Lab/tree/develop");
    std::string code2 =
        shortener.shorten("https://github.com/DomDomych/Stkn_Alg_Third_Lab/tree/main");
    std::string code3 = shortener.shorten("https://music.yandex.ru/artist/1582874");

    std::cout << "Код 1: " << code1 << '\n';
    std::cout << "Код 2: " << code2 << '\n';
    std::cout << "Код 3: " << code3 << '\n';

    std::cout << "\n2. Повторное добавление той же ссылки\n";

    std::string repeatedCode = shortener.shorten("https://music.yandex.ru/artist/1582874");
    if (repeatedCode == code3)
    {
        std::cout << "Повторная ссылка вернула старый код: " << repeatedCode << '\n';
    }
    else
    {
        std::cout << "Ошибка: был создан новый код\n";
    }

    std::cout << "\n3. Получение исходной ссылки по короткому коду\n";

    std::cout << code1 << " -> " << shortener.getOrig(code1) << '\n';

    std::cout << "\n4. Проверка существования короткого кода\n";

    if (shortener.contains(code2))
    {
        std::cout << "Код " << code2 << " существует\n";
    }

    if (!shortener.contains("Dom_Dom"))
    {
        std::cout << "Код Dom_Dom не найден";
    }

    std::cout << "\n5. Подсчёт переходов\n";

    shortener.getOrig(code1);
    shortener.getOrig(code1);
    shortener.getOrig(code2);

    shortener.print();

    std::cout << "\n6. Самая популярная ссылка\n";

    shortener.printMostPopular();

    std::cout << "\n7. Поиск ссылок, содержащих слово 'github'\n";

    std::vector<std::pair<std::string, std::string>> found = shortener.find_by_word("github");

    if (found.empty())
    {
        std::cout << "Ничего не найдено\n";
    }
    else
    {
        for (const std::pair<std::string, std::string> &item : found)
        {
            std::cout << item.first << " -> " << item.second << '\n';
        }
    }

    std::cout << "\n8. Обратный поиск: код по длинной ссылке\n";

    std::cout << "https://github.com/DomDomych/Stkn_Alg_Third_Lab/tree/main -> "
              << shortener.getcodebyUrl("https://github.com/DomDomych/Stkn_Alg_Third_Lab/tree/main")
              << '\n';

    std::cout << "\n9. Изменение длинной ссылки для существующего кода\n";

    if (shortener.changeUrl(code3, "https://music.yandex.ru/album/3313112/track/55922728"))
    {
        std::cout << "Ссылка изменена\n";
    }
    else
    {
        std::cout << "Не удалось изменить ссылку\n";
    }

    std::cout << code3 << " -> " << shortener.getOrig(code3) << '\n';

    std::cout << "\n10. Удаление ссылки по короткому коду\n";

    if (shortener.remove(code2))
    {
        std::cout << "Ссылка удалена\n";
    }
    else
    {
        std::cout << "Код не найден\n";
    }

    if (!shortener.contains(code2))
    {
        std::cout << "Код " << code2 << " больше не существует\n";
    }

    std::cout << "\n11. Финальный вывод всех ссылок\n";

    shortener.print();

    return 0;
}