#ifndef SOMEDATAWORKS_H
#define SOMEDATAWORKS_H
#include "QString"
#include "QColor"
class QLineEdit;
class QWidget;
class QPixmap;

bool isStringNumber(const QString & string);
bool isStringConsistOfOneWord(const QString & string);
bool hasStringForbiddenSymbols(const QString & string);
QString getExpressionAsArgument(const QString & expression);
//гарантируется, что number - число в формате "^[+-]?\w+$"
bool checkStringNumberForOverflow(const QString & number);
int divideWithRoundingToBigger(int dividend, int divider);
QColor getColor(int red, int green, int blue);
bool checkLineEditForDataPresense(QLineEdit * edit, QString name_of_essence, QWidget * parent);
bool checkForNumber(QLineEdit * edit, QString name_of_essence, QWidget * parent);
bool checkForOverflow(QLineEdit * edit, QString name_of_essence, QWidget * parent);
bool checkForForbiddenSymbols(QLineEdit * edit, QString name_of_essence, QWidget * parent);
bool checkForConsistingOfOneWord(QLineEdit * edit, QString name_of_essence, QWidget * parent);
QString getColorInStringRgb(QColor color, int base, bool with_lattice = true);
QByteArray getPixmapInByteArray(const QPixmap & pixmap, int quality = -1);
QColor convertStringRgbToColor(QString string, int base);
#endif // SOMEDATAWORKS_H
