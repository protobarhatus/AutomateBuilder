#include "fileparser.h"
#include "field.h"
#include "algorithm.h"
#include "somedataworks.h"
#include <QRegularExpression>
#include "parser.h"
#include "fielddistributor.h"
FileParser::FileParser(Algorithm * alg, FieldDistributor * ifield)
{
    this->algorithm = alg;
    this->field = ifield;
}
QByteArray FileParser::writeAutomate()
{
    QByteArray data;
    data = std::move(this->writeAlgorithm());
    data += std::move(this->writeField());
    return data;
}
QByteArray FileParser::writeAlgorithm()
{
    QByteArray data = "<Algorithm>\r\n";
    data += std::move(this->writeStatements());
    data += std::move(this->writeEnvironsFunctions());
    data += std::move(this->writeVariables());
    data += std::move(this->writeRules());
    data += "<\\Algorithm>\r\n";
    data += "<Statements Images>\r\n";
    auto statements = this->algorithm->getStatementsList();
    for (auto &it : statements)
    {
        if (it.second->isGivenByColor())
            continue;
        QByteArray image = std::move(getPixmapInByteArray(it.second->getSprite(), 0));
        image = qCompress(image, 9);
        image = image.toHex();
        QString size_in_string;
        size_in_string.setNum(image.size());
        data += "#Name:" + it.second->getName() + ";Size:" + size_in_string + ";Image:" + image + ";\r\n";
    }
    data += "<\\Statements Images>\r\n";
    return data;
}
QByteArray FileParser::writeStatements()
{
    QByteArray data;
    data += "\t<Statements>\r\n";
    auto statements = this->algorithm->getStatementsList();
    for (auto & it : statements)
    {
        data += "\t\t#Name:" + it.second->getName() + ";Number:";
        QString number_in_string;
        data += number_in_string.setNum(it.second->getNumber());
        if (it.second->isGivenByColor())
        {
            data += ";GivenBy:COLOR" + getColorInStringRgb(it.second->getColor(), 16, false) + ";\r\n";
        }
        else
        {
            data += ";GivenBy:IMAGE;\r\n";
        }
    }
    data += "\t<\\Statements>\r\n";
    return data;
}
QByteArray FileParser::writeEnvironsFunctions()
{
    QByteArray data;
    data += "\t<Functions>\r\n";
    auto functions = this->algorithm->getEnvironsFunctionsList();
    for (auto &it : functions)
    {
        QString str_x, str_y;
        str_x.setNum(it.second->getX());
        str_y.setNum(it.second->getY());
        data += "\t\t#Name:" + it.second->getName() + ";Is allowed:" + (it.second->isAllowed() ? "true" : "false") + ";X:" +
                str_x + ";Y:" + str_y + ";\r\n";
    }
    data += "\t<\\Functions>\r\n";
    return data;
}
QByteArray FileParser::writeVariables()
{
    QByteArray data;
    data += "\t<Variables>\r\n";
    data += "\t\t<Global> \r\n";
    auto writeLogicVariable =  [&data](LogicVariable * variable) mutable{
        data += "\t\t\t#Name:" + variable->getName() + ";Type:LOGIC;Formula:" + variable->getStringFormula() + ";\r\n";
    };
    auto writeValueVariable = [&data](ValueVariable * variable) mutable {
        data += "\t\t\t#Name:" + variable->getName() + ";Type:VALUE;Formula:" + variable->getStringFormula() + ";\r\n";
    };
    auto logic_variables = this->algorithm->getGlobalLogicVariablesList();
    for (auto &it : logic_variables)
        writeLogicVariable(it.second.get());
    auto value_variables = this->algorithm->getGlobalVariablesList();
    for (auto &it : value_variables)
        writeValueVariable(it.second.get());
    data += "\t\t<\\Global>\r\n\t\t<Local>\r\n";
    logic_variables = this->algorithm->getLogicVariablesList();
    for (auto &it : logic_variables)
        writeLogicVariable(it.second.get());
    value_variables = this->algorithm->getValueVariablesList();
    for (auto &it : value_variables)
        writeValueVariable(it.second.get());
    data += "\t\t<\\Local>\r\n\t<\\Variables>\r\n";
    return data;
}
QByteArray FileParser::writeRules()
{
    QByteArray data;
    data += "\t<Rules>\r\n";
    auto rules = this->algorithm->getRulesList();
    for (auto &it : rules)
    {
        QString str_act= it.second->getStringAction();
        QString str_sec_cond = it.second->getStringSecondAction();
        data += "\t\t#Type:" + QString(it.second->isGlobal() ? "GLOBAL" : "LOCAL") + ";Condition:" +
                it.second->getStringCondition() + ";Action: " + (str_act[0] == ' ' ? str_act : ' ' + str_act) + ";Second action: " +
                (str_sec_cond[0] == ' ' ? str_sec_cond : ' ' + str_sec_cond) + ";\r\n";
    }
    data += "\t<\\Rules>\r\n";
    return data;
}
QByteArray FileParser::writeField()
{
    QByteArray data;
    data += "<Configurations>\r\n";
    auto & configurations = this->field->getFieldsList();
    for (auto &it : configurations)
    {
        data += "\t#Name:" + it.first + ";Width:" + QString::number(it.second->getPropetries().getWidth()) + ";Height:" +
                QString::number(it.second->getPropetries().getHeight()) + ";Cells width:"
                + QString::number(it.second->getPropetries().getCellsWidth()) +
                ";Cells height:" + QString::number(it.second->getPropetries().getCellsHeight()) +
                ";Default statement:" + it.second->getPropetries().default_statements->getName() + ";Field:";
        Field * fieldptr = it.second->getField();
        QByteArray qbfield;
        for (int x = 0; x < it.second->getPropetries().getWidth(); ++x)
        {
            for (int y = 0; y < it.second->getPropetries().getHeight(); ++y)
            {
                qbfield += QString::number(fieldptr->getStatementOfCell(x, y)->getNumber()) + "|";
            }
        }
        qbfield = qCompress(qbfield, 9);
        qbfield = qbfield.toHex();
        data += qbfield + ";\r\n";
    }
    data += "<\\Configurations>";
    return data;
}




void FileParser::readAutomate(QString & data)
{
    this->readAlgorithm(data);
    this->readField(data);
}
void FileParser::readAlgorithm(QString & data)
{
    QString algorithm = std::move(this->getSection(data, "Algorithm"));
    this->readStatements(algorithm);
    this->readEnvironsFunctions(algorithm);
    this->readVariables(algorithm);
    this->readRules(algorithm);

    QStringList images = std::move(this->getSection(data, "Statements Images")).split('#');
    for (auto &it : images)
    {
        if (it.contains(QRegularExpression("^[^\\w]+$")))
            continue;
        QString name = this->getProperty(it, "Name");
        Statement * statement = this->algorithm->getStatement(name);
        int size = this->getProperty(it, "Size").toInt();
        QByteArray qbpixmap;
        qbpixmap += std::move(this->getProperty(it, "Image"));
        qbpixmap = QByteArray::fromHex(qbpixmap);
        qbpixmap = qUncompress(qbpixmap);

        QPixmap pixmap;
        pixmap.loadFromData(qbpixmap);
        statement->setSprite(pixmap);
    }
}
void FileParser::readStatements(QString & data)
{
    QStringList statements = std::move(getSection(data, "Statements").split('#'));
    for (auto &it : statements)
    {
        if (it.contains(QRegularExpression("^[^\\w]+$")))
            continue;
        QString name = getProperty(it, "Name");
        bool is_ok;
        int number = getProperty(it, "Number").toInt(&is_ok);
        if (!is_ok)
            throw QString(it + "   Мусор в значении свойства. Свойство Number должно быть числом");
        QString given_by = getProperty(it, "GivenBy");

        if (given_by.contains("COLOR"))
        {
            QColor color = convertStringRgbToColor(given_by.mid(QString("COLOR").length()), 16);
            this->algorithm->addStatement(name, number, true, color, QPixmap());
        }
        else if (given_by == "IMAGE")
        {

            this->algorithm->addStatement(name, number, false, QColor(), QPixmap());
        }
        else
            throw QString(it + "   Мусор в значении свойства GivenBy. Корректные значения - COLOR<color> или IMAGE");

    }
    SingleCounter::getCounter().setStatementsList(this->algorithm->getStatementsList());
}
void FileParser::readEnvironsFunctions(QString & data)
{
    QStringList functions = std::move(getSection(data, "Functions").split('#'));
    for (auto &it : functions)
    {
        if (it.contains(QRegularExpression("^[^\\w]+$")))
            continue;
        QString name = getProperty(it, "Name");
        bool is_allowed;
        QString str_all = getProperty(it, "Is allowed");
        if (str_all == "true")
            is_allowed = true;
        else if (str_all == "false")
            is_allowed = false;
        else
            throw QString (it + "   Мусор в значении свойства Is allowed. Корректные значения - true или false");
        bool is_ok;
        int x = getProperty(it, "X").toInt(&is_ok);
        int y = getProperty(it, "Y").toInt(&is_ok);
        if (!is_ok)
            throw QString(data + "   Мусор в значении свойства. Свойство Number должно быть числом");
        this->algorithm->addEnvironsFunction(name, x, y, is_allowed);
    }
}
void FileParser::readVariables(QString & data)
{
    QString variables = std::move(getSection(data, "Variables"));
    auto readVariable = [this](QString str_variable, bool is_global) {
        if (str_variable.contains(QRegularExpression("^[^\\w]+$")))
            return;
        QString name = this->getProperty(str_variable, "Name");
        QString type = this->getProperty(str_variable, "Type");
        if (type != "LOGIC" && type != "VALUE")
            throw QString(str_variable + "   Мусор в значении свойства Type. Корректные значения - LOGIC или VALUE");
        QString str_formula = this->getProperty(str_variable, "Formula");
        Parser parser(this->algorithm, this->field, is_global ? PARSER_MODE_GLOBAL_VARIABLE : PARSER_MODE_ITERATIVE_VARIABLE);
        try
        {
            if (type == "LOGIC")
            {
                std::shared_ptr<LogicElement> formula = parser.buildLogicFormula(str_formula);
                this->algorithm->addLogicVariable(name, is_global, str_formula, formula);
            }
            else
            {
                std::shared_ptr<ValueElement> formula = parser.buildValueFormula(str_formula);
                this->algorithm->addValueVariable(name, is_global, str_formula, formula);
            }
        } catch (QString exception)
        {
            throw QString (str_variable + "    Формула неверна. " + exception);
        }

    };
    QStringList global_variables = std::move(getSection(variables, "Global").split('#'));
    for (auto &it : global_variables)
        readVariable(it, true);
    QStringList local_variables = std::move(getSection(variables, "Local").split('#'));
    for (auto &it : local_variables)
        readVariable(it, false);

}
void FileParser::readRules(QString & data)
{
    QStringList rules = std::move(getSection(data, "Rules").split('#'));
    for (auto &it : rules)
    {
        if (it.contains(QRegularExpression("^[^\\w]+$")))
            continue;
        QString type = getProperty(it, "Type");
        if (type != "GLOBAL" && type != "LOCAL")
            throw QString(it + "   Мусор в значении свойства Type. Корректные значение - LOCAL или GLOBAL");
        QString str_condition = getProperty(it, "Condition");
        QString str_action = getProperty(it, "Action");
        QString str_sec_action = getProperty(it, "Second action");
        Rule rule;
        rule.setGlobality(type == "GLOBAL");
        try {
            Parser parser(this->algorithm, this->field, type == "GLOBAL" ? PARSER_MODE_GLOBAL_RULES :
                                                                           PARSER_MODE_LOCAL_RULES);
            rule.setCondition(str_condition, parser.buildLogicFormula(str_condition));
            rule.setAction(str_action, parser.buildAction(str_action));
            rule.setSecondAction(str_sec_action, parser.buildAction(str_sec_action));
        } catch (QString exception) {
            throw (it + "   Ошибка в формуле. " + exception);
        }
        this->algorithm->addRule(rule);
    }
}
void FileParser::readField(QString & data)
{
    QStringList configurations = std::move(getSection(data, "Configurations").split('#'));
    auto readCell = [](QByteArray & field, int & iterator) -> int
    {
        QString str = "";
        while (field[iterator] != '|')
        {
            str += field[iterator];
            ++iterator;
        }
        ++iterator;
        return str.toInt();
    };
    for (auto &it : configurations)
    {
        if (it.contains(QRegularExpression("^[^\\w]+$")))
            continue;
        QString name = getProperty(it, "Name");
        this->field->addField(name);
        this->field->selectField(name);
        auto & properties = this->field->getPropetries();
        properties.setWidth(this->getProperty(it, "Width").toInt());
        properties.setHeight(this->getProperty(it, "Height").toInt());
        properties.setCellsWidth(this->getProperty(it, "Cells width").toInt());
        properties.setCellsHeight(this->getProperty(it, "Cells height").toInt());
        properties.default_statements = this->algorithm->getStatement(this->getProperty(it, "Default statement"));
        this->field->initializeField();
        QByteArray str_field;
        str_field += this->getProperty(it, "Field");
        str_field = QByteArray::fromHex(str_field);
        str_field = qUncompress(str_field);
        Field * fieldptr = this->field->getCurrent();
        int f_iterator = 0;
        for (int x = 0; x < properties.getWidth(); ++x)
        {
            for (int y = 0; y < properties.getHeight(); ++y)
            {
                fieldptr->setStatement(x, y, this->algorithm->getStatement(readCell(str_field, f_iterator)));
            }
        }
    }

}


QString FileParser::getSection(QString & data, QString section_name)
{
    int index_of_section_capture = data.indexOf("<" + section_name + ">");
    if (index_of_section_capture == -1)
        throw QString("Необходимая секция <" + section_name + "> не обнаружена");
    int index_of_section_start = index_of_section_capture + section_name.length() + 2;
    int index_of_section_end = data.indexOf("<\\" + section_name + ">");
    if (index_of_section_end == -1)
        throw QString("Секция <" + section_name + "> не закрыта");
    return data.mid(index_of_section_start, index_of_section_end - index_of_section_start);
}
QString FileParser::getProperty(QString & element, QString property_name)
{
    int index_of_property = element.indexOf(property_name + ":");
    if (index_of_property == -1)
        throw QString(element + "   Необходимое свойство " + property_name + " не найдено");
    int index_of_value = element.indexOf(":", index_of_property) + 1;
    int index_of_end = element.indexOf(";", index_of_property);
    if (index_of_value == index_of_end)
        throw QString(element + "   Отсутствует значение свойства " + property_name);
    return element.mid(index_of_value, index_of_end - index_of_value);
}
