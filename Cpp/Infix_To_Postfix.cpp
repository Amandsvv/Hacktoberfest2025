#include <iostream>
#include <stack>
#include <string>
using namespace std;

// Function to return precedence of operators
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3; // exponent has highest precedence
    return 0;
}

// Function to check if character is an operator
bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

// Function to convert infix to postfix
string infixToPostfix(const string &infix) {
    stack<char> st;       // Stack to hold operators
    string postfix = "";  // Output string

    for (char c : infix) {
        // If the character is a space, skip it
        if (c == ' ') continue;

        // If operand (A-Z or a-z or 0-9), add it directly to the output
        if (isalnum(c)) {
            postfix += c;
        }
        // If '(' then push to stack
        else if (c == '(') {
            st.push(c);
        }
        // If ')' then pop until '(' is found
        else if (c == ')') {
            while (!st.empty() && st.top() != '(') {
                postfix += st.top();
                st.pop();
            }
            if (!st.empty()) st.pop(); // pop '('
        }
        // If operator
        else if (isOperator(c)) {
            while (!st.empty() && precedence(st.top()) >= precedence(c)) {
                postfix += st.top();
                st.pop();
            }
            st.push(c);
        }
    }

    // Pop all remaining operators from stack
    while (!st.empty()) {
        postfix += st.top();
        st.pop();
    }

    return postfix;
}

// Main function
int main() {
    string infix;
    cout << "Enter an infix expression: ";
    getline(cin, infix); // read full line including spaces

    string postfix = infixToPostfix(infix);

    cout << "Postfix Expression: " << postfix << endl;

    return 0;
}
