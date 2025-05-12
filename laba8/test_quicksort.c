#include <check.h>
#include "quicksort.h"

// возрастающий массив
START_TEST(test_sort_inc) {
    int n = 10;
    int A[10];
    FillInc(n, A);
    QuickSort(A, 0, n - 1);

    for (int i = 0; i < n; i++) {
        ck_assert_int_eq(A[i], i + 1);
    }
}
END_TEST

// убывающий массив
START_TEST(test_sort_dec) {
    int n = 10;
    int A[10];
    FillDec(n, A);
    QuickSort(A, 0, n - 1);

    for (int i = 0; i < n; i++) {
        ck_assert_int_eq(A[i], i + 1);
    }
}
END_TEST

// random массив
START_TEST(test_sort_rand) {
    int n = 10;
    int A[10];
    FillRand(n, A);
    QuickSort(A, 0, n - 1);

    for (int i = 1; i < n; i++) {
        ck_assert_int_le(A[i - 1], A[i]);
    }
}
END_TEST

// пустой массив
START_TEST(test_sort_empty) {
    int n = 0;
    int A[1];
    QuickSort(A, 0, n - 1);
}
END_TEST

// 1 элемент
START_TEST(test_sort_single) {
    int n = 1;
    int A[1] = {42};
    QuickSort(A, 0, n - 1);
    ck_assert_int_eq(A[0], 42); // проверка на неизменяемость
}
END_TEST

// одинаковые элементы
START_TEST(test_sort_duplicates) {
    int n = 5;
    int A[5] = {7, 7, 7, 7, 7};
    QuickSort(A, 0, n - 1);

    for (int i = 0; i < n; i++) {
        ck_assert_int_eq(A[i], 7); // проверка на равность элементов
    }
}
END_TEST

// big массив
START_TEST(test_sort_large) {
    int n = 1000;
    int A[1000];
    FillRand(n, A);
    QuickSort(A, 0, n - 1);

    for (int i = 1; i < n; i++) {
        ck_assert_int_le(A[i - 1], A[i]); // проверка на отсортированность
    }
}
END_TEST

Suite* quicksort_suite(void) {
    Suite* s = suite_create("QuickSort");

    TCase* tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_sort_inc);
    tcase_add_test(tc_core, test_sort_dec);
    tcase_add_test(tc_core, test_sort_rand);
    tcase_add_test(tc_core, test_sort_empty);
    tcase_add_test(tc_core, test_sort_single);
    tcase_add_test(tc_core, test_sort_duplicates);
    tcase_add_test(tc_core, test_sort_large);

    suite_add_tcase(s, tc_core);
    return s;
}

int main(void) {
    int number_failed;
    Suite* s = quicksort_suite();
    SRunner* sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? 0 : 1;
}

