
## Расчет 3D кривых, с использованием ООП (CurvesGeometry)

### Описание

Решение, предназначено для демонстрации использования методов ***ООП***,
***умных указателей***, ***отдельных алгоритмов*** и ***структуры проекта***.
И, в соответствии с заданием, реализует, на основе классов, 
создание трех видов кривых: **круг**, **эллипс** и **3D спираль** 
и расчет их координат.
#### Кривые задаются параметрами:
- **Круг**: радиусом;
- **Эллипс**: радиусами по осям **X** и **Y**;
- **3D спираль**: радиусом и шагом смещения по оси **Z** за оборот на угол **2π**.

#### С использованием реализованных классов:
- Создается набор кривых со случайно выбранными формой и параметрами;
- Выводится описание созданных кривых и расчет их координат при угле **π/4 (45°)**;
- В отдельный набор отбираются (без дублирования) сформированные кривые 
  вида **Круг**, с сортировкой в порядке возрастания радиуса;
- Рассчитывается сумма радиусов всех кривых вида **Круг**.

### Установка 

Загрузите содежимое репозитория в удобный каталог и выполните сборку 
и запуск решения в привычной среде разработки или в консоли, 
после формирования исполняемого файла: `CurvesGeometry.exe`.

При разработке использовался компилятор **MinGW** в среде разработки
**[CLion](https://www.jetbrains.com/clion/)** от
**[JBrain](https://www.jetbrains.com/)**

---
<h6 align="right">solution by Perseus<h6>