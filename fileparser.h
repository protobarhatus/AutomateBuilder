#ifndef FILEPARSER_H
#define FILEPARSER_H
#include <QString>
class Algorithm;
class FieldDistributor;
//записывает и читает автомат в текстовом состоянии
class FileParser
{
public:
    FileParser(Algorithm * algorithm, FieldDistributor * field);
    QByteArray writeAutomate();
    QByteArray writeAlgorithm();
    QByteArray writeField();
    QByteArray writeStatements();
    QByteArray writeEnvironsFunctions();
    QByteArray writeVariables();
    QByteArray writeRules();

    void readAutomate(QString & data);
    void readAlgorithm(QString & data);
    void readStatements(QString & data);
    void readEnvironsFunctions(QString & data);
    void readVariables(QString & data);
    void readRules(QString & data);
    void readField(QString & data);


private:
    Algorithm * algorithm;
    FieldDistributor * field;

    QString getSection(QString & data, QString section_name);
    QString getProperty(QString & element, QString property_name);
};

#endif // FILEPARSER_H
