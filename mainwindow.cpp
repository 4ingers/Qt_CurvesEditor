#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow) {

    this->ui->setupUi(this);

    // Фиксация размеров окна и запрет полноэкранного режима
    this->setFixedSize(960, 720);
    this->setWindowFlags(Qt::WindowMinimizeButtonHint |
                         Qt::WindowCloseButtonHint);

    // Установка операций над customPlot
    this->ui->customPlot->setInteractions(QCP::iRangeDrag |
                                    QCP::iRangeZoom |
                                    QCP::iSelectPlottables);

    // Дополнительные оси без цены деления
    this->ui->customPlot->xAxis2->setVisible(true);
    this->ui->customPlot->xAxis2->setTickLabels(false);
    this->ui->customPlot->yAxis2->setVisible(true);
    this->ui->customPlot->yAxis2->setTickLabels(false);

    // Равные цены деления по X и Y
    this->ui->customPlot->yAxis->setTickStep(
                this->ui->customPlot->xAxis->tickStep());

    // Добавление полотна, отключение соединения точек и выбор их стиля
    this->ui->customPlot->addGraph();
    this->ui->customPlot->graph(0)->setLineStyle((QCPGraph::lsNone));
    this->ui->customPlot->graph(0)->setPen(QPen(Qt::darkCyan));
    this->ui->customPlot->graph(0)->setScatterStyle(QCPScatterStyle(
                                                  QCPScatterStyle::ssDisc, 3));
    // Загрузка файла
    this->loadBasicFile("data.xml");

    // Основная ось <-> дополнительная ось
    this->connect(this->ui->customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)),
                  this->ui->customPlot->xAxis2, SLOT(setRange(QCPRange)));
    this->connect(this->ui->customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)),
                  this->ui->customPlot->yAxis2, SLOT(setRange(QCPRange)));

    // Масштабирование и перемещение
    this->connect(this->ui->customPlot, SIGNAL(mouseWheel(QWheelEvent*)),
                  this, SLOT(mouseWheelEvent()));
    this->connect(this->ui->customPlot, SIGNAL(mouseMove(QMouseEvent*)),
                  this, SLOT(mouseMoveEvent(QMouseEvent*)));

    // Контекстное меню treeWgt
    this->connect(this->ui->treeWgt, SIGNAL(customContextMenuRequested(QPoint)),
                  this, SLOT(on_treeWgt_customContextMenuRequested()),
                  Qt::UniqueConnection);
}

MainWindow::~MainWindow() {
    delete this->ui;
}

// Перерисовка кривой при сдвиге курсора с зажатой ЛКМ
void MainWindow::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton)
        this->painter();
}

// Перерисовка при масштабировании
void MainWindow::mouseWheelEvent() {
    this->painter();
}

// Нажатие ENTER при фокусе equationEdit
void MainWindow::on_equationEdit_returnPressed() {

    // Очистка полинома
    polynom.reset();

    // Если строка пустая -- очистка полотна
    if (this->ui->equationEdit->text().isEmpty()) {
        this->ui->customPlot->graph(0)->clearData();
        this->ui->customPlot->replot();
        return;
    }

    // Попытка конверирования строки
    // Если неудачно -- очистка полотна и вывод ошибки
    QString error;
    this->convertPolynom(error);
    if (!error.isEmpty()) {
        this->ui->customPlot->graph(0)->clearData();
        this->ui->customPlot->replot();
        this->ui->labelCurve->setText(QString("ERROR\n") + error);
        return;
    }
    // Иначе отображение кривой
    this->showCurve();
}

// Отображение графика и информации
void MainWindow::showCurve() {

    // Отображение кривой и её типа
    this->painter();
    this->setCurveType(polynom.type());

    // Вычисление и отображение инвариант
    QVector<double> invariants(polynom.invariants());
    setInvariant(invariants[0], invariants[1], invariants[2], invariants[3]);
}

// Конвертирование полинома
void MainWindow::convertPolynom(QString& error) {

    // Набор мономов
    QStringList monomList;

    // Получение и проверка строки из equationEdit
    Polynom::parser(error, this->ui->equationEdit->text(), &monomList);
    if (!error.isEmpty()) {
        return;
    }

    // Проверка и упрощение мономов
    bool ok = true;
    Polynom::simplifier(ok, monomList, &polynom);

    // Найден некорректный моном
    if (!ok) {
        error = "Invalid monom";
        return;
    }
    // Упрощённый полином пуст
    if (polynom.isEmpty() ) {
        error = "Simplified polynom is empty";
        return;
    }

    // Равенство не соблюдено
    if (polynom.isNotEqual()) {
        error = "Isn't equal";
        return;
    }
}

// Установка инвариант в Label
void MainWindow::setInvariant(double delta, double D, double I, double B) {
    QString line;
    line = QString("\u0394\n\n") + QString::number(delta);
    this->ui->labelDelta->setText(line);
    line = QString("D\n\n") + QString::number(D);
    this->ui->labelD->setText(line);
    line = QString("I\n\n") + QString::number(I);
    this->ui->labelI->setText(line);
    line = QString("B\n\n") + QString::number(B);
    this->ui->labelB->setText(line);
}

// Установка типа кривой в Label
void MainWindow::setCurveType(int type) {

    QString line;

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

    // В зависимости от типа установка строки
    switch (type) {
        case Ellipse :
            line = "Ellipse"; break;
        case Circle :
            line = "Circle"; break;
        case ImEllipse :
            line = "Imaginary ellipse (not real roots)"; break;
        case Hyperbola :
            line = "Hyperbola"; break;
        case Parabola :
            line = "Parabola"; break;
        case DeEllipse :
            line = "Degenerative ellipse (one real root)"; break;
        case DeHyperbola :
            line = "Degenerative hyperbola (intersected lines)"; break;
        case DeParabolaLines :
            line = "Degenerative parabola (parallel lines)"; break;
        case DeParabolaLine :
            line = "Degenerative parabola (matching lines)"; break;
        case DeParabolaNo :
            line = "Degenerative parabola (no real roots)"; break;
        default:
            line = "Can't determine"; break;
    }
    this->ui->labelCurve->setText(line);
}

// Отображение кривой
void MainWindow::painter() {

    // Полином пуст
    if (polynom.isEmpty())
        return;

    QVector<double> X, Y;

    // Диапазон; начальные и конечные точки, концентрация точек
    double rangeX = this->ui->customPlot->xAxis->range().size();
    double x1 = double(this->ui->customPlot->xAxis->range().lower - rangeX);
    double x2 = double(this->ui->customPlot->xAxis->range().upper + rangeX);
    double spanX = rangeX / 250;

    double rangeY = this->ui->customPlot->yAxis->range().size();
    double y1 = double(this->ui->customPlot->yAxis->range().lower - rangeY);
    double y2 = double(this->ui->customPlot->yAxis->range().upper + rangeY);
    double spanY = rangeY / 250;

    // Проход по точкам с заполнением векторов значений У
    for (double x = x1; x < x2; x += spanX)
    {
        // Разрешение уравнения относительно Y в точке X
        bool ok = true;
        QVector<double> rootsY = polynom.solveForVar(x, "y", ok);
        if (ok)
            for (double y : rootsY) {
                X.push_back(x);
                Y.push_back(y);
            }
    }
    // Аналогично для X
    for (double y = y1; y < y2; y += spanY) {
        bool ok = true;
        QVector<double> rootsX = polynom.solveForVar(y, "x", ok);
        if (ok)
            for (double x : rootsX) {
                X.push_back(x);
                Y.push_back(y);
            }
    }
    // Установка векторов и перерисовка
    this->ui->customPlot->graph(0)->setData(X, Y);
    this->ui->customPlot->replot();
}

// Действие Open
void MainWindow::on_actionOpen_triggered() {
    loadBasicFile("data.xml");
}

// Подгрузка данных из .xml файла
void MainWindow::loadBasicFile(const QString& fileName) {

    // Очистка дерева
    this->ui->treeWgt->clear();

    // Открытие файла с проверкой
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    // Установка потока на файл
    QXmlStreamReader xml(&file);

    // Указатель на Item
    QTreeWidgetItem* topLevelItem = nullptr;

    // Если есть открывающий тэг
    if (xml.readNextStartElement() && "nodes" == xml.name()) {

        // Пока не достигнут конец документа и не встречена ошибка формата
        while (xml.readNext() != QXmlStreamReader::EndDocument &&
               !xml.hasError()) {

            // Если тэг == <eq>, то добавляемый узел -- уравнение
            if ("eq" == xml.name() &&
                    xml.tokenType() == QXmlStreamReader::StartElement) {

                // Привязка узла к родителю, который был добавлен последним
                // (с проверкой корректности уравнения)
                QTreeWidgetItem *item = new QTreeWidgetItem(topLevelItem);
                QString line = xml.readElementText().trimmed(),
                        err;
                QStringList polynom;
                Polynom::parser(err, line, &polynom);
                if (!err.isEmpty()) {
                    xml.raiseError(err + QString("\n") + line);
                    break;
                }
                bool ok = true;
                Polynom::simplifier(ok, polynom);
                if (!ok) {
                    xml.raiseError(QString("Invalid monom\n" + line));
                    break;
                }
                line.replace("x2", QString('x') + QString(QChar(0262)));
                line.replace("y2", QString('y') + QString(QChar(0262)));
                line.replace(" ", "");
                item->setText(0, line);
            }
            // Иначе если тэг открывающий, то добавляемый узел -- папка
            else if (xml.tokenType() == QXmlStreamReader::StartElement) {
                topLevelItem =
                        new QTreeWidgetItem(this->ui->treeWgt);
                topLevelItem->
                        setText(0, xml.attributes().value("id").toString());
                this->ui->treeWgt->
                        addTopLevelItem(topLevelItem);
            }
        }
    }
    else
        xml.raiseError("Incorrect file");

    // Если была встречена ошибка -- вывод соответствующего окна
    if (xml.hasError()) {
        this->ui->treeWgt->clear();
        QMessageBox::critical(this, "Error reading XML", xml.errorString());
    }
    xml.clear();
    file.close();
}

void MainWindow::on_treeWgt_itemClicked(QTreeWidgetItem *item, int column) {
    this->ui->treeWgt->clearSelection();
    if (!item->parent()) {
        return;
    }
    QString line = item->text(column);
    line.replace(QString('x') + QString(QChar(0262)), "x2");
    line.replace(QString('y') + QString(QChar(0262)), "y2");
    this->ui->equationEdit->setText(line);
    polynom.reset();
    QString error;
    convertPolynom(error);
    if (!error.isEmpty()) {
        this->ui->customPlot->graph(0)->clearData();
        this->ui->customPlot->replot();
        this->ui->labelCurve->setText(QString("ERROR\n") + error);
    }
    else
        this->showCurve();
}

// Контекстное меню в дереве
void MainWindow::on_treeWgt_customContextMenuRequested()
{
    // Объект окна
    QMenu menu;

    // Если в момент клика не выделился элемент или у выделенного нет родителя,
    // добавляется действие вставки: в первом случае для создания папки,
    // во втором - для создания узла с уравнением
    if (!this->ui->treeWgt->selectedItems().size() ||
        !this->ui->treeWgt->selectedItems().first()->parent())
    {
        QAction* add = new QAction("Add", this);
        connect(add, SIGNAL(triggered()),
             this, SLOT(addItemInTree()),
             Qt::UniqueConnection);
        menu.addAction(add);
    }
    // Если при клике выделился элемент -- добавляется действие удаления
    if (this->ui->treeWgt->selectedItems().size()) {
        QAction* rm = new QAction("Remove", this);
        connect(rm, SIGNAL(triggered()),
             this, SLOT(delItemInTree()),
             Qt::UniqueConnection);
        menu.addAction(rm);
    }
    // Запуск контекстного меню в позиции курсора
    menu.exec(QCursor::pos());

    // Сброс выделения ради исключения неоднозначных ситуаций
    this->ui->treeWgt->clearSelection();
}

// Удаление элемента из дерева
void MainWindow::delItemInTree()
{
    // Вызов деструктора для выделенного элемента
    QTreeWidgetItem* item = this->ui->treeWgt->selectedItems().first();
    item->~QTreeWidgetItem();
}

// Вставка узла в дерево
void MainWindow::addItemInTree()
{
    // Если при клике не выделился элемен, создаётся папка с именем,
    // взятом из equationEdit
    if (!this->ui->treeWgt->selectedItems().size())
    {
        // Папку без названия создать нельзя
        if (this->ui->equationEdit->text().isEmpty())
            return;
        QTreeWidgetItem* topLevelItem = new QTreeWidgetItem(this->ui->treeWgt);
        QString folderName = this->ui->equationEdit->text().trimmed();
        topLevelItem->setText(0, folderName);
        this->ui->treeWgt->addTopLevelItem(topLevelItem);

        // Оповещение об удачной вставке с помощью labelCurve
        this->ui->labelCurve->setText(folderName + QString(" : added"));
        return;
    }
    // Иначе нужно добавить узел-уравнение в выделенную папку
    // (содержимое узла, взятое из equationEdit, проверяется на корректность)
    QTreeWidgetItem* selectedItem = this->ui->treeWgt->selectedItems().first();
    QString line = this->ui->equationEdit->text(),
            err;
    QStringList polynom;

    Polynom::parser(err, line, &polynom);
    if (!err.isEmpty()) {
        err += QString("\n") + line;
        QMessageBox::critical(this, "Error inserting node", err);
        return;
    }

    bool ok = true;
    Polynom::simplifier(ok, polynom);
    if (!ok) {
        err = QString("Invalid monom\n" + line);
        QMessageBox::critical(this, "Error inserting node", err);
        return;
    }

    line.replace("x2", QString('x') + QString(QChar(0262)));
    line.replace("y2", QString('y') + QString(QChar(0262)));
    line.replace(" ", "");

    QTreeWidgetItem* newItem = new QTreeWidgetItem(selectedItem);
    newItem->setText(0, line);
}

void MainWindow::on_actionContext_help_triggered() {
   QMessageBox::about(this, "About Black Quadratic Tuesday",
"<font face=\"menlo\"><center><b>Black Quadratic Tuesday</b> \
allows you to plot quadratic polynomial..<br>..and to get its <u>invariants\
</u>!!<br>Sooo you have a tree at the left-top where folders with \
quadratics are placed!<br>And you can add or delete folder and items and...<br>\
<u><b> to upload them from <font size=\"5\" color=\"blue\">.xml file</font>\
(!!!)</b></u><br><br><br><font size=\"6\">For example: 2x2/2+3y-xy=21\
</font></center></font>");
}

void MainWindow::on_actionAbout_triggered() {
    QMessageBox::about(this, "Black Quadratic Tuesday",
"<font face=\"menlo\"><center><font size=\"5\">Водяков Александр<br>\
М8О-213Б-17<br><br>Black Tuesday Corp.</font></center></font>");
}

void MainWindow::on_actionExit_triggered() {
    this->close();
}

void MainWindow::on_actionOpen_as_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    "Open .xml equations",
                                                    "",
                                                    "Xml(*.xml)");
    if (!fileName.isEmpty())
        this->loadBasicFile(fileName);
}
