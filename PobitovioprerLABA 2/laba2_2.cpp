#include <iostream>
#include <string>
#include <bitset>
#include <iomanip>
#include <windows.h>
using namespace std;

// структура з бітовими полями (разом рівно 16 біт)
struct CharBits {
    unsigned short pos : 6;   // номер позиції символа
    unsigned short high : 4;  // старша половина символа
    unsigned short p1 : 1;    // біт парності для позиції і старшої половини
    unsigned short low : 4;   // молодша половина символа
    unsigned short p2 : 1;    // біт парності для молодшої половини
};

// перевірка під час компіляції що структура займає рівно 2 байти
static_assert(sizeof(CharBits) == 2, "CharBits має займати 2 байти");

// union дає різні способи подивитись на ті самі 2 байти
union Code {
    CharBits bits;            // доступ до окремих полів
    unsigned short value;     // усі біти як одне число
    unsigned char bytes[2];   // доступ до кожного байта окремо
};

// рахує біт парності числа (1 якщо одиниць непарна кількість)
unsigned int parityBit(unsigned int x) {
    unsigned int p = 0;
    while (x) {
        p ^= (x & 1);   // додаємо молодший біт через XOR
        x >>= 1;        // переходимо до наступного біта
    }
    return p;
}

// перетворює один символ у код з позицією і бітами парності
Code encryptChar(unsigned char ch, unsigned int position) {
    Code c;
    c.value = 0;                     // спочатку обнуляємо всі біти
    c.bits.pos = position;           // записуємо позицію символа
    c.bits.high = ch >> 4;           // старша половина символа
    c.bits.low = ch & 0x0F;          // молодша половина символа

    c.bits.p1 = parityBit(c.bits.pos) ^ parityBit(c.bits.high); // парність позиції і старшої половини
    c.bits.p2 = parityBit(c.bits.low);                          // парність молодшої половини

    return c;
}

int main() {
    SetConsoleCP(1251);              // кодування консолі для введення
    SetConsoleOutputCP(1251);        // кодування консолі для виведення
    cout << "Введіть текст (до 64 символів): ";
    string text;
    cin >> text;                     // читаємо текст

    // обрізаємо текст до 64 символів
    if (text.size() > 64); text.resize(64);
    // доповнюємо пробілами до 64 символів
    if (text.size() < 64); text.resize(64, ' ');

    Code enc[64];                    // масив для зашифрованих кодів

    for (int i = 0; i < 64; i++) {
        enc[i] = encryptChar((unsigned char)text[i], i);   // шифруємо кожен символ

        // виводимо позицію символ і його двійковий код
        cout << i << " = " << text[i] << " = " << bitset<16>(enc[i].value) << "\n";
    }
}