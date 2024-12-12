# ماشین‌حساب ۴x۴ با استفاده از کیپد و LCD

این پروژه یک ماشین‌حساب ساده است که با استفاده از میکروکنترلر ESP32 و صفحه‌نمایش LCD 4x4 ساخته شده است. کاربر می‌تواند از طریق یک صفحه‌کلید ۴x۴ ورودی‌ها را وارد کرده و عملیات‌های ریاضی را انجام دهد.

## اجزای پروژه:
- **میکروکنترلر ESP32**
- **صفحه‌نمایش LCD 4x4**
- **صفحه‌کلید ۴x۴ (Keypad)**
- **کتابخانه‌های استفاده شده:**
  - `LiquidCrystal` برای کنترل LCD
  - `Keypad` برای مدیریت ورودی کیپد

## اتصال سخت‌افزار:
### صفحه‌کلید ۴x۴:
- ردیف‌ها: پین‌های ۸، ۳، ۴۶، ۹
- ستون‌ها: پین‌های ۱۰، ۱۱، ۱۲، ۱۳

### صفحه‌نمایش LCD:
- RS: پین ۲۰
- EN: پین ۲۱
- D4: پین ۳۵
- D5: پین ۴۵
- D6: پین ۴۸
- D7: پین ۴۷

## نحوه استفاده:
1. پس از روشن کردن دستگاه، صفحه‌کلید ۴x۴ نمایش داده می‌شود.
2. ورودی‌ها (اعداد و عملیات‌های ریاضی) از طریق کیپد وارد می‌شود.
3. نتیجه عملیات بر روی LCD نمایش داده می‌شود.
4. برای ریست کردن ماشین‌حساب، کلید `C` را فشار دهید.

## توابع اصلی:
- `resetCalculator()`: ریست کردن ماشین‌حساب و پاک کردن تمام ورودی‌ها و نتایج.
- `performOperation()`: انجام عملیات‌های ریاضی (+، -، *، /).
- `processKey()`: پردازش کلید فشرده‌شده از صفحه‌کلید و انجام عملیات‌های مربوطه.

## نصب کتابخانه‌ها:
برای استفاده از این پروژه در Arduino IDE، نیاز به نصب کتابخانه‌های زیر دارید:
- **Keypad**: برای مدیریت ورودی صفحه‌کلید ۴x۴.
- **LiquidCrystal**: برای مدیریت صفحه‌نمایش LCD.

## آموزش نصب:
1. کتابخانه‌ها را از طریق Arduino IDE نصب کنید.
2. کد را بر روی میکروکنترلر ESP32 خود بارگذاری کنید.
3. اتصالات سخت‌افزاری را طبق توضیحات بالا انجام دهید.

## نتایج:
- نمایش عددهای وارد شده و عملیات در حال انجام بر روی صفحه‌نمایش.
- نمایش نتیجه عملیات پس از فشردن کلید `=`.

## نکات:
- پس از انجام هر عملیات، نتیجه بر روی LCD نمایش داده می‌شود.
- پس از انجام عملیات، عدد اول ذخیره می‌شود و می‌توانید عملیات جدید را انجام دهید.

## مجوز:
این پروژه تحت مجوز MIT منتشر شده است.
