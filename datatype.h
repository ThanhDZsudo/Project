#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char id[50];
    char name[50];
} Category;

Category *categories;
int categoryCount = 0;
int maxCategory = 100;

typedef struct {
    char id[50];
    char name[50];
    float price;
    char categoryId[50];
} Product;

Product *products;
int productCount = 0;
int maxProduct = 100;
