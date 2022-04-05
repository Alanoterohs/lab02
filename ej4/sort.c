#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "array_helpers.h"
#include "sort_helpers.h"
#include "sort.h"

static unsigned int min_pos_from(int a[], unsigned int i, unsigned int length) {
    unsigned int min_pos = i;
    for (unsigned int j = i + 1; j < length; ++j) {
        if (!goes_before(a[min_pos],a[j])) {
            min_pos = j;
        }
    }
    return (min_pos);
}

void selection_sort(int a[], unsigned int length) {
    for (unsigned int i = 0u; i < length; ++i) {
        unsigned int min_pos = min_pos_from(a, i, length);
        swap(a, i, min_pos);
    }
}


static void insert(int a[], unsigned int i) {
    assert(i > 0);
    while (i > 0 && goes_before(a[i],a[i-1])) {
      swap(a,i,i-1);
      i--;
    }
}

void insertion_sort(int a[], unsigned int length) {
    for (unsigned int i = 1u; i < length; ++i) {
        insert(a, i);
    }
}


static unsigned int partition(int a[], unsigned int izq, unsigned int der) {
    unsigned int i,j, pivote;
    pivote = izq;
    i = izq + 1;
    j = der;

    while (i <= j) {
      if (goes_before(a[i],a[pivote])) {
        i++;
      } else if (goes_before(a[pivote],a[j])) {
        j--;
      } else if (goes_before(a[pivote],a[i]) && goes_before(a[j],a[pivote])) {
        swap(a,i,j);
        i++;
        j--;
      }
    }
    swap(a, pivote, j);
    pivote = j;

    return pivote;
}

static void quick_sort_rec(int a[], unsigned int izq, unsigned int der) {

  unsigned int pivote;
  if (der > izq) {
    pivote = partition(a,izq,der);
    if (pivote >= 1) {
      quick_sort_rec(a, izq, pivote-1);
      quick_sort_rec(a, pivote+1, der);
    } else {
      quick_sort_rec(a, izq, pivote);
      quick_sort_rec(a, pivote+1, der);
    }
  }
}

void quick_sort(int a[], unsigned int length) {
    quick_sort_rec(a, 0u, (length == 0u) ? 0u : length - 1u);
}
