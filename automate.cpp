#include "automate.h"
#include "QFile"
#include "QDir"

#include "QDebug"

#include "somedataworks.h"

#include "statement.h"
#include "fileparser.h"
#include "fielddistributor.h"
#include "field.h"
#include <QRegularExpression>
bool hasFileNeccesaryExtend(QString path)
{
    return path.right(9) == ".automate";
}
Automate::Automate(bool create_empty) : algorithm(&field, create_empty), field(&algorithm)
{

}
void Automate::createAutomateFile(QString path)
{
    if (!hasFileNeccesaryExtend(path))
        path += ".automate";

    saveAutomate(path);
}
void Automate::saveAutomate(QString path)
{
    QFile file(path);

    QByteArray data;
    FileParser parser(&this->algorithm, &this->field);
    data = std::move(parser.writeAutomate());
    file.open(QIODevice::WriteOnly);
    file.write(data);
    file.close();
}

Algorithm * Automate::getAlgorithm()
{
    return &this->algorithm;
}
FieldDistributor * Automate::getField()
{
    return &this->field;
}
bool Automate::isVariableNameCorrectlyWritten(QString name)
{
    if (Automate::isEnvironsFunctionNameCorrectlyWritten(name))
        return false;
    if (isStringConsistOfOneWord(name))
        return true;
    return false;
}

bool Automate::isEnvironsFunctionNameCorrectlyWritten(QString name)
{
    return name.contains(QRegularExpression("^[A-ZА-Я_]+$"));
}
void Automate::compliteOneStepOfSimulation()
{
    this->algorithm.doGlobalPartOfIteration();
    this->field.getCurrent()->iterate();
}
