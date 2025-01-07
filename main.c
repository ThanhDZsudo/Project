#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"
#include "datatype.h"
#include "function.c"

int main(void) {
	initCategories();
	loadCategoriesFile();
    int choice;
    do {
        printf("========= MENU ==========\n");
        printf("[1] Quan ly danh muc\n");
        printf("[2] Quan ly san pham\n");
        printf("[3] Quan ly hoa don\n");
        printf("[4] Thoat\n");
        printf("=========================\n");
        printf("Nhap lua chon: ");
        scanf("%d", &choice);
        getchar();
        switch (choice) {
            case 1:
                categoryManagement();
                break;
            case 2:
                productManagement();
                break;
            case 3:
            	invoiceManagement();
                break;
            case 4:
            	saveCategoriesFile();
            	freeCategories();
                printf("Thoat chuong trinh\n");
                break;
            default:
                printf("Lua chon khong hop le\n");
        }
        printf("\n");
    } while (choice != 4);
    return 0;
}
