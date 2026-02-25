#include<bits/stdc++.h>
using namespace std;

template <typename T>
class Stack {
private:
    vector<T> arr;

public:
    void push(T value) {
        arr.push_back(value);
    }

    T pop() {
        if (isEmpty()) {
            throw runtime_error("Stack Underflow");
        }
        T value = arr.back();
        arr.pop_back();
        return value;
    }

    T peek() {
        if (isEmpty()) {
            throw runtime_error("Stack is Empty");
        }
        return arr.back();
    }

    bool isEmpty() {
        return arr.empty();
    }

    int size() {
        return arr.size();
    }
};

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return -1;
}

string infixToPostfix(string exp) {
    Stack<char> st;
    string result = "";

    for (char ch : exp) {
        
        // If operand
        if (isalnum(ch)) {
            result += ch;
        }
        // If '('
        else if (ch == '(') {
            st.push(ch);
        }
        // If ')'
        else if (ch == ')') {
            while (!st.isEmpty() && st.peek() != '(') {
                result += st.pop();
            }
            st.pop(); // remove '('
        }
        // If operator
        else {
            while (!st.isEmpty() && precedence(ch) <= precedence(st.peek())) {
                result += st.pop();
            }
            st.push(ch);
        }
    }

    // Pop remaining operators
    while (!st.isEmpty()) {
        result += st.pop();
    }

    return result;
}

int evaluatePostfix(string exp) {
    Stack<int> st;

    for (char ch : exp) {

        // If digit
        if (isdigit(ch)) {
            st.push(ch - '0');
        }
        // If operator
        else {
            int val2 = st.pop();
            int val1 = st.pop();

            switch (ch) {
                case '+': st.push(val1 + val2); break;
                case '-': st.push(val1 - val2); break;
                case '*': st.push(val1 * val2); break;
                case '/': st.push(val1 / val2); break;
                case '^': st.push(pow(val1, val2)); break;
            }
        }
    }

    return st.pop();
}

int main() {
    string infix = "3+(2*4)-5";

    string postfix = infixToPostfix(infix);
    cout << "Postfix: " << postfix << endl;

    int result = evaluatePostfix(postfix);
    cout << "Result: " << result << endl;

    return 0;
}