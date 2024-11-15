/* Shopping App Scenario

**Problem Statement:**
In a shopping application, customers add items to their cart and place orders for delivery. 
The cart operates on a stack mechanism, where the last item added is the first to be removed when checking out. 
Meanwhile, the order delivery system operates on a queue system, delivering orders based on the sequence they were placed.

Description:
- **Stack (Shopping Cart):
  - Push: When a customer adds an item to their cart, it is placed on top of the stack.
  - Pop: When the customer checks out, the last item added to the cart is removed first.
  - Peek: View the last item added to the cart without removing it.
  - IsEmpty: Check if the cart is empty before checkout.

- Queue (Order Delivery):
  - Enqueue: When a customer places an order, it is added to the back of the queue.
  - Dequeue: The order that was placed first is processed and delivered first.
  - Peek: View the next order to be delivered without removing it from the queue.
  - IsEmpty: Check if there are any orders pending delivery.
*/

#include <iostream>
#include <string>
using namespace std;

// Node class for both Stack and Queue
class Node {
public:
    string data;
    Node* next;

    Node() {
        next = NULL;
    }

    void readData() {
        cout << "Enter item/order: ";
        cin >> data;
    }

    void displayData() {
        cout << data << endl;
    }
};

// Stack for Shopping Cart
class ShoppingCart {
    Node* top;

public:
    ShoppingCart() {
        top = NULL;
    }

    ~ShoppingCart() {
        while (top != NULL) {
            Node* temp = top;
            top = top->next;
            delete temp;
        }
    }

    // Push (add item to cart)
    void addItem() {
        Node* newNode = new Node();
        newNode->readData();
        newNode->next = top;
        top = newNode;
        cout << "Item added to cart!" << endl;
    }

    // Pop (remove last added item from cart)
    void removeLastItem() {
        if (top == NULL) {
            cout << "Cart is empty, nothing to remove!" << endl;
        } else {
            Node* temp = top;
            top = top->next;
            cout << "Removed last item: " << temp->data << endl;
            delete temp;
        }
    }

    // Peek (view last added item in cart)
    void displayLastItem() {
        if (top == NULL) {
            cout << "Cart is empty!" << endl;
        } else {
            cout << "Last item in cart: " << top->data << endl;
        }
    }

    // Check if cart is empty
    bool isCartEmpty() {
        return top == NULL;
    }

    // Function to display all items in the cart
    void viewCart() {
        if (top == NULL) {
            cout << "Cart is empty!" << endl;
        } else {
            Node* current = top;
            cout << "Items in cart:" << endl;
            while (current != NULL) {
                current->displayData();
                current = current->next;
            }
        }
    }
};

// Queue for Order Delivery
class OrderQueue {
    Node* front;
    Node* rear;

public:
    OrderQueue() {
        front = rear = NULL;
    }

    ~OrderQueue() {
        while (front != NULL) {
            Node* temp = front;
            front = front->next;
            delete temp;
        }
    }

    // Enqueue (add order to queue)
    void placeOrder() {
        Node* newNode = new Node();
        newNode->readData();
        if (rear == NULL) { // Empty queue
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
        cout << "Order placed!" << endl;
    }

    // Dequeue (process next order from queue)
    void processOrder() {
        if (front == NULL) {
            cout << "No orders to process!" << endl;
        } else {
            Node* temp = front;
            cout << "Processing order: " << temp->data << endl;
            front = front->next;
            if (front == NULL) { // Queue is now empty
                rear = NULL;
            }
            delete temp;
        }
    }

    // Peek (view next order in queue)
    void peekNextOrder() {
        if (front == NULL) {
            cout << "No pending orders!" << endl;
        } else {
            cout << "Next order in queue: " << front->data << endl;
        }
    }

    // Check if queue is empty
    bool isOrderQueueEmpty() {
        return front == NULL;
    }

    // Function to display all orders in the queue
    void viewOrders() {
        if (front == NULL) {
            cout << "No orders in the queue!" << endl;
        } else {
            Node* current = front;
            cout << "Orders in the queue:" << endl;
            while (current != NULL) {
                current->displayData();
                current = current->next;
            }
        }
    }
};

int main() {
    ShoppingCart cart;
    OrderQueue orders;

int choice;
    while(1) {
        cout << "\n--- Shopping App Menu ---\n";
        cout << "1. Add Item to Cart\n";
        cout << "2. Remove Last Item from Cart\n";
        cout << "3. View Last Item in Cart\n";
        cout << "4. View All Items in Cart\n";
        cout << "5. Place Order\n";
        cout << "6. Process Next Order\n";
        cout << "7. View Next Order\n";
        cout << "8. Check if Cart is Empty\n";
        cout << "9. Check if Orders are Pending\n";
        cout << "10. View All Orders in Queue\n";
        cout << "11. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cart.addItem();
                break;
            case 2:
                cart.removeLastItem();
                break;
            case 3:
                cart.displayLastItem();
                break;
            case 4:
                cart.viewCart();
                break;
            case 5:
                orders.placeOrder();
                break;
            case 6:
                orders.processOrder();
                break;
            case 7:
                orders.peekNextOrder();
                break;
            case 8:
                if (cart.isCartEmpty()) {
                    cout << "Cart is empty!" << endl;
                } else {
                    cout << "Cart is not empty!" << endl;
                }
                break;
            case 9:
                if (orders.isOrderQueueEmpty()) {
                    cout << "No pending orders!" << endl;
                } else {
                    cout << "Orders are pending!" << endl;
                }
                break;
            case 10:
                orders.viewOrders();
                break;
            case 11:
                cout << "Exiting app..." << endl;
                exit(0);
                break;
            default:
                cout << "Invalid choice! Try again." << endl;
                break;
        }
    } 

    return 0;
}


