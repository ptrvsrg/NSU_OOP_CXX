# Задача 1. Большое целое число BigInt

### Общая информация
В этой задаче требуется реализовать большое целое число произвольной точности и набор операций над ним.

### Задача
1. Реализовать большое целое  с заданным интерфейсом (см. раздел “Реализация”). Выбрать способ хранения и изменения размера содержимого.
1. Вместо malloc использовать new, вместо free использовать delete. [Методы строки](https://en.cppreference.com/w/cpp/string/basic_string).
1. Тщательно задокументировать публичные члены класса на языке, приближенном к техническому английскому.
2. Написать юнит-тесты на все публичные методы класса с помощью любой специализированной библиотеки (рекомендуется [Google Test Framework](http://code.google.com/p/googletest/)), либо без оной (на усмотрение преподавателя). Убедиться в полноте покрытия кода тестами (каждая строчка кода должна исполняться хотя бы одним тестом).
   
### Реализация

<pre><code>class BigInt 
{
public:
    BigInt();
    BigInt(int);
    BigInt(std::string); // бросать исключение std::invalid_argument при ошибке
    BigInt(const BigInt&);
    ~BigInt();

    BigInt& operator=(const BigInt&);  //возможно присваивание самому себе!

    BigInt operator~() const;

    BigInt& operator++();
    const BigInt operator++(int) const;
    BigInt& operator--();
    const BigInt operator--(int) const;

    BigInt& operator+=(const BigInt&);
    BigInt& operator*=(const BigInt&);
    BigInt& operator-=(const BigInt&);
    BigInt& operator/=(const BigInt&);
    BigInt& operator^=(const BigInt&);
    BigInt& operator%=(const BigInt&);
    BigInt& operator&=(const BigInt&);
    BigInt& operator|=(const BigInt&);

    BigInt operator+() const;  // unary +
    BigInt operator-() const;  // unary -

    bool operator==(const BigInt&) const;
    bool operator!=(const BigInt&) const;
    bool operator<(const BigInt&) const;
    bool operator>(const BigInt&) const;
    bool operator<=(const BigInt&) const;
    bool operator>=(const BigInt&) const;

    operator int() const;
    operator std::string() const;

    size_t size() const;  // size in bytes
private:
};

BigInt operator+(const BigInt&, const BigInt&);
BigInt operator-(const BigInt&, const BigInt&);
BigInt operator*(const BigInt&, const BigInt&);
BigInt operator/(const BigInt&, const BigInt&);
BigInt operator^(const BigInt&, const BigInt&);
BigInt operator%(const BigInt&, const BigInt&);
BigInt operator&(const BigInt&, const BigInt&);
BigInt operator|(const BigInt&, const BigInt&);

std::ostream& operator<<(std::ostream& o, const BigInt& i);
</code></pre>

### Повышенная сложность (по желанию)

+ Реализовать семантику перемещения 
<pre><code>BigInt(BigInt&&); 
BigInt& operator=(BigInt&&);
</code></pre>
+ Реализовать оператор ввода из потока с корректной обработкой ошибок 
<pre><code>std::istream& operator>>(std::istream& o, BigInt& i);
</code></pre>
