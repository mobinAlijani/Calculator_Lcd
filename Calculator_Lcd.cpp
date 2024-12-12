#define LCD_D7 47  //data bit 7          بیت هشتم داده
#define LCD_D6 48  //data bit 6          بیت هفتم داده
#define LCD_D5 45  //data bit 5          بیت ششم داده
#define LCD_D4 35  //data bit 4          بیت پنجم داده
#define LCD_E 21   //enable              برای اینکه نمایشگر دستور یا داده را از پایه های دیتا بخواند باید این پایه را صفر کرده و سپس یک کنیم
#define LCD_RS 20  //register select     اگر این پایه صفر باشد اطلاعات موجود بر روی پایه های دیتا به عنوان دستور در نظر گرفته می شود


// تعریف تعداد ردیف‌ها و ستون‌ها
const byte ROW_NUM = 4;     // تعداد ردیف‌ها
const byte COLUMN_NUM = 4;  // تعداد ستون‌ها

// تعریف ماتریس دکمه‌ها (صفحه‌کلید ۴x۴)
char keys[ROW_NUM][COLUMN_NUM] = {
  { '1', '2', '3', '+' },
  { '4', '5', '6', '-' },
  { '7', '8', '9', '*' },
  { 'C', '0', '=', '/' }
};

// پین‌های متصل به ردیف‌ها و ستون‌ها
byte rowPins[ROW_NUM] = { 8, 3, 46, 9 };        // پین‌های ردیف‌ها
byte colPins[COLUMN_NUM] = { 10, 11, 12, 13 };  // پین‌های ستون‌ها

class keyPad {
public:
  keyPad() {}
  keyPad(char (*keys)[4], uint8_t Row_number, uint8_t column_number, uint8_t* rowPins, uint8_t* colPins) {
    _rowPins = rowPins;
    _colPins = colPins;
    _ROW_NUM = Row_number;
    _COLUMN_NUM = column_number;

    for (int i = 0; i < _ROW_NUM; i++) {
      pinMode(_rowPins[i], INPUT_PULLDOWN);
    }
    for (int i = 0; i < _COLUMN_NUM; i++) {
      pinMode(_colPins[i], OUTPUT);
      digitalWrite(_colPins[i], LOW);
    }

    for (int x = 0; x < _ROW_NUM; x++) {
      for (int i = 0; i < _COLUMN_NUM; i++) {
        _keys[x][i] = keys[x][i];
        _keyState[x][i] = false;
        _keyLastState[x][i] = false;
        _keyLastTime[x][i] = 0;
      }
    }
  }

  char getKey() {
    for (int i = 0; i < _COLUMN_NUM; i++) {
      digitalWrite(_colPins[i], HIGH);  // فعال کردن ستون فعلی
      for (int x = 0; x < _ROW_NUM; x++) {
        bool currentState = digitalRead(_rowPins[x]);
        if (debounce(currentState, _keyState[x][i], _keyLastState[x][i], _keyLastTime[x][i])) {
          digitalWrite(_colPins[i], LOW);  // غیر فعال کردن ستون فعلی
          return _keys[x][i];              // برگرداندن کلید فشرده شده
        }
      }
      digitalWrite(_colPins[i], LOW);  // غیر فعال کردن ستون فعلی
    }
    return '\0';  // هیچ کلیدی فشرده نشده است
  }

private:
  uint8_t* _rowPins;
  uint8_t* _colPins;
  uint8_t _ROW_NUM;
  uint8_t _COLUMN_NUM;

  char _keys[4][4];
  bool _keyState[4][4];
  bool _keyLastState[4][4];
  uint64_t _keyLastTime[4][4];

  bool debounce(bool currentState, bool& keyState, bool& keyLastState, uint64_t& keyLastTime) {
    if (currentState != keyLastState) {
      keyLastTime = millis();  // بازنشانی تایمر debounce
    }

    if ((millis() - keyLastTime) > 50) {  // تأخیر debounce
      if (currentState != keyState) {
        keyState = currentState;
        keyLastState = currentState;
        return keyState;  // تغییر وضعیت کلید تایید شده
      }
    }

    keyLastState = currentState;
    return false;  // تغییر تایید نشده است
  }
};

class LiquidCrystal {
public:

  LiquidCrystal() {}
  LiquidCrystal(uint8_t rs, uint8_t enabel, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7) {

    _rs = rs;
    _enabel = enabel;
    _d4 = d4;
    _d5 = d5;
    _d6 = d6;
    _d7 = d7;
    pinMode(d7, OUTPUT);
    pinMode(d6, OUTPUT);
    pinMode(d5, OUTPUT);
    pinMode(d4, OUTPUT);
    pinMode(enabel, OUTPUT);
    pinMode(rs, OUTPUT);
    digitalWrite(enabel, 0);
    digitalWrite(rs, 0);
  }

  void begin(uint8_t line = 2, uint8_t column = 16) {
    _line = line;
    _column = column;
    sendData(0, 0X0F);  // روشن کردن نمایشگر و چشمک زن کردن مکان نما
    if (_line == 2) {
      sendData(0, 0X28);  // راه اندازی نمایشگر به صورت سریال، دو سطری با بلوک های 8*5
    } else {
      sendData(0, 0X18);
    }
  }

  void write(String data) {
    int i = 0;
    while (data[i] != '\0') {
      sendData(1, data[i]);
      i++;
    }
  }

  void clear() {
    sendData(0, 0X01);
    delay(1);
  }

  void gotoXY(int x, int y) {
    sendData(0, 0x02);                      // انتقال مکان نما به سطر و ستون صفر
    for (int i = 0; i < x * 40 + y; i++) {  // شیفت های پی در پی برای رسیدن به سطر و ستون مورد نظر
      sendData(0, 0x14);
    }
  }

  void createCustomChar(int index, byte charArray[]) {
    for (int i = 0; i < 8; i++) {
      sendData(0, 0x40 + i + (index * 8));
      sendData(1, charArray[i]);
    }
  }


  void writeCustomChar(int number) {
    sendData(1, number);
  }

private:
  uint8_t _rs;
  uint8_t _enabel;
  uint8_t _d0;
  uint8_t _d1;
  uint8_t _d2;
  uint8_t _d3;
  uint8_t _d4;
  uint8_t _d5;
  uint8_t _d6;
  uint8_t _d7;

  uint8_t _line;
  uint8_t _column;

  // با استفاده از این تابع یک پالس بر روی پایه اینیبل از نمایشگر ارسال می شود تا نمایشگر اطلاعات موجود بر روی پایه های دیتا را بخواند
  void puls() {
    digitalWrite(_enabel, 1);
    delay(1);
    digitalWrite(_enabel, 0);
  }

  void sendData(bool rs, byte data) {
    digitalWrite(_rs, rs);
    // ارسال کردن نیبل پر ارزش
    digitalWrite(_d4, data >> 4 & 0b00000001);
    digitalWrite(_d5, data >> 5 & 0b00000001);
    digitalWrite(_d6, data >> 6 & 0b00000001);
    digitalWrite(_d7, data >> 7 & 0b00000001);
    puls();

    // ارسال کردن نیبل کم ارزش
    digitalWrite(_d4, data & 0b00000001);
    digitalWrite(_d5, data >> 1 & 0b00000001);
    digitalWrite(_d6, data >> 2 & 0b00000001);
    digitalWrite(_d7, data >> 3 & 0b00000001);
    puls();
  }
};


// ایجاد کیپد

keyPad keypad(keys, ROW_NUM, COLUMN_NUM, rowPins, colPins);
LiquidCrystal lcd(LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

// تعریف متغیرهای اصلی
int num1 = 0;
int num2 = 0;
char operation = '+';
bool next = true;

// توابع
void resetCalculator() {
  num1 = 0;
  num2 = 0;
  operation = '+';
  Serial.println("ماشین‌حساب بازنشانی شد.");
  lcd.gotoXY(0, 0);
  lcd.clear();
}

void performOperation() {
  lcd.clear();
  int result = 0;
  switch (operation) {
    case '+':
      result = num1 + num2;
      break;
    case '-':
      result = num1 - num2;
      break;
    case '*':
      result = num1 * num2;
      break;
    case '/':
      if (num2 != 0) {
        result = num1 / num2;
      } else {
        Serial.println("خطا: تقسیم بر صفر");
        return;
      }
      break;
  }
  lcd.gotoXY(1,0);
  lcd.write("result ");
  lcd.write(String(result));
  Serial.printf("نتیجه: %d\n", result);
  num1 = result;    // ذخیره نتیجه برای ادامه عملیات
  num2 = 0;         // پاک کردن عدد دوم
  operation = '+';  // بازنشانی عملگر
}

void processKey(char key) {
  if (key == 'C') {
    resetCalculator();
    next = true;
    return;
  }

  if (key >= '0' && key <= '9') {
    if (next) {  // اضافه کردن به عدد اول
      num1 = num1 * 10 + (key - '0');
      Serial.printf("عدد اول: %d\n", num1);
      lcd.clear();
      lcd.gotoXY(0,0);
      lcd.write(String(num1));
    } else {  // اضافه کردن به عدد دوم
      num2 = num2 * 10 + (key - '0');
      lcd.gotoXY(1,0);
      lcd.write(String(num2));
      Serial.printf("عدد دوم: %d\n", num2);
    }
    return;
  }

  if (key == '+' || key == '-' || key == '*' || key == '/') {
    operation = key;
    next = false;
    lcd.gotoXY(0, 14);
    lcd.write(String(operation));
    Serial.printf("عملگر انتخاب شد: %c\n", operation);
    return;
  }

  if (key == '=') {
    performOperation();
    next = true;
  }
}

void setup() {
  Serial.begin(115200);
  lcd.begin();
  lcd.clear();
  lcd.write("ok to go");
  Serial.println("ماشین‌حساب آماده به کار است.");
  delay(2000);
  lcd.clear();
}

void loop() {
  char key = keypad.getKey();
  if (key) {
    processKey(key);
  }
}
