/*PRN: 123B1B221
Name: Pranali Rajendra Patil
Assignment number: 8
Assignment Title:
Write a program to convert infix expression to postfix, infix expression to prefix and evaluation of postfix and prefix expression.*/

#include <iostream>
#include <cstring> // for strlen()
#include <cmath>   // for pow()
using namespace std;

// Stack for operators and operands in postfix/prefix evaluation
class stack1 {
public:
    char data[100];  // Array to store characters (operators/operands)
    int top;         // Index of the top of the stack

    stack1() {       // Constructor to initialize the top of the stack
        top = -1;
    }

    void push(char c) {    // Push a character onto the stack
        data[++top] = c;
    }

    char pop() {           // Pop a character from the stack
        return data[top--];
    }

    char get_top() {       // Peek at the top of the stack without popping it
        return data[top];
    }

    bool isempty() {       // Check if the stack is empty
        return top == -1;
    }
};

// Stack for storing integer values during evaluation
class stack2 {
public:
    int data[100];   // Array to store integers (operands)
    int top;         // Index of the top of the stack

    stack2() {       // Constructor to initialize the top of the stack
        top = -1;
    }

    void push(int val) {   
        data[++top] = val;
    }

    int pop() {            
        return data[top--];
    }

    bool isempty() {       
        return top == -1;
    }
};

// Helper function to check if a character is an operator
int isop(char op) {
    return (op == '+' || op == '-' || op == '*' || op == '/' || op == '^');
}

// Function to determine the priority of operators
int priority(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

// Function to perform calculations based on operator and operands
int cal(char op, int a, int b) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        case '^': return pow(a, b);
    }
    return 0;
}

// Function to convert infix expression to postfix
void infix_toPostfix(char inf[], char post[]) {
    stack1 s1;
    int j = 0;
    for (int i = 0; i < strlen(inf); i++) {
        char x = inf[i];

        if (isalpha(x)) {  // If it's an operand (variable), add to output
            post[j++] = x;
        } else if (isop(x)) {  // If it's an operator
            while (!s1.isempty() && priority(s1.get_top()) >= priority(x)) {
                post[j++] = s1.pop();  // Pop operators from the stack based on priority
            }
            s1.push(x);  // Push current operator onto the stack
        } else if (x == '(') {  // If it's an opening parenthesis, push to stack
            s1.push(x);
        } else if (x == ')') {  // If it's a closing parenthesis, pop until '(' is found
            while (s1.get_top() != '(') {
                post[j++] = s1.pop();
            }
            s1.pop();  // Pop the opening parenthesis
        }
    }
    while (!s1.isempty()) {  // Pop remaining operators from the stack
        post[j++] = s1.pop();
    }
    post[j] = '\0';  // Terminate the postfix expression with null character
}

// Function to convert infix expression to prefix
void infix_toPrefix(char inf[], char pre[]) {
    stack1 s1;
    int j = 0;
    for (int i = strlen(inf) - 1; i >= 0; i--) {  // Iterate over the infix expression from right to left
        char x = inf[i];

        if (isalpha(x)) {  // If it's an operand (variable), add to output
            pre[j++] = x;
        } else if (isop(x)) {  // If it's an operator
            while (!s1.isempty() && priority(s1.get_top()) > priority(x)) {
                pre[j++] = s1.pop();  // Pop operators with higher priority
            }
            s1.push(x);  // Push the current operator onto the stack
        } else if (x == ')') {  // If it's a closing parenthesis, push to stack
            s1.push(x);
        } else if (x == '(') {  // If it's an opening parenthesis, pop until ')' is found
            while (s1.get_top() != ')') {
                pre[j++] = s1.pop();
            }
            s1.pop();  // Pop the closing parenthesis
        }
    }
    while (!s1.isempty()) {  // Pop remaining operators from the stack
        pre[j++] = s1.pop();
    }
    pre[j] = '\0';  // Terminate the prefix expression with null character
}

// Function to reverse a string (used to reverse the prefix result)
void reverseStr(char str[]) {
    int n = strlen(str);
    for (int i = 0; i < n / 2; i++) {
        swap(str[i], str[n - i - 1]);  // Swap characters from the beginning and end
    }
}

// Function to evaluate a postfix expression
void eval_postfix(char post[]) {
    stack2 s1;
    for (int i = 0; i < strlen(post); i++) {
        char x = post[i];

        if (isalpha(x)) {  // If it's an operand, ask for its value
            int val;
            cout << "Enter value of " << x << ": ";
            cin >> val;
            s1.push(val);  // Push the value onto the stack
        } else if (isop(x)) {  // If it's an operator
            int op2 = s1.pop();  // Pop two operands from the stack
            int op1 = s1.pop();
            s1.push(cal(x, op1, op2));  // Push the result of the operation
        }
    }
    cout << "Evaluation of Postfix: " << s1.pop() << endl;  // Final result of postfix evaluation
}

// Function to evaluate a prefix expression
void eval_prefix(char pre[]) {
    stack2 s1;
    for (int i = strlen(pre) - 1; i >= 0; i--) {  // Iterate over the prefix expression from right to left
        char x = pre[i];

        if (isalpha(x)) {  // If it's an operand, ask for its value
            int val;
            cout << "Enter value of " << x << ": ";
            cin >> val;
            s1.push(val);  // Push the value onto the stack
        } else if (isop(x)) {  // If it's an operator
            int op1 = s1.pop();  // Pop two operands from the stack
            int op2 = s1.pop();
            s1.push(cal(x, op1, op2));  // Push the result of the operation
        }
    }
    cout << "Evaluation of Prefix: " << s1.pop() << endl;  
}

// Main function to handle menu options
int main() {
    char inf[100], post[100], pre[100];
    int choice;

    while (1) {
        cout << "\nMenu:\n";
        cout << "1. Convert Infix to Postfix\n";
        cout << "2. Convert Infix to Prefix\n";
        cout << "3. Evaluate Postfix Expression\n";
        cout << "4. Evaluate Prefix Expression\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter an INFIX expression: ";
                cin >> inf;
                infix_toPostfix(inf, post); 
                cout << "POSTFIX Expression: " << post << endl;
                break;

            case 2:
                cout << "Enter an INFIX expression: ";
                cin >> inf;
                infix_toPrefix(inf, pre);  
                reverseStr(pre); 
                cout << "PREFIX Expression: " << pre << endl;
                break;

            case 3:
                eval_postfix(post);  
                break;

            case 4:
                eval_prefix(pre);    
                break;

            case 5:
                cout << "Exiting...\n";
                return 0;

            default:
                cout << "Invalid choice! Please enter again.\n";
        }
    }

    return 0;
}
