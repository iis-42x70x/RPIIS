
#include "C:\Users\omen\source\repos\SufMs\SufMs\SufMs.h"

void suffMs::inputString(suffMs* st)
{
    while (true)
    {
        std::cin.getline(st->string, 64);
        if (st->string[0] == '\0')
            std::cout << "Введите строку! \n";
        else
            break;
    }
    for (int i = 0; st->string[i] != '\0'; i++)
        st->size++;
    st->k = log2(size);
    st->c = new int*[k + 3];
}


void suffMs::printArr() {
    for (int i = 0; i < size; i++) {
        std::cout << suffarr[i] << " ";
    }
    std::cout << std::endl;
}

// Построение суффиксного массива
void suffMs::buildSuffArr(suffMs* suf) {
    int cnt[alphabet];
    int classes = 0;
    for (int i = 0; i < k + 3; i++)
        suf->c[i] = new int[maxlen];
    // Начальная сортировка по первому символу
    memset(cnt, 0, alphabet * sizeof(int));
    for (int i = 0; i < size; ++i) {
        ++cnt[suf->string[i]];
    }
    for (int i = 1; i < alphabet; ++i) {
        cnt[i] += cnt[i - 1];
    }
    for (int i = 0; i < size; ++i) {
        suf->suffarr[--cnt[suf->string[i]]] = i;
    }

    // Инициализация первого уровня классов эквивалентности
    suf->c[0][suf->suffarr[0]] = 0;
    classes = 1;
    for (int i = 1; i < size; ++i) {
        if (suf->string[suf->suffarr[i]] != suf->string[suf->suffarr[i - 1]]) {
            ++classes;
        }
        suf->c[0][suf->suffarr[i]] = classes - 1;
    }

    int pn[maxlen], cn[maxlen];
    for (int h = 0; (1 << h) < size; ++h) {
        for (int i = 0; i < size; ++i) {
            pn[i] = suf->suffarr[i] - (1 << h);
            if (pn[i] < 0) {
                pn[i] += size;
            }
        }

        // Сортировка пар (c[h][i], c[h][i + 2^h])
        memset(cnt, 0, classes * sizeof(int));
        for (int i = 0; i < size; ++i) {
            ++cnt[suf->c[h][pn[i]]];
        }
        for (int i = 1; i < classes; ++i) {
            cnt[i] += cnt[i - 1];
        }
        for (int i = size - 1; i >= 0; --i) {
            suf->suffarr[--cnt[suf->c[h][pn[i]]]] = pn[i];
        }

        // Вычисление новых классов эквивалентности
        cn[suf->suffarr[0]] = 0;
        classes = 1;
        for (int i = 1; i < size; ++i) {
            int mid1 = (suf->suffarr[i] + (1 << h)) % size, mid2 = (suf->suffarr[i - 1] + (1 << h)) % size;
            if (suf->c[h][suf->suffarr[i]] != suf->c[h][suf->suffarr[i - 1]] || suf->c[h][mid1] != suf->c[h][mid2]) {
                ++classes;
            }
            if (suf->c[h][suf->suffarr[i]] != suf->c[h][suf->suffarr[i - 1]] || suf->c[h][mid1] != suf->c[h][mid2]) {
                ++classes;
            }
            cn[suf->suffarr[i]] = classes - 1;
        }

        // Сохраняем новый уровень классов эквивалентности
        memcpy(suf->c[h + 1], cn, size * sizeof(int));
    }

    // Вывод суффиксного массива
    printArr();
}




void suffMs::largestCommonPref(int i, int j)
{
    int ans = 0;
    int input = j;
    for (int h = log2(size); h >= 0; --h) {
        if (c[h][i] == c[h][j]) {
            ans += 1 << h;
            i += 1 << h;
            j += 1 << h;
        }
    }
    for (int i = 0; i < ans; i++)
        std::cout << string[input + i];
}

int suffMs::minCycle()
{
    return suffarr[0];
}
