#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//cap phat bo nho
void initCategories() {
    categories = (Category *)malloc(maxCategory * sizeof(Category));
    if (categories == NULL) {
        printf("Khong the cap phat bo nho!\n");
        exit(1);
    }
}
//mo file
void saveCategoriesFile() {
    FILE *file = fopen("danhMuc.bin", "wb");
    if (file == NULL) return;
    fwrite(&categoryCount, sizeof(int), 1, file);
    fwrite(categories, sizeof(Category), categoryCount, file);
    fclose(file);
}
//hoa don
void invoiceManagement() {
	printf("");
}
//danh muc
void categoryManagement() {
    int choice;
    do {
        printf("====== QUAN LY DANH MUC =======\n");
        printf("[1] Hien thi danh sach danh muc\n");
        printf("[2] Them danh muc moi\n");
        printf("[3] Sua danh muc\n");
        printf("[4] Xoa danh muc\n");
        printf("[5] Sap xep danh muc theo ten\n");
        printf("[6] Tim kiem danh muc theo ten\n");
        printf("[7] Thoat\n");
        printf("==============================\n");
        printf("Nhap lua chon: ");
        scanf("%d", &choice);
        getchar();
        switch (choice) {
            case 1:
                showCategory();
                break;
            case 2:
                addCategory();
                break;
            case 3:
                editCategory();
                break;
            case 4:
                deleteCategory();
                break;
            case 5:
                sortCategories();
                break;
            case 6:
            	searchCategory();
            	break;
            case 7:
                break;
            default:
                printf("Lua chon khong hop le\n");
        }
        printf("\n");
    } while (choice != 7);
}
//san pham
void productManagement() {
    int choice;
    do {
        printf("====== QUAN LY SAN PHAM =======\n");
        printf("[1] Hien thi danh sach san pham\n");
        printf("[2] Them san pham\n");
        printf("[3] Sua thong tin san pham\n");
        printf("[4] Xoa san pham\n");
        printf("[5] Tim kiem san pham theo ten\n");
        printf("[6] Sap xep san pham theo gia\n");
        printf("[7] Loc san pham theo khoang gia hoac danh muc\n");
        printf("[8] Thoat\n");
        printf("===============================\n");
        printf("Nhap lua chon: ");
        scanf("%d", &choice);
        getchar();
        switch (choice) {
            case 1:
                showProducts();
                break;
            case 2:
                addProduct();
                break;
            case 3:
                editProduct();
                break;
            case 4:
                deleteProduct();
                break;
            case 5:
                searchProduct();
                break;
            case 6:
                sortProducts();
                break;
            case 7:
                filterProducts();
                break;
            case 8:
                break;
            default:
                printf("Lua chon khong hop le\n");
        }
        printf("\n");
    } while (choice != 8);
}
//hien danh muc
void showCategory() {
    if (categoryCount == 0) {
        printf("Danh sach trong\n");
    } else {
        printf("+-----------------+-------------------------------+\n");
        printf("| ID              | Ten danh muc                  |\n");
        printf("+-----------------+-------------------------------+\n");
        for (int i = 0; i < categoryCount; i++) {
            printf("| %-15s | %-29s |\n", categories[i].id, categories[i].name);
        }
        printf("+-----------------+-------------------------------+\n");
    }
}
//them danh muc
void addCategory() {
    if (categoryCount >= maxCategory) {
        printf("Danh sach da day!\n");
        return;
    }
    char tempId[50];
    char tempName[50];
    while (1) {
        printf("Nhap id danh muc moi: ");
        fgets(tempId, sizeof(tempId), stdin);
        tempId[strcspn(tempId, "\n")] = '\0';
        if (strlen(tempId) < 1) {
            printf("id khong duoc de trong\n");
            continue;
        }
        if (strlen(tempId) > 5) {
            printf("id khong duoc dai hon 5 ky tu\n");
            continue;
        }
        if (isDuplicateId(tempId)) {
            printf("id da ton tai\n");
            continue;
        }
        break;
    }
    while (1) {
        printf("Nhap ten danh muc moi: ");
        fgets(tempName, sizeof(tempName), stdin);
        tempName[strcspn(tempName, "\n")] = '\0';

        if (strlen(tempName) < 1) {
            printf("Ten danh muc khong duoc de trong\n");
            continue;
        }
        if (strlen(tempName) > 20) {
            printf("Ten danh muc khong duoc dai hon 20 ky tu\n");
            continue;
        }
        break;
    }
    strcpy(categories[categoryCount].id, tempId);
    strcpy(categories[categoryCount].name, tempName);
    categoryCount++;
    printf("Da them danh muc: %s - %s\n", tempId, tempName);
}
//sua danh muc
void editCategory() {
    char id[50];
    printf("Nhap ID danh muc can sua: ");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = '\0';
    int found = 0;
    for (int i = 0; i < categoryCount; i++) {
        if (strcmp(categories[i].id, id) == 0) {
            found = 1;
            printf("Nhap ten moi cho danh muc: ");
            fgets(categories[i].name, sizeof(categories[i].name), stdin);
            categories[i].name[strcspn(categories[i].name, "\n")] = '\0';
            printf("Da sua danh muc\n");
            break;
        }
    }
    if (!found) {
        printf("ID danh muc khong ton tai\n");
    }
}
//xoa danh muc
void deleteCategory() {
    char id[50];
    printf("Nhap ID danh muc can xoa: ");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = '\0';
    int found = 0;
    for (int i = 0; i < categoryCount; i++) {
        if (strcmp(categories[i].id, id) == 0) {
            found = 1;
            printf("Ban co chac chan muon xoa danh muc sau?\n");
            printf("ID:  %-15s | Ten:  %-29s\n", categories[i].id, categories[i].name);
            printf("[1] xoa \t [0] huy \n");
            int confirmation;
            printf("Nhap lua chon cua ban: ");
            scanf("%d", &confirmation);
            getchar();
            if (confirmation == 1) {
                for (int j = i; j < categoryCount - 1; j++) {
                    categories[j] = categories[j + 1];
                }
                categoryCount--;
                printf("Da xoa danh muc\n");
            } else {
                printf("Da huy \n");
            }
            break;
        }
    }
    if (!found) {
        printf("id danh muc khong ton tai\n");
    }
}
//sap xep danh muc
void sortCategories() {
    int choice;
    printf("\n========= SAP XEP DANH MUC =========\n");
    printf("Chon cach sap xep:\n");
    printf("[1] Tu A-Z \t [2] Tu Z-A \n");
    printf("Nhap lua chon: ");
    scanf("%d", &choice);
    getchar();
    if (choice == 1) {
        for (int i = 0; i < categoryCount - 1; i++) {
            for (int j = i + 1; j < categoryCount; j++) {
                if (strcmp(categories[i].name, categories[j].name) > 0) {
                    Category temp = categories[i];
                    categories[i] = categories[j];
                    categories[j] = temp;
                }
            }
        }
        printf("Danh muc da duoc sap xep theo A-Z\n");
    } else if (choice == 2) {
        for (int i = 0; i < categoryCount - 1; i++) {
            for (int j = i + 1; j < categoryCount; j++) {
                if (strcmp(categories[i].name, categories[j].name) < 0) {
                    Category temp = categories[i];
                    categories[i] = categories[j];
                    categories[j] = temp;
                }
            }
        }
        printf("Danh muc da duoc sap xep theo Z-A\n");
    } else {
        printf("Lua chon khong hop le\n");
        return;
    }
    showCategory();
}
//tim danh muc
void searchCategory() {
    char searchName[50];
    printf("Nhap ten danh muc can tim: ");
    fgets(searchName, sizeof(searchName), stdin);
    searchName[strcspn(searchName, "\n")] = '\0';
    int found = 0;
    printf("+-----------------+-------------------------------+\n");
    printf("| ID              | Ten danh muc                  |\n");
    printf("+-----------------+-------------------------------+\n");
    for (int i = 0; i < categoryCount; i++) {
        if (strstr(categories[i].name, searchName) != NULL) {
            printf("| %-15s | %-29s |\n", categories[i].id, categories[i].name);
            found = 1;
        }
    }
    printf("+-----------------+-------------------------------+\n");
    if (!found) {
        printf("Khong tim thay danh muc\n");
    }
}
//check trung id danh muc
int isDuplicateId(const char *id) {
    for (int i = 0; i < categoryCount; i++) {
        if (strcmp(categories[i].id, id) == 0) {
            return 1;
        }
    }
    return 0;
}
//giai phong bo nho danh muc
void freeCategories() {
    free(categories);
}
//dong va luu file danh muc
void loadCategoriesFile() {
    FILE *file = fopen("danhMuc.bin", "rb");
    if (file == NULL) return;
    fread(&categoryCount, sizeof(int), 1, file);
    fread(categories, sizeof(Category), categoryCount, file);
    fclose(file);
}
// khoi tao bo nho san pham
void initProducts() {
    products = (Product *)malloc(maxProduct * sizeof(Product));
    if (products == NULL) {
        printf("Khong the cap phat bo nho!\n");
        exit(1);
    }
}
// mo file san pham
void loadProductsFile() {
    FILE *file = fopen("sanPham.bin", "rb");
    if (file == NULL) return;
    fread(&productCount, sizeof(int), 1, file);
    fread(products, sizeof(Product), productCount, file);
    fclose(file);
}
// hien san pham
void showProducts() {
    if (productCount == 0) {
        printf("Danh sach san pham trong\n");
    } else {
        printf("+-----------------+-------------------------------+----------+-----------------+\n");
        printf("|   ID            | Ten san pham                  | Gia      | ID Danh Muc     |\n");
        printf("+-----------------+-------------------------------+----------+-----------------+\n");
        for (int i = 0; i < productCount; i++) {
            printf("| %-15s | %-29s | %-8.2f | %-15s |\n", products[i].id, products[i].name, products[i].price, products[i].categoryId);
        }
        printf("+-----------------+-------------------------------+----------+-----------------+\n");
    }
}
// Them san pham
void addProduct() {
    if (productCount >= maxProduct) {
        printf("Danh sach san pham da day!\n");
        return;
    }
    char categoryId[50];
    printf("Nhap id danh muc: ");
    fgets(categoryId, sizeof(categoryId), stdin);
    categoryId[strcspn(categoryId, "\n")] = '\0';
    int categoryExists = 0;
    for (int i = 0; i < categoryCount; i++) {
        if (strcmp(categories[i].id, categoryId) == 0) {
            categoryExists = 1;
            break;
        }
    }
    if (!categoryExists) {
        printf("ID danh muc khong ton tai\n");
        return;
    }
    Product newProduct;
    strcpy(newProduct.categoryId, categoryId);
    printf("Nhap id san pham: ");
    fgets(newProduct.id, sizeof(newProduct.id), stdin);
    newProduct.id[strcspn(newProduct.id, "\n")] = '\0';
    printf("Nhap ten san pham: ");
    fgets(newProduct.name, sizeof(newProduct.name), stdin);
    newProduct.name[strcspn(newProduct.name, "\n")] = '\0';
    printf("Nhap gia san pham: ");
    char priceInput[50];
    fgets(priceInput, sizeof(priceInput), stdin);
    if (sscanf(priceInput, "%f", &newProduct.price) != 1) {
        printf("Nhap gia tri cho san pham\n");
        return;
    }
    products[productCount++] = newProduct;
    printf("Da them san pham \n");
    getchar();
}
// sua san pham
void editProduct() {
    char id[50];
    printf("Nhap ID san pham can sua: ");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = '\0';
    int found = 0;
    for (int i = 0; i < productCount; i++) {
        if (strcmp(products[i].id, id) == 0) {
            found = 1;
            printf("Nhap ten moi: ");
            fgets(products[i].name, sizeof(products[i].name), stdin);
            products[i].name[strcspn(products[i].name, "\n")] = '\0';
            printf("Nhap gia moi: ");
            scanf("%f", &products[i].price);
            getchar();
            printf("Nhap ID danh muc moi: ");
            fgets(products[i].categoryId, sizeof(products[i].categoryId), stdin);
            products[i].categoryId[strcspn(products[i].categoryId, "\n")] = '\0';
            printf("Da sua thong tin san pham \n");
            break;
        }
    }
    if (!found) {
        printf("Khong tim thay san pham \n");
    }
}
// xoa san pham
void deleteProduct() {
    char id[50];
    printf("Nhap ID san pham can xoa: ");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = '\0';
    int found = 0;
    for (int i = 0; i < productCount; i++) {
        if (strcmp(products[i].id, id) == 0) {
            found = 1;
            for (int j = i; j < productCount - 1; j++) {
                products[j] = products[j + 1];
            }
            productCount--;
            printf("Da xoa san pham \n");
            break;
        }
    }
    if (!found) {
        printf("Khong tim thay san pham \n");
    }
}
// tim san pham
void searchProduct() {
    char searchName[50];
    printf("Nhap ten san pham can tim: ");
    fgets(searchName, sizeof(searchName), stdin);
    searchName[strcspn(searchName, "\n")] = '\0';
    int found = 0;
    printf("+-----------------+-------------------------------+----------+-----------------+\n");
    printf("| ID              | Ten san pham                 | Gia      | ID Danh Muc     |\n");
    printf("+-----------------+-------------------------------+----------+-----------------+\n");
    for (int i = 0; i < productCount; i++) {
        if (strstr(products[i].name, searchName) != NULL) {
            printf("| %-15s | %-29s | %-8.2f | %-15s |\n", products[i].id, products[i].name, products[i].price, products[i].categoryId);
            found = 1;
        }
    }
    printf("+-----------------+-------------------------------+----------+-----------------+\n");
    if (!found) {
        printf("Khong tim thay san pham!\n");
    }
}
// sap xep san pham
void sortProducts() {
    int choice;
    printf("Chon thu tu sap xep: [1] tang, [2] giam \n");
    printf("Lua chon: ");
    scanf("%d", &choice);
    getchar();
    for (int i = 0; i < productCount - 1; i++) {
        for (int j = i + 1; j < productCount; j++) {
            if ((choice == 1 && products[i].price > products[j].price) ||
                (choice == 2 && products[i].price < products[j].price)) {
                Product temp = products[i];
                products[i] = products[j];
                products[j] = temp;
            }
        }
    }
    printf("Da sap xep san pham \n");
    showProducts();
}
// loc san pham
void filterProducts() {
    printf("chuc nang chua duoc phat trien");
}
// luu file va dong san pham
void saveProductsFile() {
    FILE *file = fopen("sanPham.bin", "wb");
    if (file == NULL) return;
    fwrite(&productCount, sizeof(int), 1, file);
    fwrite(products, sizeof(Product), productCount, file);
    fclose(file);
}
