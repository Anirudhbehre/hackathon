#include <stdio.h>
#include <string.h>

#define MAX_ITEMS 6
#define MAX_ORDERS 20

struct Item {
    char name[40];
    float price;
};

struct Order {
    int itemIndex;
    int quantity;
    float cost;
};

int main() {
    // Menu with 6 food items
    struct Item menu[MAX_ITEMS] = {
        {"Samosa", 25.00},
        {"Masala Chai", 15.00},
        {"Veg Sandwich", 45.00},
        {"Maggi", 40.00},
        {"Cold Drink", 30.00},
        {"Burger", 70.00}
    };

    struct Order orders[MAX_ORDERS];
    int orderCount = 0;
    float subtotal = 0.0f;
    int choice, qty;

    printf("===== Welcome to College Canteen =====\n");

    // Order taking loop
    while (1) {
        printf("\n---------- MENU ----------\n");
        for (int i = 0; i < MAX_ITEMS; i++) {
            printf("%d. %-20s Rs. %.2f\n", i + 1, menu[i].name, menu[i].price);
        }
        printf("%d. Finish Order\n", MAX_ITEMS + 1);
        printf("--------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == MAX_ITEMS + 1) {
            break;  // Finish ordering
        }

        if (choice < 1 || choice > MAX_ITEMS) {
            printf("Invalid choice! Please try again.\n");
            continue;
        }

        printf("Enter quantity for %s: ", menu[choice - 1].name);
        scanf("%d", &qty);

        if (qty <= 0) {
            printf("Quantity must be greater than 0.\n");
            continue;
        }

        if (orderCount >= MAX_ORDERS) {
            printf("Maximum orders reached!\n");
            break;
        }

        // Add order
        orders[orderCount].itemIndex = choice - 1;
        orders[orderCount].quantity = qty;
        orders[orderCount].cost = menu[choice - 1].price * qty;
        subtotal += orders[orderCount].cost;
        orderCount++;

        printf("%d x %s added to your order.\n", qty, menu[choice - 1].name);
    }

    if (orderCount == 0) {
        printf("\nNo items ordered. Thank you!\n");
        return 0;
    }

    // Discount logic: 10% discount if bill exceeds Rs. 300
    float discountRate = 0.10f;
    float discountThreshold = 300.0f;
    float discount = 0.0f;

    if (subtotal > discountThreshold) {
        discount = subtotal * discountRate;
    }

    float finalAmount = subtotal - discount;

    // Display Final Bill
    printf("\n\n========== FINAL BILL ==========\n");
    printf("%-20s %8s %6s %10s\n", "Item", "Price", "Qty", "Cost");
    printf("--------------------------------------------\n");

    for (int i = 0; i < orderCount; i++) {
        int idx = orders[i].itemIndex;
        printf("%-20s %8.2f %6d %10.2f\n",
               menu[idx].name,
               menu[idx].price,
               orders[i].quantity,
               orders[i].cost);
    }

    printf("--------------------------------------------\n");
    printf("Subtotal:              Rs. %8.2f\n", subtotal);

    if (discount > 0) {
        printf("Discount (%.0f%%):          Rs. %8.2f\n", discountRate * 100, discount);
    } else {
        printf("Discount:               Rs.     0.00\n");
    }

    printf("--------------------------------------------\n");
    printf("TOTAL PAYABLE:         Rs. %8.2f\n", finalAmount);
    printf("============================================\n");
    printf("Thank you! Visit again.\n");

    return 0;
}