#pragma once

#include <QMap>
#include <iterator>
#include <QtGlobal>
#include <QtMath>
#include <QTransform>
#include <QVector>
#include <QPointF>
#include <QDebug>

class Polynom {
public:
    Polynom() = default;
    Polynom(QMap<QString, double>&);
    Polynom(const Polynom&);

    void reset();

    static void parser(QString& err,
                       const QString& input,
                       QStringList* output = nullptr);

    static void simplifier(bool& ok,
                            QStringList&,
                            Polynom* output = nullptr);

    bool isEmpty() const;

    bool isNotEqual() const;

    QVector<double> solveForVar(const double& c, QString var, bool& ok) const;

    QVector<double> invariants() const;

    int type() const;


private:
    void addMonom(const double&, const QString&);

    double discriminant(const QString& var) const;

    Polynom atPoint(const double& x, const QString& var) const;

    QVector<double> findRoots(const QString var, bool& ok) const;


    // ===== Хэш: ключ-степень, значение-коэффициент =====
    QMap<QString, double> mapPolynom;
};
