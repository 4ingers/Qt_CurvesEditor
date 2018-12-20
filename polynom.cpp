#include "polynom.h"

// Конструкторы
Polynom::Polynom(QMap<QString, double>& initmap)
{
    this->mapPolynom = initmap;
}

Polynom::Polynom(const Polynom& other)
{
    this->mapPolynom = other.mapPolynom;
}


// Проверка на пустоту
bool Polynom::isEmpty() const
{
    return this->mapPolynom.isEmpty();
}

// Представление упрощённого полинома в виде строки
QString Polynom::simpleOutput() const {
    QStringList monomList;
    if (this->mapPolynom.contains("x2"))
        monomList.append(QString::number(this->mapPolynom["x2"]) + "x2");
    if (this->mapPolynom.contains("y2"))
        monomList.append(QString::number(this->mapPolynom["y2"]) + "y2");
    if (this->mapPolynom.contains("xy"))
        monomList.append(QString::number(this->mapPolynom["xy"]) + "xy");
    if (this->mapPolynom.contains("x"))
        monomList.append(QString::number(this->mapPolynom["x"]) + "x");
    if (this->mapPolynom.contains("y"))
        monomList.append(QString::number(this->mapPolynom["y"]) + "y");
    if (this->mapPolynom.contains(""))
        monomList.append(QString::number(this->mapPolynom[""]) + "");
    QString result = monomList.join('+') + QString("=0");
    result.replace("+-", "-");
    return result;
}

// Вставка монома
void Polynom::addMonom(const double& coef,
                        const QString& var)
{
    // Если моном есть -- коэффициенты складываются
    if (this->mapPolynom.contains(var))
        this->mapPolynom[var] = this->mapPolynom[var] + coef;

    // Иначе создаётся элемент
    else
        this->mapPolynom[var] = coef;

    // Если коэффициент стал равен нулю - элемент удаляется
    if (qFuzzyIsNull(this->mapPolynom[var] ) )
        this->mapPolynom.remove(var);
}

// Очистка полинома
void Polynom::reset() {
    this->mapPolynom.clear();
}

// Проверка корректности строки
void Polynom::parser(QString& err,
                     const QString& input,
                     QStringList* output)
{
    // Проверка на пустоту
    if (input.isNull()) {
        err = "Null string";
        return;
    }

    // Создаётся промежуточная строка
    QString transit(input);

    // Удаляются все space-подобные символы
    transit.simplified();
    transit.remove(' ');

    // Один символ '='
    if (transit.count('=') != 1) {
        err = "The only equal sign is possible";
        return;
    }

    // Проверка левой части на пустоту
    if (transit.split('=', QString::SkipEmptyParts).size() != 2) {
        err = "Half forgotten";
        return;
    }

    // Отсутствие лишних символов
    QSet<QChar> besidesNum;
    besidesNum << '+' << '-' << '/' << '=' << 'x' << 'y';
    for (QChar ch : transit)
        if ( !(QChar::Number_DecimalDigit == ch.category() ||
               besidesNum.contains(ch) ) ) {
            err = QString("Invalid char : %1").arg(ch);
            return;
        }

    // Добавляется пробел перед всеми слагаемыми,
    // чтобы разбить полином на мономы
    transit.replace('-', " -");
    transit.replace('+', " +");

    // Понижение регистра
    transit.toLower();

    // Разбиение строки через '='
    QStringList equalSplit = transit.split('=');

    // Стереть пробел в начале полиномов, если он есть
    for (QString& strPolynom : equalSplit)
        if (' ' == strPolynom.front())
            strPolynom.remove(0, 1);

    // Сборка мономов
    // Разбиение обеих частей по пробелу
    QStringList rawPolynom = equalSplit[0].split(' ');
    QStringList rhsRawPolynom = equalSplit[1].split(' ');

    // Смена знака
    for (QString& monom : rhsRawPolynom) {
        monom.trimmed();
        QChar ch = monom.front();
        if ('-' == ch || '+' == ch)
            monom.remove(0, 1);
        if ('-' != ch )
            monom.prepend('-');
    }
    // Собрать правый и левый полиномы в StringList
    rawPolynom = rawPolynom + rhsRawPolynom;

    // Если требуется вернуть собранные полиномы -- возврат
    if (nullptr != output)
        *output = rawPolynom;
}

// Упрощение полинома
void Polynom::simplifier(bool& ok,
                          QStringList& strListPolynom,
                          Polynom* result)
{
    // Помономная обработка
    for (QString& monom : strListPolynom) {

        // Стереть пробелы по краям
        monom.trimmed();

        // Пустота монома
        if (monom.isEmpty() ) {
            ok = false;
            return;
        }

        // Разбиение по '/'
        QStringList divided = monom.split('/');

        // Размер разбиения равен либо 1, либо 2, и пустоты нигде нет
        if (divided.size() < 1 || divided.size() > 2 || divided.contains("")) {
            ok = false;
            return;
        }

        // Выделение делителя
        int divider = 1;
        if (2 == divided.size() ) {
            divider *= divided[1].toInt(&ok);
            if (!ok)
                return;
        }

        // Делимое
        QString divident = divided[0];

        // "yx" -> "xy"
        divident.replace("yx", "xy");

        // Проверка количества 'x' и 'y'
        if (divident.count('x') > 1 || divident.count('y') > 1) {
            ok = false;
            return;
        }

        // Пустота делимого
        if (divident.isEmpty() ) {
            ok = false;
            return;
        }

        // Коэффициент
        int coef = 1;

        // Стирается знак делимого
        if ('+' ==  divident.front())
            divident.remove('+');
        else if ('-' == divident.front()) {
            divident.remove('-');
            coef *= -1;
        }

        // Переменная
        QString var = "";

        // Случай, когда переменных нет
        if (!divident.contains('x') && !divident.contains('y'))
        {
            // Попытка достать коэффициент
            coef *= divident.toInt(&ok);
            if (!ok)
                return;
        }
        // Случай, когда есть переменные
        else {
            // Есть и 'x', и 'y', но они не вместе и не в конце -- ошибка
            if (divident.contains('x') && divident.contains('y')
                    && !divident.endsWith("xy")) {
                ok = false;
                return;
            }
            // Строка должна оканчиваться переменной
            else if (!divident.endsWith('x') && !divident.endsWith('y') &&
                     !divident.endsWith("x2") && !divident.endsWith("y2") ) {
                ok = false;
                return;
            }
            // Индекс, с которого начинается переменная
            int startVar = 0;
            if (divident.contains('y') )
                startVar = divident.indexOf('y');
            if (divident.contains('x') )
                startVar = divident.indexOf('x');

            // Разбить строку на переменную...
            divident.insert(startVar, ' ');
            var = divident.split(' ')[1];

            // ...и коэффициент (конвертирование)
            QString rawCoef = divident.split(' ')[0];
            if (!rawCoef.isEmpty() ) {
                rawCoef.toInt(&ok);
                if (!ok)
                    return;
                coef *= rawCoef.toInt();
            }
        }
        // Получение частного (коэффициент)
        double coefficient = double(coef) / double(divider);

        // Если требуется вернуть полином -- вставка монома в результат
        if (nullptr != result)
            result->addMonom(coefficient, var);
    }
    ok = true;
    return;
}

// Если в полиноме хранится только константа -- это неверное равенство
bool Polynom::isNotEqual() const {
    return this->mapPolynom.contains("") && 1 == this->mapPolynom.size();
}

// Дискриминант
double Polynom::discriminant(const QString& var) const {
    // Литера квадрата, смежная с поданной литерой
    QString var2 = var + QString('2');

    // Если ключ есть -- извлекается коэффициент, иначе кладётся 0
    double a = this->mapPolynom.contains(var2) ? this->mapPolynom[var2] : 0;
    double b = this->mapPolynom.contains(var) ? this->mapPolynom[var] : 0;
    double c = this->mapPolynom.contains("") ? this->mapPolynom[""] : 0;

    return (b * b) - (4 * a * c);
}

// Разрешение уравнения относительно одной из переменных
QVector<double> Polynom::findRoots(const QString var,
                                    bool& ok) const {
    QVector<double> result;

    // Литера квадрата, смежная с поданной литерой
    QString var2 = var + QString('2');

    // Если ключ есть -- извлекается коэффициент, иначе кладётся 0
    double a = this->mapPolynom.contains(var2) ? this->mapPolynom[var2] : 0.0;
    double b = this->mapPolynom.contains(var) ? this->mapPolynom[var] : 0.0;
    double c = this->mapPolynom.contains("") ? this->mapPolynom[""] : 0.0;

    // Если квадрата нет: -b/2a
    if (!this->mapPolynom.contains(var2) )
        result.push_back((c * -1) / b);

    // Иначе (-b+-sqrt(D))/2a
    else {
        double D = this->discriminant(var);
        if (D < 0) {
            ok = false;
            return result;
        }
        else {
            result.push_back(((b * -1) - qSqrt(D) ) / (a * 2) );
            result.push_back(((b * -1) + qSqrt(D) ) / (a * 2) );
        }
    }
    ok = true;
    return result;
}

// Получение полинома одной переменной в заданной точке
Polynom Polynom::atPoint(const double& p,
                          const QString& inVar) const {
    // Определение переменной и замены
    QString var, var2, sub, sub2;
    if ("x" == inVar) {
        var = "x";
        var2 = "x2";
        sub = "y";
        sub2 = "y2";
    }
    else {
        var = "y";
        var2 = "y2";
        sub = "x";
        sub2 = "x2";
    }

    Polynom result;

    // Вместо переменной применяется подстановочное число
    // и формируется полином одной переменной
    if (this->mapPolynom.empty() )
        return result;

    if (this->mapPolynom.contains("") )
        result.addMonom(this->mapPolynom[""], "");

    if (this->mapPolynom.contains(var) )
        result.addMonom(this->mapPolynom[var], var);

    if (this->mapPolynom.contains(var2) )
        result.addMonom(this->mapPolynom[var2], var2);

    if (this->mapPolynom.contains(sub) )
        result.addMonom(this->mapPolynom[sub] * p, "");

    if (this->mapPolynom.contains(sub2) )
        result.addMonom(this->mapPolynom[sub2] * qPow(p, 2), "");

    if (this->mapPolynom.contains("xy") )
        result.addMonom(this->mapPolynom["xy"] * p, var);

    return result;
}

// Нахождение значений в заданной точке в зависимости от переменной
QVector<double> Polynom::solveForVar(const double& p,
                                      QString var,
                                      bool& ok) const {
    // Формирование полинома одной переменной
    Polynom polynomAtP = this->atPoint(p, var);

    // Нахождение корней этого полинома
    QVector<double> roots = polynomAtP.findRoots(var, ok);
    return roots;
}

// Инварианты
QVector<double> Polynom::invariants() const
{
    // Извлечение всех коэффициентов
    double  a11 = this->mapPolynom.contains("x2") ? this->mapPolynom["x2"] : 0.0,
            a22 = this->mapPolynom.contains("y2") ? this->mapPolynom["y2"] : 0.0,
            a12 = this->mapPolynom.contains("xy") ? this->mapPolynom["xy"]/ 2.0 : 0.0,
            a13 = this->mapPolynom.contains("x")  ? this->mapPolynom["x"] / 2.0 : 0.0,
            a23 = this->mapPolynom.contains("y")  ? this->mapPolynom["y"] / 2.0 : 0.0,
            a33 = this->mapPolynom.contains("")   ? this->mapPolynom[""] : 0.0;

    // Матрица для поиска D-инварианты
    QTransform matrixDelta(a11, a12, a13,
                           a12, a22, a23,
                           a13, a23, a33);

    // Оставшиеся инварианты
    double delta = double(matrixDelta.determinant() ),
           D = (a11 * a22) - double(qPow(a12, 2) ),
           I = a11 + a22,
           B = ((a11 * a33) - double(qPow(a13, 2) ) ) +
               ((a22 * a33) - double(qPow(a23, 2) ) );

    QVector<double> result = { delta, D, I, B };
    return result;
}

// Определение типа кривой
int Polynom::type() const
{
    // Извлечение инвариант
    QVector<double> invariants = this->invariants();
    double delta = invariants[0],
           D     = invariants[1],
           I     = invariants[2],
           B     = invariants[3];

    // Типы кривых
    enum CurveType {
        Ellipse,
        Circle,
        ImEllipse,
        Hyperbola,
        Parabola,

        DeEllipse,
        DeHyperbola,
        DeParabolaLines,
        DeParabolaLine,
        DeParabolaNo
    };

    // Поиск соответствия
    if (qFuzzyIsNull(delta) ) {
        if (qFuzzyIsNull(D) ) {
            if (qFuzzyIsNull(B) )
                return DeParabolaLine;
            else if (B < 0)
                return DeParabolaLines;
            else if (B > 0)
                return DeParabolaNo;
        }
        if (D > 0)
            return DeEllipse;
        else if (D < 0)
            return DeHyperbola;
    }
    else {
        if (qFuzzyIsNull(D) )
            return Parabola;
        else if (D > 0 && delta * I < 0) {
            if (qFuzzyCompare(I * I, 4 * D))
                return Circle;
            return Ellipse;
        }
        else if (D > 0 && delta * I > 0)
            return ImEllipse;
        else if (D < 0)
            return Hyperbola;
    }

    return -1;
}
