//**************************************************************************************************
// Headers
//**************************************************************************************************
#include <cstdio>

#include <algorithm>
#include <map>
#include <memory>
#include <stack>
#include <string>
#include <vector>

//**************************************************************************************************
// Defines
//**************************************************************************************************
#define log(...)    printf("[%s][%d] %s", __func__, __LINE__, __VA_ARGS__)
#define logf(fmt, ...)   printf("[%s][%d] " fmt, __func__, __LINE__, __VA_ARGS__)

//**************************************************************************************************
// Data Types
//**************************************************************************************************
struct op_st {
    int priority;
    char op;
};

//**************************************************************************************************
// Data
//**************************************************************************************************
std::map<int, std::vector<char>> operators = {
    // 1. Scope	::	scope qualifier	Left-to-right
    // 2. Postfix (unary) | Left-to-right
    //      ++, --   | postfix increment/decrement
    //      ()       | functional forms
    //      []       | subscript
    //      . ->	    | member access
    // 3. Prefix (unary) | Right-to-left
    //      ++ --	 prefix increment / decrement
    //      ~ !	bitwise NOT / logical NOT
    //      + -	unary prefix
    //      & *	reference / dereference
    //      new delete	allocation / deallocation
    //      sizeof	parameter pack
    //      (type)	C-style type-casting
    // 4. Pointer-to-member | Left-to-right
    //      .* ->*	access pointer
    { 5, {'*', '/', '%'}},  // Arithmetic | multiply, divide, modulo | Left-to-right
    { 6, {'+', '-'}},       // Arithmetic | addition, subtraction | Left-to-right
    // 7. Bitwise shift | Left-to-right
    //      << >>	shift left, shift right
    // 8. Relational | Left-to-right
    //      < > <= >=   comparison operators
    // 9. Equality	== !=	equality / inequality	Left-to-right
    { 10, {'&'}},   // AND | bitwise AND | Left-to-right
    { 11, {'^'}},   // Exclusive or | bitwise XOR | Left-to-right
    { 12, {'|'}}    // Inclusive or | bitwise OR  | Left-to-right
    // 13. Conjunction | Left-to-right
    //      &&  logical AND
    // 14. Disjunction | Left-to-right
    //      ||  logical OR	
    // 15. Assignment-level expressions	| Right-to-left
    //      = *= /= %= += -= >>= <<= &= ^= |=   assignment / compound assignment	
    //      ?   conditional operator
    // 16. Sequencing | Left-to-right
    //      ,   comma separator
};

//**************************************************************************************************
// Function Prototypes
//**************************************************************************************************
std::string remove_char(const std::string& input, const char ch=' ') {
    char buf[input.length() + 1] = {0};
    size_t buf_index = 0;
    for (auto it = input.begin(); it != input.end(); it++) {
        if (ch != *it){
            buf[buf_index++] = *it;
        }
    }

    return std::string(buf);
}

inline bool is_operator(const char ch) {
    for (auto it = operators.begin(); it != operators.end(); it++) {
        auto sub_it = std::find(it->second.begin(), it->second.end(), ch);
        if (it->second.end() != sub_it) {
            return true;
        }
    }

    return false;
}

inline int get_op_pri(const char op) {
    for (auto it = operators.begin(); it != operators.end(); it++) {
        auto sub_it = std::find(it->second.begin(), it->second.end(), op);
        if (it->second.end() != sub_it) {
            return it->first;
        }
    }

    return -1;
}

std::string expr_i2p(const std::string& input) {
    char buf[input.length() + 1] = {0};
    size_t buf_index = 0;

    std::stack<op_st> op_stack;
    int priority;
    for (auto it = input.begin(); it != input.end(); it++) {
        priority = get_op_pri(*it);
        if (0 < priority){
            logf("%c -> %d\n", *it, priority);
            while ((!op_stack.empty()) && (priority >= op_stack.top().priority)) {
                logf("%d >= %d -> %c -> %zu\n", 
                    priority, op_stack.top().priority, op_stack.top().op, buf_index
                );
                buf[buf_index++] = op_stack.top().op;
                log("\n");
                op_stack.pop();
                log("\n");
            }
            log("\n");
            op_stack.push(op_st{priority, *it});
            log("\n");
        } else {
            logf("%c -> not an operator!\n", *it);
            buf[buf_index++] = *it;
        }
        logf("Buffer: `%s` (%zu)\n", buf, buf_index);
    }
    
    while (!op_stack.empty()) {
        buf[buf_index++] = op_stack.top().op;
        op_stack.pop();
    }

    return std::string(buf);
}

int main() {
    const std::string expr("a + b * c - d / e");
    logf("Postfix: %s\n", expr_i2p(remove_char(expr)).c_str());

    return 0;
}
