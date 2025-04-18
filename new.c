#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int compare_int(const void* a, const void* b) // void* - can ssilatsya na luboy tip dannyx, const - garantiya chto fun ne izmenit dannye 5 - 3 = 2 => 5 > 3 chanhe 35
{
    return (*(int*)a - *(int*)b);
}
// Функция для сравнения двух строк (без учета порядка элементов)
bool compare_rows(int* row1, int size1, int* row2, int size2) // arrays in c ne peredutsya po znacheniy
{
    // proverka razmeroz, row - ukazateli na stroki (odnimernie massivi)
    if(size1 != size2) return false; //raznie razmeri strok
    if(size1 == 0) return true; // Null rows with 0 size esli oba razm = 0
    if(row1 == NULL || row2 == NULL) return false;
    // Создаем временные массивы для сортировки
    int* copyarr1 = (int*)malloc(size1 * sizeof(int));
    int* copyarr2 = (int*)malloc(size2 * sizeof(int));
    
    if(copyarr1 == NULL || copyarr2 == NULL)
    {
        if(copyarr1) free(copyarr1);
        if(copyarr2) free(copyarr2);
        return false;
    }

    for (int i = 0; i < size1; i++) {
        copyarr1[i] = row1[i];
        copyarr2[i] = row2[i];
    }
    
    // sort
    qsort(copyarr1, size1, sizeof(int), compare_int); // ukaza na arr, kol element in arr, size of 1 elem (in bytes), funct for compare elems
    qsort(copyarr2, size2, sizeof(int), compare_int);
    bool res = true;
    // Сравнение отсортированных массивов, mozno bez flaga, no togda pridetsya osvobozdat memory do return false i eto esloznit cod (4 free return false)
    for (int i = 0; i < size1; i++) {
        if (copyarr1[i] != copyarr2[i]) {
            res = false;
            break;
        }
    }
    
    free(copyarr1);
    free(copyarr2);
    return res;
}

// Функция проверки совпадения массивов
bool arrays_match(int** A1, int* sizes1, int rows1, int** A2, int* sizes2, int rows2) // if y arr has stroki, proverim ykazateli na massii i ix razmeri
{
    if((rows1 > 0) && (A1 == NULL || A2 == NULL || sizes1 == NULL || sizes2 == NULL)) return false; // nalichie strok podrazymevaet chto massivi dolzni soderzat dannie
    if(rows1 != rows2) return false; // one is empty, other is not, kol strok raznoe - massivi ne sovpadaet
    if(rows1 == 0) return true; // both are empty

    for(int i = 0; i < rows1; i++) // if razmer kakoyto stroki otrizatelnyu 
    {
        if(sizes1[i] < 0 || sizes2[i] < 0) return false;
    }
    // Создаем массив флагов для отслеживания использованных строк
    bool* used = (bool*)calloc(rows2, sizeof(bool)); //massiv used chtobi otslezivat kakie stroki a2 yze bili sopostavleni so strokami a1, malloc - videlyaet memory bez inizializaii, calloc - videluaet i inizial memory nulyami (false), ydobno chtobi all elebs will false
    if(used == NULL) // proverka videleniya pamyati
    {
        return false;
    }

    for (int i = 0; i < rows1; i++) // perebor strok pervogo massiva a1, aim - for every stroki A1[i] nayti rovno odny neispolzovannuy stroky A2[j], kotoray sovpadet po soderzaniy
    {
        bool found = false;
        if(sizes1[i] > 0 && A1[i] == NULL) // if razmer stroki > 0, no ykazatel na nee NULL - oshibka
        {
            free(used);
            return false;
        }

        for (int j = 0; j < rows2; j++) {
            if(sizes2[j] > 0 && A2[j] == NULL)
            {
                free(used);
                return false;
            }
            
            if (used[j] == 0 && compare_rows(A1[i], sizes1[i], A2[j], sizes2[j]))  // used[j] = NULL - stroka A2[j] eshe ne ispolzovana i stroki sovpadaet 
            {
                used[j] = true; // note A2[j] kak ispolzovannyu
                found = true;
                break;
            }
        }

        if (!found) // if for A1[i] ne nashli nichego podhodyashego in A2[j]
        {
            free(used);
            return false;
        }
    }
    
    free(used);
    return true;
}

bool arrays_match_bidirectional(int** A1, int* sizes1, int rows1, int** A2, int* sizes2, int rows2) {
    // Проверка в обе стороны
    return arrays_match(A1, sizes1, rows1, A2, sizes2, rows2) && 
           arrays_match(A2, sizes2, rows2, A1, sizes1, rows1);
}
