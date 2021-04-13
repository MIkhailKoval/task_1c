Тестовое задание для отбора на кафедру 1С
=========================================

# Формат входных данных:

* количество предметов
 * название предмета, его уровень(предметы вводить в порядке приоритета)
 * количество обязательных предметов для этого предмета
 (затем выводим предметы: если нужно закрыть один из множества, 
 то вводим количество элементов в этом множестве, затем названия предметов и из уровень)

 Sample:
 5
 development 3 
    1 
      java 2
 java 2
    3 
      2 
      python 1
      chemistry 1
      1 
        arhitecture 1
 chemistry 1 
  0
 python 1 
  0
 arhitecture 1 
  0
# Описание сущностей и интерфейса

# Описание алгоритма
Перебираем все возможные курсы за 2 в степение количесва курсов. После этого проверяем, что все зависимости сохранены,
то есть, что мы взяли те три курса третьего уровня и один курс пятого, а также, что все зависимые от них тоже взяты.

После этого необходимо проверить условие на то, что в каждом семестре выбрано хотя бы 3 курса.
Эта проверка реализована в функции ```TryToPlaceInTymetable``` следующим образом:
1) Для каждого курса подсчитана величина ```hight``` - это минимальный семестр, в который можно взять текущий курс
(высчитывается как максмальная длинна цепочки зависимости)
2) Изначально все курсы берутся в тот семестр, номер которого равен значению ```hight``` + 1.
3) Если теперь в каждом семестре и так взято не меньше 3х курсов, то больше делать ничего не надо.
4) Иначе выбираем семестр с максимальным номером в котором взято меньше 3х курсов. Пусть это семестр с номером k.
Рассматриваем все семестры с номерами  k-1, k-2, ..., 0. Если в текущем семестре есть курс, который можно перенести в 
семестр с номером k (то есть нет зависимостей от курсов, расположенных в более высоких семестрах - это проверка реализована в функции ```GetUpVertex()```, котрая возвращает минимальный номер семестра среди всех курсов, зависимых от данного), то переносим его в k-ый семестр. Если ни один курс не может быть передвинут на k-ый семестр, то данный набор курсов невозможно разместить на все семь семестров. В таком случае прерываемся и продолжаем перебор за два в степени кол-ва курсов.
5) Переходим на шаг 3.
6) Из всех корретных наборов курсов, выбирается набор с максимальной суммой приорететов. Это и будет ответом.
####  Асимптотика
Перебор работает за O(2^n). 
Первая проверка на то, что все зависимые курсы находятя в наборе, реализуется dfs'ом  и работает за O(n + m), где n - 
кол-во курсов и m - кол-во зависимостей.
Идейная часть алгоритма - функция ```TryToPlaceInTymetable``` работает за O(n).
 Конечная асимптотика - O(nlogn)
#### Корректность алгоритма

1) Никогда не получится так, что мы передвинули какой-то курс, и нам не хватит времени взять все, от которых он зависит.
Заметим, что с самого начала мы взяли курсы так, чтобы времени хватило на все, от которых он зависит (за это отвечала переменнай ```hight``` и начальное расположение по семестрам). На каждом шаге мы только увеличиваем номер семестра, в котором берем курс, поэтому на все зависимые курсы времени становится только больше.
2) Все зависимости остались выполнены.
Не получится так, что какой-то курс взят раньше, чем зависимый от него, потому что с самого начала все зависимости удовлетворены. Когда переносим курс на другой семестр, делаем проверку того, что номер нового семестра не превосходит величины ```GetUpVertex()```, что сохраняет инвариант корректности зависимостей.
