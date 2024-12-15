#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <chrono>

using namespace std;

using Clock = std::chrono::high_resolution_clock;
using TimePoint = std::chrono::time_point<Clock>;
TimePoint start_time, end_time;

const int REPEAT_COUNT = 1000000; // Кол-во повторений для тестирования производительности.
/**
 * @brief Начинает отсчёт времени.
 */
void start_timer(){
    start_time = Clock::now();
}
/**
 * @brief  Завершает отсчёт времени и выводит длительность операции.
 * @param operation - название операции.
 * @param repetitions - кол-во повторений для усреднённого времени.
 */
void end_timer(const string &operation, int repetitions){
    end_time = Clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count();
    cout << operation << " took " << duration / repetitions << " nanoseconds per iteration." << endl;
}

/**
 * @brief Проверка элемента на оригинальность.
 * @param num - Кол-во элементов.
 * @param arr - массив уже добавленных элементов.
 * @param el - Элемент, который проверяется на оригинальность.
 */
bool find_in_arr(int num, char *arr, char el)
{ // array
    for (int i = 0; i < num; i++)
    {
        if (arr[i] == el)
        {
            return false;
        }
    }
    return true;
}

/**
 * @brief Вывод массива.
 * @param arr - Сам массив.
 * @param num - Кол-во элементов.
 */
void print_arr(char *arr, int num)
{
    cout << "Finish array: ";
    for (int i = 0; i < num; i++)
    {
        if (isalpha(arr[i]))
        {
            cout << arr[i];
        }
    }
}

/**
 * @brief Создание массива.
 * @param arr - Где будет хранится массив.
 * @param num - Кол-во элементов массива.
 */
char *create_array(char *arr, int num)
{
    char el;
    int flag;
    arr = (char *)malloc(num * sizeof(char));
    do
    {
        cout << "Do you want random generation or hand work?(1/0): ";
        cin >> flag;
        if (flag != 0 && flag != 1)
        {
            cout << "Try again" << endl;
        }
    } while (flag != 0 && flag != 1);
    for (int i = 0; i < num; i++)
    {
        if (flag == 0)
        {
            cout << "Enter " << i << " element: ";
            cin >> el;
        }
        else if (flag == 1)
        {
            el = rand() % ('z' - 'a' + 1) + 'a';
            cout << el << endl;
        }
        if (find_in_arr(i, arr, el) && isalpha(el) && isupper(el) == 0)
        {
            arr[i] = el;
        }
        else
        {
            if (!find_in_arr(i, arr, el))
            {
                cout << "This element already stay in set. Please try again" << endl;
            }
            else
            {
                cout << "Please, enter the small latin symbol, try agai." << endl;
            }
            i--;
        }
    }
    return arr;
}

/**
 * @brief Поиск одинаковых элементов во всех 4-х массивов.
 * @param a - Первый массив.
 * @param b - Второй массив.
 * @param c - Третий массив.
 * @param d - Четвёртый массив.
 * @param num - Кол-во элементов в массиве.
 */
char *check_array(char *a, char *b, char *c, char *d, int num)
{
    char *e;
    char e1[num], e2[num];
    int flag = 0;
    e = (char *)malloc(num * sizeof(char));
    for (int i = 0; i < num; i++)
    {
        for (int j = 0; j < num; j++)
        {
            if (a[i] == b[j])
            {
                e1[flag] = a[i];
                flag++;
            }
        }
    }
    flag = 0;
    for (int i = 0; i < num; i++)
    {
        for (int j = 0; j < num; j++)
        {
            if (c[i] == d[j])
            {
                e2[flag] = c[i];
                flag++;
            }
        }
    }
    flag = 0;
    for (int i = 0; i < num; i++)
    {
        for (int j = 0; j < num; j++)
        {
            if (e1[i] == e2[j])
            {
                e[flag] = e1[i];
                flag++;
            }
        }
    }
    return e;
} // array finish

/**
 * @brief Структура элемента списка.
 */
struct Set // list
{
    char el;
    Set *next;
    Set(char e, Set *n = nullptr) : el(e), next(n) {}
    ~Set() { delete next; }
};

/**
 * @brief Создание списка из массива.
 * @param arr - Массив, из которого будет делаться список.
 * @param num - Кол-во элементов массива.
 */
Set *create_list_from_array(char *arr, int num)
{
    Set *head = nullptr;
    Set *tail = nullptr;
    for (int i = 0; i < num; i++)
    {
        Set *newnode = new Set(arr[i]);
        if (head == nullptr)
        {
            head = newnode;
            head->next = tail;
        }
        else
        {
            tail->next = newnode;
        }
        tail = newnode;
    }
    return head;
}

/**
 * @brief Поиск одинаковых элементов двух списков.
 * @param head1 - Первый список.
 * @param head2 - Второй список.
 */
Set *check_sets(Set *head1, Set *head2)
{
    Set *current1 = head1;
    Set *current2 = head2;
    Set *set_head = nullptr;
    Set *set_tail = nullptr;

    while (current1 != nullptr)
    {
        current2 = head2;
        while (current2 != nullptr)
        {
            if (current1->el == current2->el)
            {
                Set *newNode = new Set(current1->el);
                if (set_head == nullptr)
                {
                    set_head = newNode;
                    set_head->next = set_tail;
                }
                else
                {
                    set_tail->next = newNode;
                }
                set_tail = newNode;
            }
            current2 = current2->next;
        }
        current1 = current1->next;
    }
    return set_head;
}

/**
 * @brief Вывод списка
 * @param set - Список.
 */
void print_set(Set *set)
{
    Set *current = set;
    if (set == nullptr)
    {
        cout << "Error, set is empty" << endl;
    }
    else
    {
        while (current != nullptr)
        {
            cout << current->el << " ";
            current = current->next;
        }
    }
    cout << endl;
} // finish list

/**
 * @brief Поиск одинаковых элементов в битовом массиве и подсчёт времени выполнения.
 * @param a - первый массив.
 * @param b - второй массив.
 * @param c - третий массив.
 * @param d - четвёртый массив.
 * @param arr - итоговый массив.
 */
void process_bits(bool* a, bool* b, bool* c, bool* d, bool* arr){
    start_timer();
    for (int j = 0; j < REPEAT_COUNT; j++){
    for (int i = 0; i < 26; i++)
    {
        if (a[i] == 1 && b[i] == 1 && c[i] == 1 && d[i] == 1)
        {
            arr[i] = 1;
        }
        else
        {
            arr[i] = 0;
        }
    }
    }
    end_timer("Bits array", REPEAT_COUNT);
}

 /**
  * @brief Создаём битовый массив, который содержит 0 или 1, и сразу находим общие элементы.
  * @param arr - Массив из 0 и 1.
  * @param A - Первый обычный массив.
  * @param B - Второй обычный массив.
  * @param C - Третий обычный массив.
  * @param D - Четвёртый обычный массив.
  * @param num - Кол-во элементов в массиве.
  */
void find_bool(bool *arr, char *A, char *B, char *C, char *D, int num)
{
    bool *a, *b, *c, *d;
    a = (bool *)malloc(26 * sizeof(bool));
    b = (bool *)malloc(26 * sizeof(bool));
    c = (bool *)malloc(26 * sizeof(bool));
    d = (bool *)malloc(26 * sizeof(bool));
    for (int i = 1; i <= 26; i++)
    {
        for (int j = 0; j < num; j++)
        {
            if (A[j] == i + 96)
            {
                a[i - 1] = 1;
            }
            else if(a[i-1] != 1)
            {
                a[i - 1] = 0;
            }
        }
    }
    for (int i = 1; i <= 26; i++)
    {
        for (int j = 0; j < num; j++)
        {
            if (B[j] == i + 96)
            {
                b[i - 1] = 1;
            }
            else if (b[i-1] != 1)
            {
                b[i - 1] = 0;
            }
        }
    }
    for (int i = 1; i <= 26; i++)
    {
        for (int j = 0; j < num; j++)
        {
            if (C[j] == i + 96)
            {
                c[i - 1] = 1;
            }
            else if (c[i-1] != 1)
            {
                c[i - 1] = 0;
            }
        }
    }
    for (int i = 1; i <= 26; i++)
    {
        for (int j = 0; j < num; j++)
        {
            if (D[j] == i + 96)
            {
                d[i - 1] = 1;
            }
            else if (d[i-1] != 1)
            {
                d[i - 1] = 0;
            }
        }
    }
    process_bits(a, b, c, d, arr);
}



/**
 * @brief Вывод элементов побитового массива индекс + 71(код буквы 'a').
 * @param array - массив, который будем выводить.
 */
void print_bits(bool *array)
{
    char a;
    cout << "Finish array of bits: ";
    for (int i = 1; i <= 26; i++)
    {
        if (array[i-1])
        {
            a = i + 96;
            cout << a << " ";
        }
    }
}

/**
 * @brief Заполнение массива bool с помощью побитового сравнения.
 * @param arr - Массив, над которым проводят операции.
 * @param size - Размер массива.
 */
bool *fill_machine_word(char arr[], int size)
{
    bool *alphas;
    bool flag;
    alphas = (bool *)calloc(26, sizeof(bool));
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < sizeof(char) * 8; j++)
        {
            int result = int(int(arr[i] - 96) & (1 << j));
            if (result)
            {
                flag = false;
            }
            else
            {
                flag = true;
            }
            if (flag)
            {
                alphas[arr[i] - 97] = 1;
            }
            else
            {
                alphas[arr[i] - 97] = 0;
            }
        }
    }

    return alphas;
}

/**
 * @brief Поиск одинаковых элементов в 4-х массивах.
 * @param a - Первый массив.
 * @param b - Второй массив.
 * @param c - Третий массив.
 * @param d - Четвертый массив.
 * @param arr - Итоговый массив bool.
 */
void processWord(bool a[], bool b[], bool c[], bool d[], bool *arr)
{
    for (int i = 0; i < 26; i++)
    {
        if (a[i] == b[i] && a[i] == c[i] && a[i] == d[i] && a[i] == 1)
        {
            arr[i] = 1;
        }
        else
        {
            arr[i] = 0;
        }
    }
}

/**
 * @brief Вывод массива с машинным словом.
 * @param name - Название массива.
 * @param word - Массив, который будем выводить.
 */
void print_word(char name, bool word[])
{
    cout << "Words " << name << ": ";
    for (int i = 0; i < 26; i++)
    {
        if (word[i])
        {
            char a = i + 97;
            cout << a << " ";
        }
    }
    cout << endl;
}

int main()
{
    int num;
    bool *words;
    char *A, *B, *C, *D, *E;
    Set *As, *Bs, *Cs, *Ds, *Es, *E1, *E2;
    cout << "How much elements will be in the sets: ";
    cin >> num;

    cout << "------------\nARRAY" << endl; // ARRAYS
    cout << "Let's fill first set!" << endl;
    A = create_array(A, num);
    cout << "Let's fill second set!" << endl;
    B = create_array(B, num);
    cout << "Let's fill third set!" << endl;
    C = create_array(B, num);
    cout << "Let's fill forth set!" << endl;
    D = create_array(D, num);

    cout << "\n----------------------\nARRAY" << endl;

    start_timer();
    for (int i = 0; i < REPEAT_COUNT; i++)
        E = check_array(A, B, C, D, num);

    end_timer("Array", REPEAT_COUNT);

    E = check_array(A, B, C, D, num);
    print_arr(E, num);
    cout << endl;

    cout << "\n----------------------\nLIST" << endl; // LISTS
    cout << "Let's start to make a list!" << endl;

    cout << "First list: ";
    As = create_list_from_array(A, num);
    print_set(As);
    Bs = create_list_from_array(B, num);
    cout << "Second list: ";
    print_set(Bs);
    Cs = create_list_from_array(C, num);
    cout << "Third list: ";
    print_set(Cs);
    Ds = create_list_from_array(D, num);
    cout << "Forth list: ";
    print_set(Ds);

    start_timer();
    for (int i = 0; i < REPEAT_COUNT; i++)
    {
        E1 = check_sets(As, Bs);
        E2 = check_sets(Cs, Ds);
        Es = check_sets(E1, E2);
    }
    end_timer("Lists", REPEAT_COUNT);

    E1 = check_sets(As, Bs);
    E2 = check_sets(Cs, Ds);
    Es = check_sets(E1, E2);

    cout << "Finish list: ";
    print_set(Es);
    cout << endl;

    cout << "\n----------------------\nBITS ARRAY" << endl;
    words = (bool *)malloc(26 * sizeof(bool)); // BITS ARRAY

    find_bool(words, A, B, C, D, num);

    print_bits(words);

    cout << "\n----------------------\nMACHINE WORD" << endl;
    bool *Aw, *Bw, *Cw, *Dw, *Ew;
    Aw = (bool *)malloc(26 * sizeof(bool));
    Bw = (bool *)malloc(26 * sizeof(bool));
    Cw = (bool *)malloc(26 * sizeof(bool));
    Dw = (bool *)malloc(26 * sizeof(bool));
    Ew = (bool *)malloc(26 * sizeof(bool));

    Aw = fill_machine_word(A, num);
    print_word('A', Aw);
    Cw = fill_machine_word(C, num);
    print_word('C', Cw);
    Dw = fill_machine_word(D, num);
    print_word('D', Dw);
    Bw = fill_machine_word(B, num);
    print_word('B', Bw);

    start_timer();
    for (int i = 0; i < REPEAT_COUNT; i++)
        processWord(Aw, Cw, Dw, Bw, Ew);
    end_timer("Machine word", REPEAT_COUNT);


    cout << "Finish ";
    print_word('E', Ew);
    return 0;
}
