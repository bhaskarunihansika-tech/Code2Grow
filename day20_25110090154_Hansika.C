#include <stdio.h>

#define MAX 20

// Global product arrays
int pID[MAX], qty[MAX], price[MAX];
int count = 0;

// 3x3 Rack Matrix
int rack[3][3] = {
    {5, 8, 3},
    {2, 9, 4},
    {7, 1, 6}
};

// ------------------- FUNCTION DECLARATIONS -------------------
void addProduct();
void searchProduct();
void updateQuantity();
void rackReport();
void calculateStockValue();
void displayAll();

// -------------------------------------------------------------
int main() {
    int ch;

    while (1) {
        printf("\n===== SMART WAREHOUSE MENU =====\n");
        printf("1. Add Product\n");
        printf("2. Search Product\n");
        printf("3. Update Quantity\n");
        printf("4. Generate Rack Report (2D Array)\n");
        printf("5. Calculate Stock Value for Products\n");
        printf("6. Display All Products\n");
        printf("7. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1: addProduct(); break;
            case 2: searchProduct(); break;
            case 3: updateQuantity(); break;
            case 4: rackReport(); break;
            case 5: calculateStockValue(); break;
            case 6: displayAll(); break;
            case 7: return 0;
            default: printf("Invalid Choice!\n");
        }
    }
}

// 1. ADD PRODUCT 
void addProduct() {
    if (count == MAX) {
        printf("Storage Full! Cannot add more products.\n");
        return;
    }

    int id, q, pr, i;

    printf("Enter Product ID: ");
    scanf("%d", &id);

    // Check duplicate
    for (i = 0; i < count; i++) {
        if (pID[i] == id) {
            printf("Duplicate ID! Product already exists.\n");
            return;
        }
    }

    printf("Enter Quantity: ");
    scanf("%d", &q);

    printf("Enter Price: ");
    scanf("%d", &pr);

    if (q <= 0 || pr <= 0) {
        printf("Quantity & Price must be positive!\n");
        return;
    }

    pID[count] = id;
    qty[count] = q;
    price[count] = pr;
    count++;

    printf("Product Added Successfully!\n");
}

// 2. SEARCH PRODUCT 
void searchProduct() {
    int id, i;
    printf("Enter Product ID to search: ");
    scanf("%d", &id);

    for (i = 0; i < count; i++) {
        if (pID[i] == id) {
            printf("FOUND!\n");
            printf("ID: %d  Qty: %d  Price: %d\n", pID[i], qty[i], price[i]);
            return;
        }
    }
    printf("Not Found!\n");
}

// 3. UPDATE QUANTITY 
void updateQuantity() {
    int id, i, ch, amount;
    printf("Enter Product ID: ");
    scanf("%d", &id);

    for (i = 0; i < count; i++) {
        if (pID[i] == id) {
            printf("1. Increase Stock\n2. Decrease Stock\nEnter choice: ");
            scanf("%d", &ch);

            printf("Enter amount: ");
            scanf("%d", &amount);

            if (ch == 1) {
                qty[i] += amount;
            }
            else if (ch == 2) {
                if (qty[i] - amount < 0) {
                    printf("Error! Quantity cannot be negative.\n");
                    return;
                }
                qty[i] -= amount;
            }
            else {
                printf("Invalid Option!\n");
                return;
            }

            printf("Quantity Updated!\n");
            return;
        }
    }
    printf("Product Not Found!\n");
}

//  4. RACK REPORT 
void rackReport() {
    int max = rack[0][0], min = rack[0][0];
    int maxR = 0, maxC = 0, minR = 0, minC = 0;
    int sum = 0;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            int val = rack[i][j];
            sum += val;

            if (val > max) {
                max = val;
                maxR = i;
                maxC = j;
            }
            if (val < min) {
                min = val;
                minR = i;
                minC = j;
            }
        }
    }

    printf("Max Stock = %d at position (%d, %d)\n", max, maxR, maxC);
    printf("Min Stock = %d at position (%d, %d)\n", min, minR, minC);
    printf("Total items across racks = %d\n", sum);
}

//  5. STOCK VALUE 
void calculateStockValue() {
    if (count == 0) {
        printf("No products available!\n");
        return;
    }

    int i;
    int highest = qty[0] * price[0];
    int lowest = qty[0] * price[0];
    int highIndex = 0, lowIndex = 0;
    int total = 0;

    printf("\nID   Qty   Price   StockValue\n");

    for (i = 0; i < count; i++) {
        int sv = qty[i] * price[i];
        printf("%d   %d     %d      %d\n", pID[i], qty[i], price[i], sv);

        total += sv;

        if (sv > highest) {
            highest = sv;
            highIndex = i;
        }
        if (sv < lowest) {
            lowest = sv;
            lowIndex = i;
        }
    }

    printf("\nProduct with Highest Stock Value: ID %d (Value %d)\n", pID[highIndex], highest);
    printf("Product with Lowest Stock Value: ID %d (Value %d)\n", pID[lowIndex], lowest);
    printf("Total Warehouse Stock Value = %d\n", total);
}

//  6. DISPLAY ALL PRODUCTS 
void displayAll() {
    if (count == 0) {
        printf("No products to display!\n");
        return;
    }

    printf("\nID   Quantity   Price   StockValue\n");
    for (int i = 0; i < count; i++) {
        int sv = qty[i] * price[i];
        printf("%d      %d        %d        %d\n", pID[i], qty[i], price[i], sv);
    }
}
