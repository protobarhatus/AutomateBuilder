#ifndef PARSER_H
#define PARSER_H
#include<memory>
#include<QString>
#include<QRegularExpression>

class LogicElement;
class ValueElement;
class Algorithm;
class LogicOperator;
class LogicValueOperator;
class ArithmeticalOperator;
class FieldDistributor;
class Action;
class ActionElement;

//определяет конструкции, которые парсер построит, а которые отбракует. означает то, для чего парсер составляет формулу
enum ParserMode
{
    PARSER_MODE_GLOBAL_VARIABLE,
    PARSER_MODE_ITERATIVE_VARIABLE,
    PARSER_MODE_GLOBAL_RULES,
    PARSER_MODE_LOCAL_RULES

};

//на некоторые ситуации может бросить исключение с неподходящим текстом. перед парсингом, рекомендуется вызвать функцию checkString()
class Parser
{
public:
    Parser(Algorithm * algorithm, FieldDistributor * field, ParserMode mode);
    void setMode(ParserMode mode);
    void setAlgorithm(Algorithm * algorithm);
    std::shared_ptr<LogicElement> buildLogicFormula(QString formula);
    std::shared_ptr<ValueElement> buildValueFormula(QString formula);
    std::shared_ptr<Action> buildAction(QString formula);

    //проверка строки на некоторые из ситуаций, сообщения об ошибках о которых имеют неподходящий текст - наличие
    //лишних закрывающих скобок, к примеру. В случае, если строка проходит проверку, передает управление выше, если нет -
    //кидает исключения.
    void checkString(QString string);
private:
    Algorithm * algorithm;
    FieldDistributor * field;
    ParserMode mode;
    const QRegularExpression logic_operators = QRegularExpression("^\\s?(AND|OR|NAND|NOR|XOR|XNOR)\\s?$");
    const QRegularExpression logic_value_operators = QRegularExpression("^\\s?(==|!=|<|<=|>|>=)\\s?$");
    const QRegularExpression arithmetical_operators = QRegularExpression("^\\s?(\\+|-|\\*|/|//|%)\\s?$");
    const QRegularExpression value_simple_functions = QRegularExpression("^\\s?(STEP|BANNED_FUNCTIONS|ALLOWED_FUNCTIONS|CURRENT_CELL)\\s?$");
    const QRegularExpression logic_params_functions = QRegularExpression("(COND_IN_R|CHANCE|NOT)");
    const QRegularExpression value_params_functions = QRegularExpression("(RAND|COUNT|TERN|SLCOUNT)");
    bool isNumber(QString formula_fragment);
    bool isParamsFunction(QString formula_fragment);
    std::shared_ptr<LogicElement> buildOneWordLogicExpression(QString formula_fragment);
    std::shared_ptr<ValueElement> buildOneWordValueExpression(QString formula_fragment);
    std::shared_ptr<ActionElement> buildActionElement(QString formula_fragment);
    void divideThreePartExpression(QString full_expression, QString & left_part, QString & s_operator, QString & right_part);
    void separateBreaketedPart(QString expression, QString & breaketed_part, QString & remainded_part, int index_of_opening_breaket);
    void separateFirstWord(QString expression, QString & separated_part, QString & remainded_part);
    void separateLastWord(QString expression, QString & separated_part, QString & remainded_part);
    void separateParamsFunction(QString expression, QString & separated_part, QString & remainded_part, int index_of_opening_breaket);
    LogicOperator * identityLogicOperator(QString s_operator);
    LogicValueOperator * identityLogicValueOperator(QString s_operator);
    ArithmeticalOperator * identityArithmeticalOperator(QString s_operator);
    std::shared_ptr<LogicElement> identityLogicParamsFunction(QString formula_fragment);
    std::shared_ptr<LogicElement> identityLogicVariable(QString formula_fragment, bool &have_found);
    std::shared_ptr<ValueElement> identitySimpleValueFunction(QString formula_fragment);
    std::shared_ptr<ValueElement> identityValueVariable(QString formula_fragment, bool &have_found);
    std::shared_ptr<ValueElement> identityCellFunction(QString formula_fragment, bool & have_found);
    std::shared_ptr<ValueElement> identityValueParamsFunction(QString formula_fragment);
    std::shared_ptr<LogicElement> buildCondInRFunction(QString formula_fragment);
    std::shared_ptr<LogicElement> buildChanceFunction(QString formula_fragment);
    std::shared_ptr<LogicElement> buildNotFunction(QString formula_fragment);
    std::shared_ptr<ValueElement> buildRandFunction(QString formula_fragment);
    std::shared_ptr<ValueElement> buildCountFunction(QString formula_fragment);
    std::shared_ptr<ValueElement> buildTernFunction(QString formula_fragment);
    std::shared_ptr<ValueElement> buildSlCountFunction(QString formula_fragment);

    std::shared_ptr<ActionElement> buildSetAction(QString formula_fragment);
    std::shared_ptr<ActionElement> buildSetByFAction(QString formula_fragment);
    std::shared_ptr<ActionElement> buildBanAction(QString formula_fragment);
    std::shared_ptr<ActionElement> buildAllowAction(QString formula_fragment);
    //В функции с параметром заменяет все внутренние функции с параметром на символ @
    QString replaceInternalFunctionsWithStuff(QString function);
    //В функции с параметром заменяет все не односложные аргументы на символ @
    QString replaceAllArgumentsWithStuff(QString function);
    //ожидает выражение в формате "^\(.+\)$". Если это выражение все обернуто в
    //крайние скобки, замещает все внутри скобок на @, иначе (если скобки в начале и
    //конце относятся к разным группам), заменяет на знак @ частично.
    QString replaceAllInBreaketsWithStuff(QString function);
    QString pullOutOfBreakets(QString formula_fragment);
    QString pullOutOfQuotes(QString formula_fragment);
    //функции окружения и CURRENT_CELL
    std::shared_ptr<ValueElement> identityFunctionReturningCell(QString formula_fragment);
};

#endif // PARSER_H
