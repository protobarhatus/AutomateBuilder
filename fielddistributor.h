#ifndef FIELDDISTRIBUTOR_H
#define FIELDDISTRIBUTOR_H
#include <QString>
#include <map>
#include <memory>
#include "field.h"
#include "configuration.h"
class Field;
class Algorithm;
class Configuration;
class SimulatingPropetries;

class FieldDistributor
{
private:
    typedef std::unique_ptr<Configuration> FieldPtr;
public:
    FieldDistributor(Algorithm * algorithm);
    void addField(QString name);
    bool hasField(QString name);
    void selectField(QString name);
    void removeSelection();
    bool hasSelection();
    void eraseField(QString name);
    void renameField(QString old_name, QString new_name);
    Field* operator->();
    Field* getCurrent();
    const std::map<QString, FieldPtr> & getFieldsList();
    SimulatingPropetries & getPropetries();
    void uninitializeAllFields();
    //current field
    bool isFieldInitialized();
    void initializeField();
    QString getCurrentFieldsName();
private:

    std::map<QString, FieldPtr> fields;
    Field * current_field = nullptr;
    SimulatingPropetries * current_field_propetries = nullptr;
    QString current_field_name;
    Algorithm * algorithm;
};

#endif // FIELDDISTRIBUTOR_H
