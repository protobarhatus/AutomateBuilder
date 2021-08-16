#include "parser.h"
#include "logicvalue.h"
#include "QRegularExpression"
#include "logicoperator.h"
#include "logicvalueoperator.h"
#include "arithmeticaloperator.h"
#include "logicvalue.h"
#include "functioncondinr.h"
#include "functionchance.h"
#include "somedataworks.h"
#include "value.h"
#include "functionstep.h"
#include "functionbannedrules.h"
#include "functionallowedrules.h"
#include "functionrand.h"
#include "functioncount.h"
#include "functiontern.h"
#include "functionnot.h"
#include "functioncurrentcell.h"
#include "algorithm.h"
#include "action.h"
#include "actionsetstatement.h"
#include "actionsetbyf.h"
#include "actionban.h"
#include "actionallow.h"
#include "specialoperators.h"
#include "functionslcount.h"
Parser::Parser(Algorithm * alg, FieldDistributor * ifield, ParserMode imode)
{
    this->algorithm = alg;
    this->field = ifield;
    this->mode = imode;
}
void Parser::setMode(ParserMode imode)
{
    this->mode = imode;
}
void Parser::setAlgorithm(Algorithm * ialgorithm)
{
    this->algorithm = ialgorithm;
}
std::shared_ptr<LogicElement> Parser::buildLogicFormula(QString formula)
{
    formula = formula.simplified();
    formula = this->pullOutOfBreakets(formula);
    try {
    if (formula.contains(QRegularExpression("^((\\S+)|(\\[.+\\]))$")))
    {
        return this->buildOneWordLogicExpression(formula);
    }
    QString left, s_operator, right;
    this->divideThreePartExpression(formula, left, s_operator, right);
    if (s_operator.contains(this->logic_operators))
    {

        LogicOperator * l_operator = this->identityLogicOperator(s_operator);
        try {
        l_operator->setLeftOperand(this->buildLogicFormula(left));
        l_operator->setRightOperand(this->buildLogicFormula(right));
        } catch (QString exception){
            delete l_operator; throw exception;
        }
        std::shared_ptr<LogicElement> oper(l_operator);
        return oper;
    }
    else if (s_operator.contains(this->logic_value_operators))
    {
        LogicValueOperator * lv_operator = this->identityLogicValueOperator(s_operator);
        try {
        lv_operator->setLeftOperand(this->buildValueFormula(left));
        lv_operator->setRightOperand(this->buildValueFormula(right));
        } catch (QString exception) {
            delete lv_operator; throw exception;
        }
        std::shared_ptr<LogicElement> oper(lv_operator);
        return oper;
    }
    else if (s_operator.contains(QRegularExpression("=(?!=)")))
    {
        if (!this->algorithm->hasStatement(this->pullOutOfQuotes(right)))
            throw QString("Состояние с именем " + right + " не найдено");
        StatementsComparisonOperator * oper = new StatementsComparisonOperator;
        try {
            oper->setLeftOperand(this->identityFunctionReturningCell(left));
        } catch (QString exception) {
            delete oper; throw exception;
        }
        oper->setRightOperand(this->algorithm->getStatement(this->pullOutOfQuotes(right)));
        return std::shared_ptr<LogicElement>(oper);
    }
    else {
        if (s_operator.contains(this->arithmetical_operators))
            throw (QString)"Нельзя применять арифметический оператор для выражения логического значения";
        else
            throw QString("Некорректный оператор " + s_operator);
    }

    }
    catch(QString exception)
        {throw exception;}
}
std::shared_ptr<ValueElement> Parser::buildValueFormula(QString formula)
{
    formula = formula.simplified();
    formula = this->pullOutOfBreakets(formula);
    try {
        if (formula.contains(QRegularExpression("^((\\S+)|(\\[.+\\]))$")))
            return this->buildOneWordValueExpression(formula);
        QString left, s_operator, right;
        this->divideThreePartExpression(formula, left, s_operator, right);
        if (s_operator.contains(this->arithmetical_operators))
        {
            ArithmeticalOperator * a_operator = this->identityArithmeticalOperator(s_operator);
            try {
                a_operator->setLeftOperand(this->buildValueFormula(left));
                a_operator->setRightOperand(this->buildValueFormula(right));
            } catch (QString exception) {
                delete a_operator; throw exception;
            }
            std::shared_ptr<ValueElement> oper(a_operator);
            return oper;
        }
        if (s_operator.contains(this->logic_operators) ||
                s_operator.contains(this->logic_value_operators))
            throw (QString)"Нельзя применять логический оператор для выражения числового значения";
        else
            throw (QString)"Неизвестный оператор " + s_operator;

    } catch (QString exception) { throw exception;}
}
std::shared_ptr<LogicElement> Parser::buildOneWordLogicExpression(QString formula_fragment)
{
try {
    if (formula_fragment == "true")
        return std::shared_ptr<LogicElement>(new LogicValue(true));
    if (formula_fragment == "false")
        return std::shared_ptr<LogicElement>(new LogicValue(false));
    if (formula_fragment.contains(QRegularExpression("^\\[.+\\]$")))
    {
        return identityLogicParamsFunction(formula_fragment);
    }
    bool have_found_variable;
    std::shared_ptr<LogicElement> variable = this->identityLogicVariable(formula_fragment, have_found_variable);
    if (have_found_variable)
        return variable;
    else
        throw QString("Неизвестный или неподходящий идентификатор " + formula_fragment);
    } catch(QString exception) { throw exception;}
}
std::shared_ptr<ValueElement> Parser::buildOneWordValueExpression(QString formula_fragment)
{
 try {
    if (isStringNumber(formula_fragment))
        return std::shared_ptr<ValueElement>(new Value(formula_fragment.toInt()));
    if (formula_fragment.contains(this->value_simple_functions))
        return this->identitySimpleValueFunction(formula_fragment);
    if (formula_fragment.contains(QRegularExpression("^\\[.+\\]$")))
    {

            return this->identityValueParamsFunction(formula_fragment);

    }
    bool have_found_variable;
    std::shared_ptr<ValueElement> variable = this->identityValueVariable(formula_fragment, have_found_variable);
    if (have_found_variable)
        return variable;
    bool have_found_cell_function;
    std::shared_ptr<ValueElement> cell_function = this->identityCellFunction(formula_fragment, have_found_cell_function);
    if (have_found_cell_function)
        return cell_function;
    throw (QString)"Неизвестный или неподходящий идентификатор " + formula_fragment;
    } catch (QString exception) { throw exception;}
}
std::shared_ptr<ValueElement> Parser::identitySimpleValueFunction(QString formula_fragment)
{
    formula_fragment = formula_fragment.simplified();
    if (formula_fragment == "STEP")
        return std::shared_ptr<FunctionSTEP>(new FunctionSTEP(this->algorithm));
    if (formula_fragment == "BANNED_FUNCTIONS")
        return std::shared_ptr<FunctionBannedRules>(new FunctionBannedRules(this->algorithm));
    if (formula_fragment == "ALLOWED_FUNCTIONS")
        return std::shared_ptr<FunctionAllowedRules>(new FunctionAllowedRules(this->algorithm));
    if (formula_fragment == "CURRENT_CELL")
    {
        if (this->mode == PARSER_MODE_GLOBAL_VARIABLE)
            throw (QString)"Функция CURRENT_CELL не может быть использована в формуле глобальных переменных";
        else if (this->mode == PARSER_MODE_GLOBAL_RULES)
            throw (QString)"Функция CURRENT_CELL не может быть использована в формуле глобальных правил";
        else
            return std::shared_ptr<FunctionCurrentCell>(new FunctionCurrentCell(this->field));
    }
}
LogicOperator * Parser::identityLogicOperator(QString s_operator)
{
    s_operator = s_operator.simplified();
    if (s_operator == "AND")
        return new OperatorAND;
    if (s_operator == "OR")
        return new OperatorOR;
    if (s_operator == "NAND")
        return new OperatorNAND;
    if (s_operator == "NOR")
        return new OperatorNOR;
    if (s_operator == "XOR")
        return new OperatorXOR;
    if (s_operator == "XNOR")
        return new OperatorXNOR;

}
LogicValueOperator * Parser::identityLogicValueOperator(QString s_operator)
{
    s_operator = s_operator.simplified();
    if (s_operator == "==")
        return new OperatorEquals;
    if (s_operator == "!=")
        return new OperatorNotEquals;
    if (s_operator == "<")
        return new OperatorLess;
    if (s_operator == "<=")
        return new OperatorLessEquals;
    if (s_operator == ">")
        return new OperatorBigger;
    if (s_operator == ">=")
        return new OperatorBiggerEquals;
}
ArithmeticalOperator * Parser::identityArithmeticalOperator(QString s_operator)
{
    s_operator = s_operator.simplified();
    if (s_operator == "+")
        return new OperatorPlus;
    if (s_operator == "-")
        return new OperatorMinus;
    if (s_operator == "*")
        return new OperatorMultiplication;
    if (s_operator == "/")
        return new OperatorDivision;
    if (s_operator == "//")
        return new OperatorDivisionWithRounding;
    if (s_operator == "%")
        return new OperatorRemainder;
}
void Parser::divideThreePartExpression(QString formula, QString & left, QString & s_operator, QString & right)
{
    if (!formula.contains(QRegularExpression("^(\\S+|\\(.+\\)|\\[.+\\])\\s\\S+\\s(\\S+|\\(.+\\)|\\[.+\\])$")))
        throw QString("Выражение " + formula + " не подходит под формат \"выражение - оператор - выражение\"");
    try {
    //если левое условие выражено оператором, оно будет начинаться со скобки
    if (formula[0] == '(')
    {
        this->separateBreaketedPart(formula, left, formula, 0);
    }
    else if (formula[0] == '[') // если левое условие выражено оператором, оно будет начинаться с квадратной скобки
    {
        this->separateParamsFunction(formula, left, formula, 0);
    }
    else
    {
        this->separateFirstWord(formula, left, formula);
    }
    if (formula.contains(QRegularExpression("^[^\\(]+\\)$")))
        throw QString("В строке \"" + formula + "\" присутствует лишняя закрывающая скобка )");
    if (formula.contains(QRegularExpression("^[^\\[]+\\]$")))
        throw QString("В строке \"" + formula + "\" присутствует лишняя закрывающая квадратная скобка ]");
    //если правое условие выражено оператором, оно будет заканчиваться скобкой
    if (formula.back() == ')')
    {
        this->separateBreaketedPart(formula, right, formula, formula.indexOf(QRegularExpression("\\(.+\\)$")));
    }
    else if(formula.back() == ']')
    {
        this->separateParamsFunction(formula, right, formula, formula.indexOf(QRegularExpression("\\[.+\\]$")));
    }
    else
    {
        this->separateLastWord(formula, right, formula);
    }
    s_operator = formula;
    } catch (QString exception)
    { throw exception;}
}
void Parser::separateBreaketedPart(QString expression, QString & breaketed_part, QString & remainded_part, int index_of_opening_breaket)
{
    //данный счетчик показывает кол-во открывающих скобок, которых нужно закрыть. нужно для нормальной работы со вложенными в скобки группами
    int breaket_counter = 1;
    int index_of_closing_breaket = index_of_opening_breaket + 1;
    for (; breaket_counter != 0; ++index_of_closing_breaket)
    {
        if (index_of_closing_breaket == expression.length())
            throw QString("В строке \"" + expression + "\" присутствует незакрытая скобка");
        if (expression[index_of_closing_breaket] == ')')
        {
            --breaket_counter;
        }
        if (expression[index_of_closing_breaket] == '(')
        {
            ++breaket_counter;
        }
    }
    remainded_part = expression.left(index_of_opening_breaket) + expression.right(expression.length() - index_of_closing_breaket);
    breaketed_part = expression.mid(index_of_opening_breaket + 1, index_of_closing_breaket - index_of_opening_breaket - 2);
}
//разница от отделения части в круглых скобках в том, что квадратные скобки также должны войти в separated_part
void Parser::separateParamsFunction(QString expression, QString & separated_part, QString & remainded_part, int index_of_opening_breaket)
{
    int breaket_counter = 1;
    int index_of_closing_breaket = index_of_opening_breaket + 1;
    for (; breaket_counter != 0; ++index_of_closing_breaket)
    {
        if (index_of_closing_breaket == expression.length())
            throw QString("В строке \"" + expression + "\" присутствует незакрытая квадратная скобка");
        if (expression[index_of_closing_breaket] == ']')
        {
            --breaket_counter;
        }
        if (expression[index_of_closing_breaket] == '[')
        {
            ++breaket_counter;
        }
    }
    remainded_part = expression.left(index_of_opening_breaket) + expression.right(expression.length() - index_of_closing_breaket);
    separated_part = expression.mid(index_of_opening_breaket, index_of_closing_breaket - index_of_opening_breaket);
}
//expression не должен начинаться с пробелов, в противном случае - исключение
void Parser::separateFirstWord(QString expression, QString & separated_part, QString & remainded_part)
{
    //expression was simplified
    int index_of_space = expression.indexOf(" ");
    //теоретически, такого не может быть. но мало ли
    if (index_of_space == -1)
        throw QString("Internal error. Monosyllabic expression handled incorrectly.");
    if (index_of_space == 0)
        throw (QString)"Internal error. The expression haven't simplified.";
    separated_part = expression.left(index_of_space);
    remainded_part = expression.right(expression.length() - index_of_space - 1);

}
//expression не должно заканчиваться пробелами. в противном случае - иключение"
void Parser::separateLastWord(QString expression, QString & separated_part, QString & remainded_part)
{
    int index_of_last_space = expression.indexOf(QRegularExpression("\\s\\S+$"));
    if (index_of_last_space == -1)
        throw (QString)"Internal error. Can not separate right operand. Expression doesn't match the pattern \"\\s\\S+$\"";
    separated_part = expression.right(expression.length() - index_of_last_space - 1);
    remainded_part = expression.left(index_of_last_space);
}
std::shared_ptr<LogicElement> Parser::identityLogicParamsFunction(QString formula_fragment)
{
    try {
        QString function_without_internal = this->replaceAllArgumentsWithStuff(formula_fragment);
    if (function_without_internal.contains("COND_IN_R"))
    {
        return this->buildCondInRFunction(formula_fragment);
    }
    if (function_without_internal.contains("CHANCE"))
    {
        return this->buildChanceFunction(formula_fragment);
    }
    if (function_without_internal.contains("NOT"))
    {
        return this->buildNotFunction(formula_fragment);
    }
    } catch (QString exception) { throw exception;}
    if (formula_fragment.contains(this->value_params_functions))
        throw QString("Числовая функция " + formula_fragment + " не может использоваться как логическое выражение.");
    throw QString("Неизвестная функция " + formula_fragment);


}
std::shared_ptr<ValueElement> Parser::identityValueParamsFunction(QString formula_fragment)
{
    try {
        QString function_without_internal = this->replaceAllArgumentsWithStuff(formula_fragment);
    if (function_without_internal.contains("RAND"))
    {
        return this->buildRandFunction(formula_fragment);
    }
    if (function_without_internal.contains("COUNT"))
    {
        return this->buildCountFunction(formula_fragment);
    }
    if (function_without_internal.contains("TERN"))
    {
        return this->buildTernFunction(formula_fragment);
    }
    } catch (QString exception) { throw exception;}
    if (formula_fragment.contains(this->logic_params_functions))
        throw QString("Логическая функция " + formula_fragment + " не может использоваться \
как числовое выражение");
    throw QString("Неизвестная функция " + formula_fragment);
}
std::shared_ptr<LogicElement> Parser::buildCondInRFunction(QString formula_fragment)
{
    if (this->mode == PARSER_MODE_GLOBAL_VARIABLE)
        throw (QString)"Функция COND_IN_R не может быть использована в формуле глобальных переменных";
    if (this->mode == PARSER_MODE_GLOBAL_RULES)
        throw (QString)"Функция COND_IN_R не может быть использована в формуле глобальных правил";
    FunctionCondInR * function = new FunctionCondInR(this->algorithm, this->field);
    QString sR, slow, shigh, soperator, sval, function_without_internal;
    int index_of_R, index_of_FR, index_of_TO, index_of_oper, index_of_rvalue, index_of_end;
    try{
    //облегчает поиск аргументов по регэспам
    function_without_internal = this->replaceAllArgumentsWithStuff(formula_fragment);
    if (!function_without_internal.contains(QRegularExpression("^\\[\\s?COND_IN_R\\s\\S+\\sFR\\s\\S+\\sTO\\s\\S+\\s(==|!=|<|<=|>|>=)\\s\\S+\\s?\\]$")))
        throw (QString)"Неправильный синтаксис функции COND_IN_R.";
    index_of_R = function_without_internal.indexOf(QRegularExpression("\\S+\\sFR"));
    index_of_FR = function_without_internal.indexOf(QRegularExpression("\\S+\\sTO"));
    index_of_TO = function_without_internal.indexOf(QRegularExpression("\\S+\\s(==|!=|<|<=|>|>=)"));
    index_of_oper = function_without_internal.indexOf(QRegularExpression("(==|!=|<|<=|>|>=)"));
    index_of_rvalue = function_without_internal.indexOf(QRegularExpression("\\S+\\s?\\]$"));
    index_of_end = function_without_internal.indexOf(QRegularExpression("\\s?\\]$"));

    sR = formula_fragment.mid(index_of_R, index_of_FR - index_of_R - 1 - 3);
    slow = formula_fragment.mid(index_of_FR, index_of_TO - index_of_FR - 1 - 3);
    shigh = formula_fragment.mid(index_of_TO, index_of_oper - index_of_TO - 1);
    soperator = formula_fragment.mid(index_of_oper, index_of_rvalue - index_of_oper - 1);
    //в отличии от предыдущих ф-ций, index_of_end всегда указывает на символ сразу за правым выражением, поэтому -1 не нужен
    sval = formula_fragment.mid(index_of_rvalue, index_of_end - index_of_rvalue);
    ParserMode old_mode = this->mode;
    this->mode = PARSER_MODE_GLOBAL_VARIABLE;
    function->setRadius(this->buildValueFormula(sR));
    this->mode = old_mode;
    function->setLowBorder(this->buildValueFormula(slow));
    function->setHighBorder(this->buildValueFormula(shigh));
    function->setOperator(std::shared_ptr<LogicValueOperator>(this->identityLogicValueOperator(soperator)));
    function->setRightOperand(this->buildValueFormula(sval));
    }
    catch (QString exception)
    {
        delete function;
        throw exception;
    }
    return std::shared_ptr<LogicElement>(function);

}
std::shared_ptr<LogicElement> Parser::buildChanceFunction(QString formula_fragment)
{

    FunctionChance * function = new FunctionChance;
    QString schance, function_without_internal;
    int index_of_chance, index_of_end;
    try {
    function_without_internal = this->replaceAllArgumentsWithStuff(formula_fragment);
    if (!function_without_internal.contains(QRegularExpression("^\\[\\s?CHANCE\\s\\S+\\s?\\]$")))
        throw (QString)"Неправильный синтаксис функции CHANCE";
    index_of_chance = function_without_internal.indexOf(QRegularExpression("\\S+\\s?\\]$"));
    index_of_end = function_without_internal.indexOf(QRegularExpression("\\s?\\]$"));

    schance = formula_fragment.mid(index_of_chance, index_of_end - index_of_chance);

    function->setChance(this->buildValueFormula(schance));
    } catch (QString exception) {
        delete function;
        throw exception;
    }
    return std::shared_ptr<LogicElement>(function);
}
std::shared_ptr<LogicElement> Parser::buildNotFunction(QString formula_fragment)
{
    FunctionNot * function = new FunctionNot;
    try {
        QString function_without_internal = this->replaceAllArgumentsWithStuff(formula_fragment);
        if (!function_without_internal.contains(QRegularExpression("^\\[\\s?NOT\\s\\S+\\s?\\]$")))
            throw (QString)"Неправильный синтаксис функции NOT";

        int index_of_expr, index_of_end;
        index_of_expr = function_without_internal.indexOf(QRegularExpression("\\S+\\s?\\]$"));
        index_of_end = function_without_internal.indexOf(QRegularExpression("\\s?\\]$"));

        QString sexpr;
        sexpr = formula_fragment.mid(index_of_expr, index_of_end - index_of_expr);


        function->setExpression(this->buildLogicFormula(sexpr));
        return std::shared_ptr<LogicElement>(function);
    } catch (QString exception) {
        delete function;
        throw exception;
    }
}
std::shared_ptr<ValueElement> Parser::buildRandFunction(QString formula_fragment)
{

    FunctionRand * function = new FunctionRand;
    QString slow, shigh, function_without_internal;
    int index_of_low, index_of_high, index_of_end;
    try {
        function_without_internal = this->replaceAllArgumentsWithStuff(formula_fragment);
        if (!function_without_internal.contains(QRegularExpression("^\\[\\s?RAND\\s\\S+\\sTO\\s\\S+\\s?\\]$")))
            throw (QString)"Неправильный синтаксис функции RAND";
        index_of_low = function_without_internal.indexOf(QRegularExpression("\\S+\\sTO"));
        index_of_high = function_without_internal.indexOf(QRegularExpression("\\S+\\s?\\]$"));
        index_of_end = function_without_internal.indexOf(QRegularExpression("\\s?\\]$"));

        slow = formula_fragment.mid(index_of_low, index_of_high - index_of_low - 1 - 3);
        shigh = formula_fragment.mid(index_of_high, index_of_end - index_of_high);

        function->setLow(this->buildValueFormula(slow));
        function->setHigh(this->buildValueFormula(shigh));
    } catch (QString exception)
    {
        delete function;
        throw exception;
    }
    return std::shared_ptr<ValueElement>(function);
}
std::shared_ptr<ValueElement> Parser::buildCountFunction(QString formula_fragment)
{
    if (this->mode == PARSER_MODE_GLOBAL_VARIABLE)
        throw (QString)"Функция COUNT не может быть использована в формуле глобальных переменных";
    if (this->mode == PARSER_MODE_GLOBAL_RULES)
        throw (QString)"Функция COUNT не может быть использована в формуле глобальных правил";
    FunctionCount * function = new FunctionCount(this->algorithm, this->field);
    QString srad, soperator, sright_value;
    int index_of_rad, index_of_operator, index_of_right_value, index_of_end;
    try {
        QString function_without_internal = this->replaceAllArgumentsWithStuff(formula_fragment);
        if (!function_without_internal.contains(QRegularExpression("^\\[\\s?COUNT\\s\\S+\\s(==|!=|<|<=|>|>=)\\s\\S+\\s?\\]$")))
            throw (QString)"Неправильный синтаксис функции COUNT";
        index_of_rad = function_without_internal.indexOf(QRegularExpression("\\S+\\s(==|!=|<|<=|>|>=)"));
        index_of_operator = function_without_internal.indexOf(QRegularExpression("(==|!=|<|<=|>|>=)"));
        index_of_right_value = function_without_internal.indexOf(QRegularExpression("\\S+\\s?\\]$"));
        index_of_end = function_without_internal.indexOf(QRegularExpression("\\s?\\]$"));

        srad = formula_fragment.mid(index_of_rad, index_of_operator - index_of_rad - 1);
        soperator = formula_fragment.mid(index_of_operator, index_of_right_value - index_of_operator - 1);
        sright_value = formula_fragment.mid(index_of_right_value, index_of_end - index_of_right_value);
        ParserMode old_mode = this->mode;
        this->mode = PARSER_MODE_GLOBAL_VARIABLE;
        function->setRadius(this->buildValueFormula(srad));
        this->mode = old_mode;
        function->setOperator(std::shared_ptr<LogicValueOperator>(this->identityLogicValueOperator(soperator)));
        function->setRightOperand(this->buildValueFormula(sright_value));
    } catch (QString exception) {
        delete function;
        throw exception;
    }
    return std::shared_ptr<ValueElement>(function);
}
std::shared_ptr<ValueElement> Parser::buildSlCountFunction(QString formula_fragment)
{
    if (this->mode == PARSER_MODE_GLOBAL_VARIABLE)
        throw (QString)"Функция SLCOUNT не может быть использована в формуле глобальных переменных";
    if (this->mode == PARSER_MODE_GLOBAL_RULES)
        throw (QString)"Функция SLCOUNT не может быть использована в формуле глобальных правил";
    FunctionSlCount * function = new FunctionSlCount(this->algorithm, this->field);
    QString srad, soperator, sright_value;
    int index_of_rad, index_of_operator, index_of_right_value, index_of_end;
    try {
        QString function_without_internal = this->replaceAllArgumentsWithStuff(formula_fragment);
        if (!function_without_internal.contains(QRegularExpression("^\\[\\s?SLCOUNT\\s\\S+\\s(==|!=|<|<=|>|>=)\\s\\S+\\s?\\]$")))
            throw (QString)"Неправильный синтаксис функции SLCOUNT";
        index_of_rad = function_without_internal.indexOf(QRegularExpression("\\S+\\s(==|!=|<|<=|>|>=)"));
        index_of_operator = function_without_internal.indexOf(QRegularExpression("(==|!=|<|<=|>|>=)"));
        index_of_right_value = function_without_internal.indexOf(QRegularExpression("\\S+\\s?\\]$"));
        index_of_end = function_without_internal.indexOf(QRegularExpression("\\s?\\]$"));

        srad = formula_fragment.mid(index_of_rad, index_of_operator - index_of_rad - 1);
        soperator = formula_fragment.mid(index_of_operator, index_of_right_value - index_of_operator - 1);
        sright_value = formula_fragment.mid(index_of_right_value, index_of_end - index_of_right_value);
        function->setRadius(this->buildValueFormula(srad));
        function->setOperator(std::shared_ptr<LogicValueOperator>(this->identityLogicValueOperator(soperator)));
        function->setRightOperand(this->buildValueFormula(sright_value));
    } catch (QString exception) {
        delete function;
        throw exception;
    }
    return std::shared_ptr<ValueElement>(function);
}
std::shared_ptr<ValueElement> Parser::buildTernFunction(QString formula_fragment)
{
    FunctionTern * function = new FunctionTern;
    try {
       QString function_without_internal = this->replaceAllArgumentsWithStuff(formula_fragment);
       if (!function_without_internal.contains(QRegularExpression("^\\[\\s?TERN\\s\\S+\\sY\\s\\S+\\sN\\s\\S+\\s?\\]$")))
           throw (QString)"Неправильный синтаксис функции TERN";
       int index_of_cond, index_of_yes, index_of_no, index_of_end;
       index_of_cond = function_without_internal.indexOf(QRegularExpression("\\S+\\sY"));
       index_of_yes = function_without_internal.indexOf(QRegularExpression("\\S+\\sN"));
       index_of_no = function_without_internal.indexOf(QRegularExpression("\\S+\\s?\\]$"));
       index_of_end = function_without_internal.indexOf(QRegularExpression("\\s?\\]$"));

       QString scond, syes, sno;
       scond = formula_fragment.mid(index_of_cond, index_of_yes - index_of_cond - 1 - 2);
       syes = formula_fragment.mid(index_of_yes, index_of_no - index_of_yes - 1 - 2);
       sno = formula_fragment.mid(index_of_no, index_of_end - index_of_no);


       function->setCondition(this->buildLogicFormula(scond));
       function->setResultIfTrue(this->buildValueFormula(syes));
       function->setResultIfFalse(this->buildValueFormula(sno));
       return std::shared_ptr<ValueElement>(function);
    } catch (QString exception)
    {
        delete function;
        throw exception;
    }

}
QString Parser::replaceAllArgumentsWithStuff(QString function)
{
    try {
        function = this->replaceInternalFunctionsWithStuff(function);
    } catch (QString exception) {
        throw exception;
    }
    int breaket_counter = 0;

    //начинается с 1 и заканчивается на length() - 1, т. к. эти позиции все-равно заняты квадратными скобками
    for (int i = 1; i < function.length() - 1; ++i)
    {
        if (function[i] == '(')
        {
            ++breaket_counter;
        }
        if (function[i] == ')')
        {
            --breaket_counter;
            function[i] = '@';
        }
        if (breaket_counter > 0)
        {
            function[i] = '@';
        }

    }
    if (breaket_counter > 0)
        throw (QString)"В строке присутствует незакрытая скобка (";
    if (breaket_counter < 0)
        throw (QString)"В строке присутствует лишняя закрывающая скобка )";
    return function;

}
QString Parser::replaceAllInBreaketsWithStuff(QString function)
{
    int breaket_counter = 1;
    //начинается с 1 и заканчивается на length() - 1, т. к. эти позиции все-равно заняты квадратными скобками
    for (int i = 1; i < function.length() - 1; ++i)
    {
        if (function[i] == '(')
        {
            ++breaket_counter;
        }
        if (function[i] == ')')
        {
            --breaket_counter;
            function[i] = '@';
        }
        if (breaket_counter > 0)
        {
            function[i] = '@';
        }

    }
    if (breaket_counter > 1)
        throw (QString)"В строке присутствует незакрытая скобка (";
    if (breaket_counter < 1)
        throw (QString)"В строке присутствует лишняя закрывающая скобка )";
    return function;
}
std::shared_ptr<LogicElement> Parser::identityLogicVariable(QString formula_fragment, bool & have_found)
{
    formula_fragment = formula_fragment.simplified();
    std::shared_ptr<LogicVariable> variable;
    try {
        variable = this->algorithm->getLogicVariable(formula_fragment);
    } catch (QString exception) {
        have_found = false;
        return variable;
    }
    if (this->mode == PARSER_MODE_GLOBAL_VARIABLE)
        throw (QString)"Переменные не могут быть использованы в формуле глобальных переменных";
    if (this->mode == PARSER_MODE_ITERATIVE_VARIABLE && !variable->isGlobal())
        throw (QString)"Только глобальные переменные могут быть использованы в формуле локальных переменных";
    if (this->mode == PARSER_MODE_GLOBAL_RULES && !variable->isGlobal())
        throw (QString)"Локальные переменные не могут быть использованы в формуле глобальных правил";
    have_found = true;
    return variable;
}
std::shared_ptr<ValueElement> Parser::identityValueVariable(QString formula_fragment, bool & have_found)
{
    formula_fragment = formula_fragment.simplified();
    std::shared_ptr<ValueVariable> variable;
    try {
        variable = this->algorithm->getValueVariable(formula_fragment);
    } catch (QString exception) {
        have_found = false;
        return variable;
    }
    if (this->mode == PARSER_MODE_GLOBAL_VARIABLE)
        throw (QString)"Переменные не могут быть использованы в формуле глобальных переменных";
    if (this->mode == PARSER_MODE_ITERATIVE_VARIABLE && !variable->isGlobal())
        throw (QString)"Только глобальные переменные могут быть использованы в формуле локальных переменных";
    if (this->mode == PARSER_MODE_GLOBAL_RULES && !variable->isGlobal())
        throw (QString)"Локальные переменные не могут быть использованы в глобальных правилах";
    have_found = true;
    return variable;
}

QString Parser::replaceInternalFunctionsWithStuff(QString function)
{
    int square_breaket_counter = 0;
    //цикл не будет затрагивать саму функцию, только внутренние внутри нее, поэтому, чтобы пропустить скобки в начале и в конце,
    //начинается с 1 и заканчивается на length() - 1
    for (int i = 1; i < function.length() - 1; ++i)
    {
        if (function[i] == '[')
        {
            ++square_breaket_counter;
        }
        if (function[i] == ']')
        {
            --square_breaket_counter;
            function[i] = '@';
        }
        if (square_breaket_counter > 0)
        {
            function[i] = '@';
        }

    }
    if (square_breaket_counter > 0)
        throw (QString)"В строке присутствует незакрытая квадратная скобка [";
    if (square_breaket_counter < 0)
        throw (QString)"В строке присутствует лишняя закрывающая квадратная скобка ]";
    return function;
}
void Parser::checkString(QString string)
{
    if (string.length() == 0)
        throw (QString) "Передана пустая строка";
    int breaket_counter = 0;
    for (int i = 0; i < string.length(); ++i)
    {
        if (string[i] == '(')
            breaket_counter++;
        if (string[i] == ')')
            breaket_counter--;
    }
    if (breaket_counter > 0)
        throw (QString)"В строке присутствует незакрытая скобка";
    if (breaket_counter < 0)
        throw (QString)"В строке присутствует лишняя закрывающая скобка";
}
std::shared_ptr<ValueElement> Parser::identityCellFunction(QString formula_fragment, bool & have_found)
{
    formula_fragment = formula_fragment.simplified();
    std::shared_ptr<ValueElement> function;
    try {
        function = this->algorithm->getEnvironsFunction(formula_fragment);
    } catch (QString exception) {
        have_found = false;
        return function;
    }
    if (this->mode == PARSER_MODE_GLOBAL_VARIABLE)
        throw (QString)"Функция окрестности не может быть использована в формуле глобальных переменных.";
    if (this->mode == PARSER_MODE_GLOBAL_RULES)
        throw (QString)"Функция окрестности не может быть использована в формуле глобальных правил";
    have_found = true;
    return function;
}
QString Parser::pullOutOfBreakets(QString formula_fragment)
{


    while (formula_fragment.contains(QRegularExpression("^\\(.+\\)$")))
    {
        QString fragment_with_only_outside_breakets = replaceAllInBreaketsWithStuff(formula_fragment);
        if (!fragment_with_only_outside_breakets.contains(QRegularExpression("^\\(@+\\)$")))
            return formula_fragment;
        formula_fragment.remove(0, 1);
        formula_fragment.remove(formula_fragment.length() - 1, 1);
        formula_fragment = formula_fragment.simplified();
    }
    return formula_fragment;
}
QString Parser::pullOutOfQuotes(QString formula_fragment)
{
    if (!formula_fragment.contains(QRegularExpression("^\"[^\"]+\"$")))
        throw (QString)"Неверный синтаксис выражения в кавычках";
    formula_fragment.remove(0, 1);
    formula_fragment.remove(formula_fragment.length() - 1, 1);
    return formula_fragment;
}
std::shared_ptr<Action> Parser::buildAction(QString formula)
{
    Action * action = new Action;
    formula = formula.simplified();
    if (formula == "")
        return std::shared_ptr<Action>(new Action());
    int amount_of_addictive_action_elements = formula.count("&");

    try {
        for (int action_elements_handled = 0; action_elements_handled < amount_of_addictive_action_elements; ++action_elements_handled)
        {
            QString action_element;
            int index_of_next_action = formula.indexOf(QRegularExpression("&"));
            action_element = formula.left(index_of_next_action);
            formula = formula.right(formula.size() - index_of_next_action - 1);

            action->addActionElement(this->buildActionElement(action_element), action_element);

        }
        action->addActionElement(this->buildActionElement(formula), formula);
    } catch (QString exception) {
        delete action;
        throw exception;
    }
    return std::shared_ptr<Action>(action);

}
std::shared_ptr<ActionElement> Parser::buildActionElement(QString formula_fragment)
{
    try {
        if (formula_fragment.contains(QRegularExpression("SET[\\s\"]")))
            return this->buildSetAction(formula_fragment);
        if (formula_fragment.contains(QRegularExpression("SET_BY_F")))
            return this->buildSetByFAction(formula_fragment);
        if (formula_fragment.contains(QRegularExpression("BAN")))
            return this->buildBanAction(formula_fragment);
        if (formula_fragment.contains(QRegularExpression("ALLOW")))
            return this->buildAllowAction(formula_fragment);
        throw QString("Неизвестное действие " + formula_fragment);
    } catch (QString exception) {
        throw exception;
    }

}
std::shared_ptr<ActionElement> Parser::buildSetAction(QString formula_fragment)
{
    if (this->mode == PARSER_MODE_GLOBAL_RULES)
        throw (QString)"Команда SET не может быть использована в глобальных правилах";
    formula_fragment = formula_fragment.simplified();
    if (!formula_fragment.contains(QRegularExpression("^SET\\s?\"\\S+\"$")))
        throw (QString)"Неправильный синтаксис команды SET";
    ActionSetStatement * action = new ActionSetStatement(this->field);
    try {
        int index_of_opening_quote = formula_fragment.indexOf('\"');
        QString statements_name;
        statements_name = this->pullOutOfQuotes(formula_fragment.right(formula_fragment.size() - index_of_opening_quote));
        if (!this->algorithm->hasStatement(statements_name))
            throw QString("Состояние с именем \"" + statements_name + "\" не существует");
        action->setStatement(this->algorithm->getStatement(statements_name));
        return std::shared_ptr<ActionElement>(action);
    } catch (QString exception) {
        delete action;
        throw exception;
    }
}
std::shared_ptr<ActionElement> Parser::buildSetByFAction(QString formula_fragment)
{
    if (this->mode == PARSER_MODE_GLOBAL_RULES)
        throw (QString)"Команда SET_BY_F не может быть использована в глобальных правилах";
    formula_fragment = formula_fragment.simplified();

    if (!formula_fragment.contains(QRegularExpression("^SET_BY_F\\s.+$")))
        throw (QString)"Неправильный синтаксис команды SET_BY_F";
    ActionSetByF * action = new ActionSetByF(this->algorithm, this->field);
    try {
        int index_of_statements_number = 9; // подсчитано вручную.
        QString string_number = formula_fragment.right(formula_fragment.size() - index_of_statements_number);

        action->setStatementsNumber(this->buildValueFormula(string_number));
        return std::shared_ptr<ActionElement>(action);
    } catch (QString exception) {
        delete action;
        throw exception;
    }
}
std::shared_ptr<ActionElement> Parser::buildBanAction(QString formula_fragment)
{
    formula_fragment = formula_fragment.simplified();
    if (!formula_fragment.contains(QRegularExpression("^BAN\\s\\S+$")))
        throw (QString)"Неправильный синтаксис команды BAN";

    int index_of_functions_name = 4;
    QString string_name = formula_fragment.right(formula_fragment.size() - index_of_functions_name);
    if (!this->algorithm->hasEnvironsFunction(string_name))
        throw QString("Функция окружения с именем \"" + string_name + "\" не существует");

    ActionBan * action = new ActionBan(this->algorithm);
    action->setFunction(this->algorithm->getEnvironsFunction(string_name).get());
    return std::shared_ptr<ActionElement>(action);
}
std::shared_ptr<ActionElement> Parser::buildAllowAction(QString formula_fragment)
{
    formula_fragment = formula_fragment.simplified();
    if (!formula_fragment.contains(QRegularExpression("^ALLOW\\s\\S+$")))
        throw (QString)"Неправильный синтаксис команды ALLOW";

    int index_of_functions_name = 6;
    QString string_name = formula_fragment.right(formula_fragment.size() - index_of_functions_name);
    if (!this->algorithm->hasEnvironsFunction(string_name))
        throw QString("Функция окружения с именем \"" + string_name + "\" не существует");

    ActionAllow * action = new ActionAllow(this->algorithm);
    action->setFunction(this->algorithm->getEnvironsFunction(string_name).get());
    return std::shared_ptr<ActionElement>(action);
}
std::shared_ptr<ValueElement> Parser::identityFunctionReturningCell(QString formula_fragment)
{
    formula_fragment = formula_fragment.simplified();
    if (!formula_fragment.contains(QRegularExpression("^\\S+$")))
        throw QString("Идентификатор " + formula_fragment + " не может состоять из более чем одного слова. Ожидается функция окружения или CURRENT_CELL");

    if (formula_fragment == "CURRENT_CELL")
        return std::shared_ptr<ValueElement>(new FunctionCurrentCell(this->field));
    bool have_found;
    std::shared_ptr<ValueElement> func = this->identityCellFunction(formula_fragment, have_found);
    if (have_found)
        return func;
    else
        throw QString("Идентификатор " + formula_fragment + " не опознан");
}
