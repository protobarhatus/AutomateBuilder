#include "fielddistributor.h"
#include "field.h"
#include "configuration.h"
#include "statementscounter.h"
FieldDistributor::FieldDistributor(Algorithm * alg)
{
    this->algorithm = alg;
}
void FieldDistributor::addField(QString name)
{
    if (hasField(name))
        return;
    this->fields.insert(std::pair<QString, FieldPtr>(name, FieldPtr(new Configuration(this->algorithm))));
    SingleCounter::getCounter().addConfiguration(name);
}
bool FieldDistributor::hasField(QString name)
{
    return this->fields.find(name) != this->fields.end();
}
void FieldDistributor::selectField(QString name)
{
    auto it = this->fields.find(name);
    this->current_field = it->second->getField();
    this->current_field_name = it->first;
    this->current_field_propetries = &it->second->getPropetries();
    SingleCounter::getCounter().selectConfiguration(name);
}
void FieldDistributor::removeSelection()
{
    this->current_field = nullptr;
    this->current_field_name = "";
    this->current_field_propetries = nullptr;
}
bool FieldDistributor::hasSelection()
{
    return this->current_field != nullptr;
}
void FieldDistributor::eraseField(QString name)
{
    auto it = this->fields.find(name);
    if (it == this->fields.end())
        return;
    if (it->first == this->current_field_name)
        this->removeSelection();
    this->fields.erase(it);
    SingleCounter::getCounter().eraseConfiguration(name);
}
Field* FieldDistributor::operator->()
{
    return this->current_field;
}
Field* FieldDistributor::getCurrent()
{
    return this->current_field;
}
void FieldDistributor::renameField(QString old_name, QString new_name)
{
    if (hasField(new_name))
        return;
    auto it = this->fields.find(old_name);
    if (it == this->fields.end())
        return;
    FieldPtr field = std::move(it->second);
    this->fields.erase(it);
    this->fields.insert(std::pair<QString, FieldPtr>(new_name, std::move(field)));
    SingleCounter::getCounter().renameConfiguration(old_name, new_name);
}
const std::map<QString, FieldDistributor::FieldPtr> & FieldDistributor::getFieldsList()
{
    return this->fields;
}
SimulatingPropetries & FieldDistributor::getPropetries()
{
    return *this->current_field_propetries;
}
void FieldDistributor::uninitializeAllFields()
{
    for (auto &it : this->fields)
    {
        it.second->uninitialize();
    }
}
bool FieldDistributor::isFieldInitialized()
{
    if (!this->hasSelection())
        return false;
    return this->fields.find(this->current_field_name)->second->isInitialized();
}
void FieldDistributor::initializeField()
{
    if (!this->hasSelection())
        return;
    this->fields.find(this->current_field_name)->second->initialize();

}
QString FieldDistributor::getCurrentFieldsName()
{
    return this->current_field_name;
}
