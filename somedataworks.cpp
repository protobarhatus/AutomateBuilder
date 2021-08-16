#include "somedataworks.h"
#include "QRegularExpression"
#include "QWidget"
#include "QLineEdit"
#include "QMessageBox"
#include <QPixmap>
#include <QBuffer>
#include <QByteArray>
#include <QDebug>
bool isStringNumber(const QString & string)
{
    QRegularExpression exp("^(([\\+\\-]?[1-9]\\d*)|(0+))$");
    return string.contains(exp);
}
bool isStringConsistOfOneWord(const QString & string)
{
    QRegularExpression exp("^[A-Za-zА-Яа-яё][\\wА-Яа-яё]*$");
    return string.contains(exp);
}
bool hasStringForbiddenSymbols(const QString & string)
{
    QRegularExpression exp("[^A-Za-zА-Яа-яё\\w]");
    return string.contains(exp);
}
//если выражение состоит более чем из одного слова, заключает его в скобки
QString getExpressionAsArgument(const QString & expression)
{
    if (isStringConsistOfOneWord(expression) || isStringNumber(expression))
        return expression;
    else
        return "(" + expression + ")";
}
QString getColorInStringRgb(QColor color, int base, bool with_lattice)
{
    int r, g, b, a;
    color.getRgb(&r, &g, &b, &a);
    QString strR, strG, strB, strA, format;
    //для того, чтобы все обозначения цветов были одного размера (0F вместо F при 16-ричной системе, к примеру)
    format.setNum(255, base);
    auto toFormat = [](const QString & str, int amount_of_symbols)->QString {
        QString correct_result = "";
        for (int i = str.length(); i < amount_of_symbols; ++i)
            correct_result += '0';
        correct_result += str;
        return correct_result;
    };
    return (with_lattice ? "#" : "") + toFormat(strR.setNum(r, base), format.length()) + toFormat(strG.setNum(g, base), format.length())
            + toFormat(strB.setNum(b, base), format.length()) + toFormat(strA.setNum(a, base), format.length());
}
QColor convertStringRgbToColor(QString string, int base)
{
    int color_length = QString::number(255, base).length();
    int lattice_correction = string[0] == '#';
    QColor color;
    color.setRed(string.mid(lattice_correction, color_length).toInt(Q_NULLPTR, base));
    color.setGreen(string.mid(lattice_correction + 1 * color_length, color_length).toInt(Q_NULLPTR, base));
    color.setBlue(string.mid(lattice_correction + 2 * color_length, color_length).toInt(Q_NULLPTR, base));
    if (string.length() == color_length * 4 + lattice_correction)
        color.setAlpha(string.mid(lattice_correction + 3 * color_length, color_length).toInt(Q_NULLPTR, base));
   // else
   //     qDebug() << "Blyat: " << string.length() << " : " << color_length << " : " << lattice_correction << " -" << QString::number(255, base);
    return color;
}
QByteArray getPixmapInByteArray(const QPixmap & pixmap, int quality)
{
    QByteArray byte_array;
    QBuffer buffer(&byte_array);
    buffer.open(QIODevice::WriteOnly);
    pixmap.save(&buffer, "PNG", quality);
    return byte_array;
}
bool checkStringNumberForOverflow(const QString & number)
{
    QString max_int;
    max_int.setNum(std::numeric_limits<int>::max());
    short int minus_and_zeros_shift = (*number.begin() == QChar('-') || *number.begin() == QChar('+')) ? 1 : 0;
    for (auto &it : number.right(number.length() - minus_and_zeros_shift))
    {
        if (it == QChar('0'))
            ++minus_and_zeros_shift;
        else
            break;
    }
    if (number.length() > max_int.length() + minus_and_zeros_shift)
        return false;
    if (number.length() < max_int.length() + minus_and_zeros_shift)
        return true;
    for (int i = 0; i < max_int.length(); ++i)
    {
        if (number[i + minus_and_zeros_shift].toLatin1() > max_int[i] )
            return false;
        else if (number[i + minus_and_zeros_shift].toLatin1() < max_int[i] )
            return true;
    }
    return true;
}
QColor getColor(int red, int green, int blue)
{
    QColor color;
    color.setRed(red);
    color.setGreen(green);
    color.setBlue(blue);
    return color;
}
int divideWithRoundingToBigger(int dividend, int divider) {
    return dividend / divider + (dividend % divider == 0 ? 0 : 1);
};

bool checkLineEditForDataPresense(QLineEdit * edit, QString name_of_essence, QWidget * parent)
{
    if (edit->text().isEmpty())
    {
        QMessageBox::information(parent, "Внимание", "Введите " + name_of_essence);
        return false;
    }
    return true;
}
bool checkForNumber(QLineEdit * edit, QString name_of_essence, QWidget * parent)
{
    if (!isStringNumber(edit->text()))
    {
        QMessageBox::information(parent, "Внимание", name_of_essence + " должен быть числом");
        return false;
    }
    return true;
}
bool checkForOverflow(QLineEdit * edit, QString name_of_essence, QWidget * parent)
{
    if (!checkStringNumberForOverflow(edit->text()))
    {
        QMessageBox::information(parent, "Внимание", name_of_essence + " должен быть в пределах (-2147483648; 2147483648)");
        return false;
    }
    return true;
}
bool checkForForbiddenSymbols(QLineEdit * edit, QString name_of_essence, QWidget * parent)
{
    if (hasStringForbiddenSymbols(edit->text()))
    {
        QMessageBox::information(parent, "Внимание", name_of_essence + " содержит неразрешенные символы. Разрешается \
использовать цифры, буквы английского и русского алфавита, а также знак нижнего подчеркивания");
        return false;
    }
    return true;
}
bool checkForConsistingOfOneWord(QLineEdit * edit, QString name_of_essence, QWidget * parent)
{
    if (!isStringConsistOfOneWord(edit->text()))
    {
        QMessageBox::information(parent, "Внимание", name_of_essence + " должно быть односложным, состоять из цифр, букв \
английского и русского алфавита и не должно начинаться с цифры");
        return false;
    }
    return true;
}
