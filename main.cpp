#include <iostream>
#include <vector>

// умножение для использования потом
void multiply(std::vector<int>& num, int x) {
    int carry = 0;

    for (int i = 0; i < num.size(); i++) {
        int cur = num[i] * x + carry;

        num[i] = cur % 10;
        carry = cur / 10;
    }

    // добавляем оставшиеся цифры
    while (carry > 0) {
        num.push_back(carry % 10);
        carry /= 10;
    }
}

// 1)факториал
std::vector<int> factorial(int n) {
    std::vector<int> res = {1};

    for (int i = 2; i <= n; i++) {
        multiply(res, i);
    }

    return res;
}

// 2)2^input
std::vector<int> power2(int n) {
    std::vector<int> res = {1};

    for (int i = 0; i < n; i++) {
        multiply(res, 2);
    }

    return res;
}

// 3)cложение
std::vector<int> add(std::vector<int> a, std::vector<int> b) {
    std::vector<int> res;
    int carry = 0;

    int n = std::max(a.size(), b.size());

    for (int i = 0; i < n; i++) {
        int x = (i < a.size()) ? a[i] : 0;
        int y = (i < b.size()) ? b[i] : 0;

        int sum = x + y + carry;

        res.push_back(sum % 10);
        carry = sum / 10;
    }

    if (carry) res.push_back(carry);

    return res;
}


// 4)вычитание (a > b)
std::vector<int> subtract(std::vector<int> a, std::vector<int> b) {
    std::vector<int> res;
    int borrow = 0;

    for (int i = 0; i < a.size(); i++) {
        int x = a[i] - borrow;
        int y = (i < b.size()) ? b[i] : 0;

        if (x < y) {
            x += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }

        res.push_back(x - y);
    }

    // убираем нули в конце
    while (res.size() > 1 && res.back() == 0) {
        res.pop_back();
    }
    return res;
}

// фибоначчи
std::vector<int> fib(int n) {
    std::vector<int> a = {0};
    std::vector<int> b = {1};

    if (n == 0) return a;

    for (int i = 2; i <= n; i++) {
        std::vector<int> c = add(a, b);
        a = b;
        b = c;
    }

    return b;
}

// принт
void print(std::vector<int> num) {
    for (int i = num.size() - 1; i >= 0; i--) {
        std::cout << num[i];
    }
    std::cout << std::endl;
}

int main() {

    int a, b;

    //1. факториал
    std::cout << "Enter n (>100): ";
    std::cin >> a;

    std::cout << "n! = ";
    print(factorial(a));


    //2. степень
    std::cout << "\nEnter n (>64): ";
    std::cin >> a;

    std::cout << "2^n = ";
    print(power2(a));


    //3. сумма
    std::cout << "\nEnter a and b (>64): ";
    std::cin >> a >> b;

    std::vector<int> sum = add(power2(a), power2(b));

    std::cout << "2^a + 2^b = ";
    print(sum);


    //4. разность
    std::cout << "\nEnter a and b (a > b): ";
    std::cin >> a >> b;

    std::vector<int> diff = subtract(power2(a), power2(b));

    std::cout << "2^a - 2^b = ";
    print(diff);


    //5. Фибоначчи
    std::cout << "\nEnter n (>100): ";
    std::cin >> a;

    std::cout << "Fib(n) = ";
    print(fib(a));


    return 0;
}