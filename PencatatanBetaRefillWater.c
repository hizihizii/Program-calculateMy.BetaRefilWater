#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>

char PATH[] = "./sales.txt"; // File path

typedef struct {
    int id, transDate, transMonth, transYear;
    char customerName[255]; // in order to accommodate customer name
    char productType[255]; // in order to accommodate product type
    char productName[255]; // in order to accommodate procuct name
    int productStock;   //  in order to accommodate stock 
    float productPrice; // in order to accommodate price
    float totalPayment; // in order to accommodate total price
} barang;

int dataLength = 1;

barang selectedData, *currentDatas;

void displayType() 
{
    // Function to display thing
    printf("====Which one====\n");
    printf("Type '1' for Aqua\n");
    printf("Type '2' for Vit\n");
    printf("Type '3' for Beta\n");
    printf("Type '4' for Mizone\n");
    printf("Type '5' for Club\n");
    printf("=================\n\n");
}

int displayModifyMenu() 
{
    // Function to display modify menu
    int input = 0, 
        arrowPos = 1;

    do {
        system("cls");

        // Display Modify Menu
        printf("==========MODIFY DATA MENU===========\n");
        (arrowPos == 1) ? printf(" > Modify price\n") : printf(" Modify price\n");
        (arrowPos == 2) ? printf(" > Modify stock\n") : printf(" Modify stock\n");
        (arrowPos == 3) ? printf(" > Re-select id\n") : printf(" Re-select id\n");
        (arrowPos == 4) ? printf(" > Back to main menu\n") : printf(" Back to main menu\n");
        printf("======================================\n");
        printf("Use up and down to move the key\n");

        input = getch();
        fflush(stdin);

        // Choose menu using arrow keys
        if (input == 80 && arrowPos != 4) arrowPos++; // 80 is arrow down ASCII
        else if (input == 72 && arrowPos != 1) arrowPos--; // 72 is arrow up ASCII
        // Choose menu using number keys
        else if (input >= (int)'1' && input <= (int)'4') arrowPos = input - (int)'0';
    } while (input != 13);

    return arrowPos; // Return modify menu input
}

void displaySelectedData() 
{
    // Function to display selected data
    // Display selected data
    printf("=====================================================================================================================\n");
    printf("ID\tTrans. date\tCustomer Name\tProduct Type\tProduct Name\tProduct Stock\tProduct Price\tTotal Payment\t\n");
    printf("=====================================================================================================================\n");
    printf("%d\t%4d/%d/%d\t%8s\t%8s\t%8s\t%8d\t%9.2f\t%9.2f\n", selectedData.id, selectedData.transDate, selectedData.transMonth, selectedData.transYear, 
            selectedData.customerName, selectedData.productType, selectedData.productName, selectedData.productStock, selectedData.productPrice, 
            selectedData.totalPayment);
    printf("---------------------------------------------------------------------------------------------------------------------\n");
}

int displaySortMenu() 
{
    // Function to display sort menu
    int input = 0, 
        arrowPos = 1;

    do {
        system("cls");

        // Display sort Menu
        printf("==========SORT DATA=============\n");
        (arrowPos == 1) ? printf(" > Sort by Id\n") : printf(" Sort by Id\n");
        (arrowPos == 2) ? printf(" > Sort from lowest price\n") : printf(" Sort from lowest price\n");
        (arrowPos == 3) ? printf(" > Sort from highest price\n") : printf(" Sort from highest price\n");
        (arrowPos == 4) ? printf(" > Sort from oldest date\n") : printf(" Sort from oldest date\n");
        (arrowPos == 5) ? printf(" > Sort from newest date\n") : printf(" Sort from newest date\n");
        (arrowPos == 6) ? printf(" > Back to main menu\n") : printf(" Back to main menu\n");
        printf("================================\n");
        printf("Use up and down to move the key\n");

        input = getch();
        fflush(stdin);

        // Choose menu using arrow keys
        if (input == 80 && arrowPos != 6) arrowPos++; // 80 is arrow down ASCII
        else if (input == 72 && arrowPos != 1) arrowPos--; // 72 is arrow up ASCII
        // Choose menu using number keys
        else if (input >= (int)'1' && input <= (int)'6') arrowPos = input - (int)'0';
    } while (input != 13);

    return arrowPos; // Return sort menu input
}

int displaySearchMenu() 
{
    // Function to display search menu
    int input = 0, 
        arrowPos = 1;

    do {
        system("cls");

        // Display Search Menu
        printf("==========SEARCH DATA =============\n");
        (arrowPos == 1) ? printf("  > Search by Id\n") : printf(" Search by Id\n");
        (arrowPos == 2) ? printf("  > Search by product name\n") : printf(" Search by product name\n");
        (arrowPos == 3) ? printf("  > Search most sold\n") : printf(" Search most sold\n");
        (arrowPos == 4) ? printf("  > Search sales in a month\n") : printf(" Search sales in a month\n");
        (arrowPos == 5) ? printf("  > Back to main menu\n") : printf(" Back to main menu\n");
        printf("===================================\n");
        printf("Use up and down to move the key\n");

        input = getch();
        fflush(stdin);

        // Choose menu using arrow keys
        if (input == 80 && arrowPos != 5) arrowPos++; // 80 is arrow down ASCII
        else if (input == 72 && arrowPos != 1) arrowPos--; // 72 is arrow up ASCII
        // Choose menu using number keys
        else if (input >= (int)'1' && input <= (int)'5') arrowPos = input - (int)'0';
    } while (input != 13);

    return arrowPos; // Return search menu input
}

// Utilites functions
int validateId(int target) {
    // Function to validate sales id
    FILE *fp = fopen(PATH, "r"); // Open file with read mode
    
    int isExist = 0;

    // Check whenever the id is exist inside data
    while (fscanf(fp, "%d,%d/%d/%d,%[^,],%[^,],%[^,],%d,%f,%f\r\n", &selectedData.id, &selectedData.transDate, &selectedData.transMonth, &selectedData.transYear,
            selectedData.customerName, selectedData.productType, selectedData.productName, &selectedData.productStock, &selectedData.productPrice, &selectedData.totalPayment) != EOF) {
        if (selectedData.id == target) {
            isExist = 1;
            break;
        } 
    }

    fclose(fp); // Close file

    return isExist; // Return a boolean type as indicator the id exist inside data
}

int validateProdName(char prodName[]) {
    // Function to validate product name
    FILE *fp = fopen(PATH, "r"); // Open file with read mode

    barang temp;

    char tempDate[255], tempStr[255];
    int isExist = 0;

    // Check whenever product name exist inside data
    while (fscanf(fp, "%d,%[^,],%[^,],%[^,],%[^,],%[^\n]\r\n", &temp.id, tempDate, temp.customerName, temp.productType, 
            temp.productName, tempStr) != EOF) {
        if (!strcmpi(prodName, temp.productName)) {
            isExist = 1;
            break;
        }
    }

    fclose(fp); // Close file

    return isExist; // Return a boolean type as indicator the product exist inside data
}

int countData() {
    // Function to count datas inside file
    FILE *fp = fopen(PATH, "r"); // Open file with read mode

    int count = 0; // This variable represent data count inside file

    char strTemp[255];

    // Counting data algorithm
    while (fscanf(fp, "%[^\n]\r\n", strTemp) != EOF) count++;

    fclose(fp); // Close file

    return count;
}

int getCurrentData() {
    // Function to copy all datas from file into a strcut of array
    FILE *fp = fopen(PATH, "r"); // Open file with read mode

    dataLength = 1;

    int mostSoldVal = 0;
    // Store current datas into a struct of array
    while (fscanf(fp, "%d,%d/%d/%d,%[^,],%[^,],%[^,],%d,%f,%f\r\n", &currentDatas[dataLength - 1].id, &currentDatas[dataLength - 1].transDate, 
            &currentDatas[dataLength - 1].transMonth, &currentDatas[dataLength - 1].transYear, currentDatas[dataLength - 1].customerName, currentDatas[dataLength - 1].productType, 
            currentDatas[dataLength - 1].productName, &currentDatas[dataLength - 1].productStock, &currentDatas[dataLength - 1].productPrice, &currentDatas[dataLength - 1].totalPayment) != EOF) {
            currentDatas = (barang *) realloc(currentDatas, (dataLength + 1) * sizeof(barang));

            // Get most sold product index
            if (currentDatas[dataLength - 1].productStock > mostSoldVal) mostSoldVal = currentDatas[dataLength - 1].productStock;

            dataLength++;
    }

    dataLength--;

    fclose(fp); // Close file

    return mostSoldVal; // Return the most sold value
}

// Sorting algorithm functions
void swap(barang *data1, barang *data2) {
    // Function to swap 2 structs
    barang temp = *data1;
    *data1 = *data2;
    *data2 = temp;
}

int partition(int lowBound, int highBound, int method) {
    // Function to search for quick sort pivot
    int pointer = lowBound - 1;

    // Swap number less than pivot
    for (int counter = lowBound; counter < highBound; counter++) {
        if ((method == 1 && currentDatas[counter].id <= currentDatas[highBound].id) || 
            (method == 2 && currentDatas[counter].productPrice <= currentDatas[highBound].productPrice) || 
            (method == 3 && currentDatas[counter].productPrice >= currentDatas[highBound].productPrice) ||
            (method == 4 && (currentDatas[counter].transYear <= currentDatas[highBound].transYear || 
            currentDatas[counter].transMonth <= currentDatas[highBound].transYear || 
            currentDatas[counter].transDate <= currentDatas[highBound].transDate)) || 
            (method == 5 && (currentDatas[counter].transYear >= currentDatas[highBound].transYear || 
            currentDatas[counter].transMonth >= currentDatas[highBound].transYear || 
            currentDatas[counter].transDate >= currentDatas[highBound].transDate))) {
                pointer++;
                swap(&currentDatas[counter], &currentDatas[pointer]);
        }
    }

    swap(&currentDatas[highBound], &currentDatas[pointer + 1]);

    return pointer + 1;
}

void quickSort(int lowBound, int highBound, int method) {
    /*
    Method details:
    1 for sorting by id
    2 for sorting from lowest price
    3 for sorting from highest price
    4 for sorting from oldest date
    5 for sorting from newest date
    */
    // Quick sort algorithm
    if (lowBound < highBound) {
        int pivot = partition(lowBound, highBound, method);

        quickSort(lowBound, pivot - 1, method);
        quickSort(pivot + 1, highBound, method);
    }
}

// Sort functions
void displaySortedData() {
    // Function to display sorted data
    // Display sorted data
    printf("=====================================================================================================================\n");
    printf("ID\tTrans. date\tCustomer Name\tProduct Type\tProduct Name\tProduct Stock\tProduct Price\tTotal Payment\t\n");
    printf("=====================================================================================================================\n");
    for (int counter = 0; counter < dataLength; counter++) {
        printf("%d\t%4d/%d/%d\t%8s\t%8s\t%8s\t%8d\t%9.2f\t%9.2f\n", currentDatas[counter].id, currentDatas[counter].transDate, 
            currentDatas[counter].transMonth, currentDatas[counter].transYear, currentDatas[counter].customerName, currentDatas[counter].productType, 
            currentDatas[counter].productName, currentDatas[counter].productStock, currentDatas[counter].productPrice, currentDatas[counter].totalPayment);
        printf("---------------------------------------------------------------------------------------------------------------------\n");
    }
}

// Search functions
void searchById() {
    // Function to search data from it's id
    int tempId;

    // Input sales id
    printf("Input Id to search: ");
    scanf("%d", &tempId); getchar();

    // Validate id
    if (!validateId(tempId)) printf("\nData not found\n");
    else {
        system("cls");

        displaySelectedData();
    }

    putchar('\n');
}

void searchByProdName() {
    // Function to search data from it's product name
    char tempName[255];

    // Input product name
    printf("Input product name to search: ");
    scanf("%[^\n]", tempName); getchar();

    // Validate product name
    if (!validateProdName(tempName)) printf("\nData not found\n");
    else {
        system("cls");
    
        // Display selected data
        printf("=====================================================================================================================\n");
        printf("ID\tTrans. date\tCustomer Name\tProduct Type\tProduct Name\tProduct Stock\tProduct Price\tTotal Payment\t\n");
        printf("=====================================================================================================================\n");
        // Linear search algorithm
        for (int counter = 0; counter < dataLength; counter++) {
            if (!strcmpi(tempName, currentDatas[counter].productName)) {
                printf("%d\t%4d/%d/%d\t%8s\t%8s\t%8s\t%8d\t%9.2f\t%9.2f\n", currentDatas[counter].id, currentDatas[counter].transDate, 
                    currentDatas[counter].transMonth, currentDatas[counter].transYear, currentDatas[counter].customerName, 
                    currentDatas[counter].productType, currentDatas[counter].productName, currentDatas[counter].productStock, 
                    currentDatas[counter].productPrice, currentDatas[counter].totalPayment);
                printf("---------------------------------------------------------------------------------------------------------------------\n");
            }
        }

        putchar('\n');
    }
}

void searchMostSold(int maxVal) {
    // Function to search the most sold product
    // Display selected data
    printf("=====================================================================================================================\n");
    printf("ID\tTrans. date\tCustomer Name\tProduct Type\tProduct Name\tProduct Stock\tProduct Price\tTotal Payment\t\n");
    printf("=====================================================================================================================\n");
    // Linear search algorithm
    for (int counter = 0; counter < dataLength; counter++) {
        if (currentDatas[counter].productStock == maxVal) {
            printf("%d\t%4d/%d/%d\t%8s\t%8s\t%8s\t%8d\t%9.2f\t%9.2f\n", currentDatas[counter].id, currentDatas[counter].transDate, 
                currentDatas[counter].transMonth, currentDatas[counter].transYear, currentDatas[counter].customerName, 
                currentDatas[counter].productType, currentDatas[counter].productName, currentDatas[counter].productStock, 
                currentDatas[counter].productPrice, currentDatas[counter].totalPayment);
            printf("---------------------------------------------------------------------------------------------------------------------\n");
        }
    }
}

void searchSalesMonth() {
    // Function to search sales in a month
    int tempMonth;

    // Input month to search
    do {
        printf("Input month to search: ");
        scanf("%d", &tempMonth); getchar();

        // Validate month input
        if (tempMonth <= 0 || tempMonth > 12) printf("Invalid month input\n");
    } while (tempMonth <= 0 || tempMonth > 12);

    system("cls");

    // Display selected data
    printf("=====================================================================================================================\n");
    printf("ID\tTrans. date\tCustomer Name\tProduct Type\tProduct Name\tProduct Stock\tProduct Price\tTotal Payment\t\n");
    printf("=====================================================================================================================\n");
    // Linear search algorithm
    for (int counter = 0; counter < dataLength; counter++) {
        if (currentDatas[counter].transMonth == tempMonth) {
            printf("%d\t%4d/%d/%d\t%8s\t%8s\t%8s\t%8d\t%9.2f\t%9.2f\n", currentDatas[counter].id, currentDatas[counter].transDate, 
                currentDatas[counter].transMonth, currentDatas[counter].transYear, currentDatas[counter].customerName, 
                currentDatas[counter].productType, currentDatas[counter].productName, currentDatas[counter].productStock, 
                currentDatas[counter].productPrice, currentDatas[counter].totalPayment);
            printf("---------------------------------------------------------------------------------------------------------------------\n");
        }
    }
}

// Main functions
void display() {
    // Function to display stored datas
    FILE *fp = fopen(PATH, "r"); // Open file with read mode

    barang temp;

    // Display available datas
    printf("=====================================================================================================================\n");
    printf("ID\tTrans. date\tCustomer Name\tProduct Type\tProduct Name\tProduct Stock\tProduct Price\tTotal Payment\t\n");
    printf("=====================================================================================================================\n");
    while (fscanf(fp, "%d,%d/%d/%d,%[^,],%[^,],%[^,],%d,%f,%f\r\n", &temp.id, &temp.transDate, &temp.transMonth, &temp.transYear, temp.customerName, 
            temp.productType, temp.productName, &temp.productStock, &temp.productPrice, &temp.totalPayment) != EOF) {
        printf("%d\t%4d/%d/%d\t%8s\t%8s\t%8s\t%8d\t%9.2f\t%9.2f\n", temp.id, temp.transDate, temp.transMonth, temp.transYear, temp.customerName, 
                temp.productType, temp.productName, temp.productStock, temp.productPrice, temp.totalPayment);
        printf("---------------------------------------------------------------------------------------------------------------------\n");
    }

    fclose(fp); // Close file
}

int create() {
    // Function create new data
    FILE *fp = fopen(PATH, "a"); // Open file with append mode
    
    display();

    putchar('\n');

    barang temp;
    
    // Input sale id
    do {
        printf("Input id: ");
        scanf("%d", &temp.id); getchar();

        // Validate id existence
        if (validateId(temp.id)) printf("Id already exist\n");
        else if (temp.id <= 0) printf("Id cannot 0 or less than 0\n");
    } while (validateId(temp.id));

    // Input transaction date
    do {
        printf("Input transaction date(format: dd/mm/yyyy): ");
        scanf("%d/%d/%d", &temp.transDate, &temp.transMonth, &temp.transYear); getchar();

        // Validate date input
        if (temp.transDate <= 0 || temp.transMonth <= 0 || temp.transMonth > 12 || temp.transYear <= 0 || 
            (temp.transMonth == 2 && ((temp.transYear % 4 == 0 && temp.transDate > 29) || (temp.transDate % 4 != 0 && 
            temp.transDate > 28))) || (temp.transMonth % 2 == 0) && ((temp.transMonth <= 7 && temp.transDate > 30) || 
            (temp.transMonth >= 8 && temp.transDate > 31)) || (temp.transMonth % 2 == 1) && ((temp.transMonth <= 7 && 
            temp.transDate > 31) || (temp.transMonth >= 8 && temp.transDate > 30))) {
                printf("Invalid input\n");
            }
    } while (temp.transDate <= 0 || temp.transMonth <= 0 || temp.transMonth > 12 || temp.transYear <= 0 || 
            (temp.transMonth == 2 && ((temp.transYear % 4 == 0 && temp.transDate > 29) || (temp.transDate % 4 != 0 && 
            temp.transDate > 28))) || (temp.transMonth % 2 == 0) && ((temp.transMonth <= 7 && temp.transDate > 30) || 
            (temp.transMonth >= 8 && temp.transDate > 31)) || (temp.transMonth % 2 == 1) && ((temp.transMonth <= 7 && 
            temp.transDate > 31) || (temp.transMonth >= 8 && temp.transDate > 30)));

    // Input customer name
    int isValid = 1;
    do {
        printf("Input customer name: ");
        scanf("%[^\n]", temp.customerName); getchar();

        int index = 0;
        while (temp.customerName[index] != '\0') {
            // Validate char
            if ((!(temp.customerName[index] >= 'a' || temp.customerName[index] <= 'z') || 
                !(temp.customerName[index] >= 'A' || temp.customerName[index] <= 'Z')) && 
                temp.customerName[index] != ' ' && (strlen(temp.customerName) == 1 && 
                temp.customerName[index] == ' ')) {
                    printf("Invalid name\n");

                    isValid = 0;
                    break;
                }

            // Capitilize char
            if (index == 0 || (temp.customerName[index - 1] == ' ')) temp.customerName[index] = toupper(temp.customerName[index]);
            // Normalize char
            else temp.customerName[index] = tolower(temp.customerName[index]);

            index++;
        }
    } while (!isValid);

    putchar('\n');

    displayType();

    int TypeInput;

    // Input product type
    do {
        printf("Input product type: ");
        scanf("%d", &TypeInput); getchar();
        
        // Validate vehicle type input
        if (TypeInput < 1 || TypeInput > 5) printf("Invalid input\n");
    } while (TypeInput < 1 ||TypeInput > 5);

    // This array represent possible types
    char types[5][255] = {"Aqua", "Vit", "Beta", "Mizone", "Club"};

    // Input product name
    printf("Input product name: ");
    scanf("%[^\n]", temp.productName); getchar();

    temp.productName[0] = toupper(temp.productName[0]);

    // Input product stock
    do {
        printf("Input product stock: ");
        scanf("%d", &temp.productStock); getchar();

        // Validate product stock
        if (temp.productStock <= 0) printf("Invalid stock number\n");
    } while (temp.productStock <= 0);

    // Input product price
    do {
        printf("Input product price: ");
        scanf("%f", &temp.productPrice); getchar();

        // Validate product price
        if (temp.productPrice <= 0) printf("Invalid price number\n");
    } while (temp.productPrice <= 0);

    // Display total payment
    printf("Total Payment: %.2f\n", temp.productPrice * temp.productStock);

    // Append new data into file
    int isSuccess = fprintf(fp, "%d,%d/%d/%d,%s,%s,%s,%d,%.2f,%.2f\n", temp.id, temp.transDate, temp.transMonth, temp.transYear, temp.customerName, 
        types[TypeInput - 1], temp.productName, temp.productStock, temp.productPrice, temp.productPrice * temp.productStock);
    
    fclose(fp); // Close file

    return isSuccess > 0;
}
int delete() 
{
    // Function to delete data
    FILE *fp = fopen(PATH, "r"), // Open original file with read mode
        *tempFile = fopen("./temp.txt", "w"); // Open temp file with write mode

    barang temp; 

    int tempId;
    char isFixed;

    // Input sales id
    do {
        printf("Input id to delete: ");
        scanf("%d", &tempId); getchar();

        // Validate id
        if (!validateId(tempId)) printf("Id is not exist\n");
    } while (!validateId(tempId));
    
    putchar('\n');
    displaySelectedData();
    putchar('\n');
    
    // Ask for user validation to delete data
    do {
        printf("Are you sure to delete [Y/N]? ");
        scanf("%c", &isFixed); getchar();

        // Validate input
        if ((isFixed != 'N' && isFixed != 'n') &&
            (isFixed != 'Y' && isFixed != 'y')) printf("Invalid input\n");
    } while ((isFixed != 'N' && isFixed != 'n') &&
            (isFixed != 'Y' && isFixed != 'y'));

    if (isFixed == 'N' || isFixed == 'n') {
        fclose(fp); // Close original file
        fclose(tempFile); // Close temp file

        return 0; // Exit function
    }

    // Copy datas from original file to temp file except the inputted id
    while (fscanf(fp, "%d,%d/%d/%d,%[^,],%[^,],%[^,],%d,%f,%f\r\n", &temp.id, &temp.transDate, &temp.transMonth, &temp.transYear, temp.customerName, 
            temp.productType, temp.productName, &temp.productStock, &temp.productPrice, &temp.totalPayment) != EOF) {
        if (temp.id != tempId) {
            fprintf(tempFile, "%d,%d/%d/%d,%s,%s,%s,%d,%.2f,%.2f\n", temp.id, temp.transDate, temp.transMonth, temp.transYear, temp.customerName, 
                    temp.productType, temp.productName, temp.productStock, temp.productPrice, temp.totalPayment);
        }
    }

    fclose(fp); // Close original file
    fclose(tempFile); // Close temp file

    return !remove("sales.txt") && // Delete original file
            !rename("temp.txt", "sales.txt"); // Rename temp file into original file
}
int modify() 
{
    // Function to modify existing data
    FILE *fp = fopen(PATH, "r"), // Open file with read mode
        *tempFile = fopen("./temp.txt", "w"); // Open file with write mode

    display();

    barang temp;
    
    int tempId;
    
    // Input sales id
    do {
        printf("\nInput id to modify: ");
        scanf("%d", &tempId); getchar();

        // Validate id
        if (!validateId(tempId)) printf("Id is not exist\n");
    } while (!validateId(tempId));

    system("cls");

    displaySelectedData();
    putchar('\n');

    float tempPrice, tempStock;
    
    int input;

    switch (input = displayModifyMenu()) 
    {
        case 1:
            // Input new price
            do {
                printf("Input new product price: ");
                scanf("%f", &tempPrice); getchar();

                // Validate price number
                if (tempPrice <= 0) printf("Invalid price number\n");
            } while (tempPrice <= 0);

            break;
        
        case 2:
            // Input new stock
            do {
                printf("Input new product stock: ");
                scanf("%f", &tempStock); getchar();

                // Validate stock number
                if (tempStock <= 0) printf("Invalid stock number\n");
            } while (tempStock <= 0);

            break;
    }

    if (input == 3) {
        system("cls");

        fclose(fp); // Close original file
        fclose(tempFile); // Close temp file

        return 0; // Exit function
    }
    else if (input == 4) {
        system("cls");

        fclose(fp); // Close original file
        fclose(tempFile); // Close temp file

        return -1;
    }

    // Copy datas from original file and paste to temp file with modifying the old data value
    while (fscanf(fp, "%d,%d/%d/%d,%[^,],%[^,],%[^,],%d,%f,%f\r\n", &temp.id, &temp.transDate, &temp.transMonth, &temp.transYear, temp.customerName, 
            temp.productType, temp.productName, &temp.productStock, &temp.productPrice, &temp.totalPayment) != EOF) {
        temp.productPrice = (input == 1 && temp.id == tempId) ? tempPrice : temp.productPrice;
        temp.productStock = (input == 2 && temp.id == tempId) ? tempStock : temp.productStock;
        
        fprintf(tempFile, "%d,%d/%d/%d,%s,%s,%s,%d,%f,%f\n", temp.id, temp.transDate, temp.transMonth, temp.transYear, temp.customerName, 
                temp.productType, temp.productName, temp.productStock, temp.productPrice, 
                (temp.id == tempId) ? temp.productPrice * temp.productStock : temp.totalPayment);
    }

    fclose(fp); // Close original file
    fclose(tempFile); // Close temp file

    return !remove("sales.txt") && // Delete original file
            !rename("temp.txt", "sales.txt"); // Rename temp file into original file
}
void sortData() 
{
    // Function to sort data from file
    currentDatas = malloc(sizeof(barang));

    int menuInput = displaySortMenu(); // display few option

    if (menuInput == 6) return; // Exit function

    getCurrentData();

    system("cls");

    // Sort data
    quickSort(0, dataLength - 1, menuInput);

    displaySortedData();

    free(currentDatas);

    system("pause");
}

void searchData() 
{
    // Function to search data from file
    currentDatas = malloc(sizeof(barang));

    int menuInput = displaySearchMenu();

    if (menuInput == 5) return; // Exit function
    
    int mostSold = getCurrentData();

    system("cls");

    if (menuInput != 3 && menuInput != 4) {
        display();
        putchar('\n');
    }

    switch (menuInput) {
        case 1: // Search by id
            searchById();
            break;
        
        case 2: // Search by product name
            searchByProdName();
            break;

        case 3: // Search most sold product
            searchMostSold(mostSold);
            break;

        case 4: // Search sales in a month
            searchSalesMonth();
            break;
    }

    free(currentDatas);

    system("pause");
}

// Program main driver 
int main() 
{
    
    // Program main process
    do {
        int input;
        printf("==========");
        printf("MAIN MENU");
        printf("==========\n");
        printf("1. Create\n");
        printf("2. Sort data\n");
        printf("3. Search data\n");
        printf("4. Display\n");
        printf("5. Modify\n");
        printf("6. Delete\n");
        printf("7. Exit\n");
        printf("=============================\n");
        printf("Whatcha gonna do :");
        scanf("%d", &input);
        getchar();

        system("cls");

        switch (input) {
            case 1: // Create or add
                if (create()) printf("\nData added successfully\n\n");
                else printf("\nFailed add data\n\n");

                system("pause");
                break;
            
            case 2: // Sort
                if (countData()) {
                    sortData();
                    putchar('\n');
                }
                else printf("There is no data in file. Please create a new one\n\n");
                break;

            case 3: // Search
                if (countData()) {
                    searchData();
                    putchar('\n');
                }
                else printf("There is no data in file. Please create a new one\n\n");
                break;

            case 4: // Display
                display();

                putchar('\n');

                system("pause");
                break;

            case 5: // Modify
                if (countData()) {
                    int isTrue = 0;
                    while (isTrue == 0) isTrue = modify();

                    if (isTrue != -1) printf("\nData modified successfully\n\n");
                    else printf("\nFailed modify data\n\n");
                }
                else printf("There is no data in file. Please create a new one\n\n");

                system("pause");
                break;
                
            case 6: // Delete
                if (countData()) {
                    display();

                    putchar('\n');

                    if (delete()) printf("\nData deleted successfully\n\n");
                    else printf("\nFailed delete data\n\n");
                }
                else printf("There is no data in file. Please create a new one\n\n");

                system("pause");
                break;
        }

        if (input == 7) break;
    } while (1);

    return 0;
}