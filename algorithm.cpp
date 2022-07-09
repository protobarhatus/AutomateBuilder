#include "algorithm.h"
#include "mydeleter.h"
#include "statementscounter.h"
Algorithm::Algorithm(FieldDistributor * ifield, bool create_empty)
{
    this->field = ifield;
    if (!create_empty)
    {
        this->generateStandartEnvironsFunctionsKit();
        this->generateStandartStatementsKit();
    }
}
Algorithm::~Algorithm()
{
    for (auto &it : this->allowed_environs_functions_list)
        it.second.reset();
    for (auto &it : this->allowed_environs_functions_vector)
        it.reset();
    for (auto &it : this->environs_functions_list)
         it.second.reset();
    for (auto &it : this->global_logic_variables_list)
        it.second.reset();
    for (auto &it : this->global_logic_variables_vector)
        it.reset();
    for (auto &it : this->global_rules_vector)
        it.reset();
    for (auto &it : this->global_value_variables_vector)
        it.reset();
    for (auto &it : this->global_variables_list)
        it.second.reset();
    for (auto &it : this->local_rules_vector)
        it.reset();
    for (auto &it : this->logic_variables_list)
        it.second.reset();
    for (auto &it : this->logic_variables_vector)
        it.reset();
    for (auto &it : this->rules_list)
        it.second.reset();
    for (auto &it : this->statements_list)
        it.second.reset();
    for (auto &it : this->value_variables_list)
        it.second.reset();
    for (auto &it : this->value_variables_vector)
        it.reset();
}
void Algorithm::addLogicVariable(QString name, bool is_global, QString sformula, std::shared_ptr<LogicElement> formula)
{
    LogicVariable * variable = new LogicVariable(name, sformula, formula);
    variable->setGlobality(is_global);
    if (is_global)
    {

        this->global_logic_variables_list.insert(std::pair<QString,
                                     std::shared_ptr<LogicVariable>>(name, std::shared_ptr<LogicVariable>(variable)));
    }
    else
    {
        this->logic_variables_list.insert(std::pair<QString,
                                                 std::shared_ptr<LogicVariable>>(name, std::shared_ptr<LogicVariable>(variable)));
    }
}
void Algorithm::addValueVariable(QString name, bool is_global, QString sformula, std::shared_ptr<ValueElement> formula)
{

    ValueVariable * variable = new ValueVariable(name, sformula, formula);
    variable->setGlobality(is_global);
    if (is_global)
    {
        this->global_variables_list.insert(std::pair<QString, std::shared_ptr<ValueVariable>>(name,
                                                              std::shared_ptr<ValueVariable>(variable)));
    }
    else
    {
        this->value_variables_list.insert(std::pair<QString, std::shared_ptr<ValueVariable>>(name,
                                                             std::shared_ptr<ValueVariable>(variable)));
    }

}
void Algorithm::addStatement(QString name, int number, bool is_given_by_color, QColor color, QPixmap sprite)
{
    bool is_name_free =
            this->statements_list.find(name) ==
            this->statements_list.end();
    if (!is_name_free)
    {
        throw (QString)"Statement with this name is \
        already exists";
    }
    bool is_number_free = this->statements_number_list.find(number) ==
            this->statements_number_list.end();
    if (!is_number_free)
    {
        throw (QString)"Statement with this number is already \
        exists";
    }
    Statement * statement = new Statement(name, number);
    if (is_given_by_color)
    {
        statement->setColor(color);
    }
    else
    {
        statement->setSprite(sprite);
    }
    this->statements_list.insert(
                std::pair<QString, std::shared_ptr<Statement>>(name, std::shared_ptr<Statement>(statement)));
    this->statements_number_list.insert(
                std::pair<int, Statement*>(number, statement));
}
void Algorithm::addEnvironsFunction(QString name, int X, int Y, bool is_allowed)
{
    FunctionCell * function = new FunctionCell(name, X, Y, is_allowed, this->field);
    this->environs_functions_list.insert(std::pair<QString, std::shared_ptr<FunctionCell>>(name,
          std::shared_ptr<FunctionCell>(function)));
    if (is_allowed)
    {
        this->allowEnvironsFunction(name);
    }
}
bool Algorithm::hasIterativeVariable(QString name)
{

        return this->logic_variables_list.find(name) != this->logic_variables_list.end() ||
            this->value_variables_list.find(name) != this->value_variables_list.end();

}
bool Algorithm::hasGlobalVariable(QString name)
{
    return this->global_variables_list.find(name) !=  this->global_variables_list.end() ||
            this->global_logic_variables_list.find(name) != this->global_logic_variables_list.end();
}
const std::map<QString, std::shared_ptr<LogicVariable>> & Algorithm::getLogicVariablesList()
{
    return this->logic_variables_list;
}
const std::map<QString, std::shared_ptr<ValueVariable>> & Algorithm::getValueVariablesList()
{
    return this->value_variables_list;
}
const std::map<QString, std::shared_ptr<ValueVariable>> & Algorithm::getGlobalVariablesList()
{
    return this->global_variables_list;
}
const std::map<QString, std::shared_ptr<LogicVariable>> & Algorithm::getGlobalLogicVariablesList()
{
    return this->global_logic_variables_list;
}
bool Algorithm::hasLogicVariable(QString name)
{
    return this->logic_variables_list.find(name) != this->logic_variables_list.end() ||
            this->global_logic_variables_list.find(name) != this->global_logic_variables_list.end();
}
bool Algorithm::hasValueVariable(QString name)
{
    return this->value_variables_list.find(name) != this->value_variables_list.end() ||
            this->global_variables_list.find(name) != this->global_variables_list.end();
}
std::shared_ptr<LogicVariable> Algorithm::getLogicVariable(QString name)
{
    std::map<QString, std::shared_ptr<LogicVariable>>::iterator it;
    std::shared_ptr<LogicVariable> ptr;

    if ((it = this->logic_variables_list.find(name)) != this->logic_variables_list.end())
    {
        /*
        ptr = std::shared_ptr<LogicVariable>(&it->second, MyDeleter());
        std::get_deleter<MyDeleter>(ptr)->setDelete(false);
        return ptr;*/
        return it->second;
    }
    if ((it = this->global_logic_variables_list.find(name)) != this->global_logic_variables_list.end())
    {
        return it->second;
    }
    throw QString("Value variable with name " + name + " doesn't exist");
}
std::shared_ptr<ValueVariable> Algorithm::getValueVariable(QString name)
{
    std::map<QString, std::shared_ptr<ValueVariable>>::iterator it;
    std::shared_ptr<ValueVariable> ptr;

    if ((it = this->value_variables_list.find(name)) != this->value_variables_list.end())
    {
        return it->second;
    }
    if ((it = this->global_variables_list.find(name)) != this->global_variables_list.end())
    {
        return it->second;
    }
    throw QString("Value variable with name " + name + " doesn't exist");
}
void Algorithm::generateStandartEnvironsFunctionsKit()
{
    std::shared_ptr<FunctionCell> U(new FunctionCell("U", 0, -1, true, this->field));
    std::shared_ptr<FunctionCell> UR(new FunctionCell("UR", 1, -1, true, this->field));
    std::shared_ptr<FunctionCell> R(new FunctionCell("R", 1, 0, true, this->field));
    std::shared_ptr<FunctionCell> BR(new FunctionCell("BR", 1, 1, true, this->field));
    std::shared_ptr<FunctionCell> B(new FunctionCell("B", 0, 1, true, this->field));
    std::shared_ptr<FunctionCell> BL(new FunctionCell("BL", -1, 1, true, this->field));
    std::shared_ptr<FunctionCell> L(new FunctionCell("L", -1, 0, true, this->field));
    std::shared_ptr<FunctionCell> UL(new FunctionCell("UL", -1, -1, true, this->field));

    this->environs_functions_list.insert(std::pair<QString, std::shared_ptr<FunctionCell>>("U", U));
    this->environs_functions_list.insert(std::pair<QString, std::shared_ptr<FunctionCell>>("UR", UR));
    this->environs_functions_list.insert(std::pair<QString, std::shared_ptr<FunctionCell>>("R", R));
    this->environs_functions_list.insert(std::pair<QString, std::shared_ptr<FunctionCell>>("BR", BR));
    this->environs_functions_list.insert(std::pair<QString, std::shared_ptr<FunctionCell>>("B", B));
    this->environs_functions_list.insert(std::pair<QString, std::shared_ptr<FunctionCell>>("BL", BL));
    this->environs_functions_list.insert(std::pair<QString, std::shared_ptr<FunctionCell>>("L", L));
    this->environs_functions_list.insert(std::pair<QString, std::shared_ptr<FunctionCell>>("UL", UL));

    this->allowed_environs_functions_list.insert(std::pair<QString, std::shared_ptr<FunctionCell>>("U", U));
    this->allowed_environs_functions_list.insert(std::pair<QString, std::shared_ptr<FunctionCell>>("UR", UR));
    this->allowed_environs_functions_list.insert(std::pair<QString, std::shared_ptr<FunctionCell>>("R", R));
    this->allowed_environs_functions_list.insert(std::pair<QString, std::shared_ptr<FunctionCell>>("BR", BR));
    this->allowed_environs_functions_list.insert(std::pair<QString, std::shared_ptr<FunctionCell>>("B", B));
    this->allowed_environs_functions_list.insert(std::pair<QString, std::shared_ptr<FunctionCell>>("BL", BL));
    this->allowed_environs_functions_list.insert(std::pair<QString, std::shared_ptr<FunctionCell>>("L", L));
    this->allowed_environs_functions_list.insert(std::pair<QString, std::shared_ptr<FunctionCell>>("UL", UL));
}
bool Algorithm::hasEnvironsFunction(QString name)
{
    return this->environs_functions_list.find(name) != this->environs_functions_list.end();
}
const std::map<QString, std::shared_ptr<FunctionCell>> & Algorithm::getEnvironsFunctionsList()
{
    return this->environs_functions_list;
}
std::shared_ptr<FunctionCell> Algorithm::getEnvironsFunction(QString name)
{
    std::map<QString, std::shared_ptr<FunctionCell>>::iterator it;
    std::shared_ptr<FunctionCell> ptr;
    if (this->hasEnvironsFunction(name))
    {
        it = this->environs_functions_list.find(name);
        return it->second;
    };
    throw "Environs function with name " + name + " doesn't exist";
}
void Algorithm::changeLogicVariable(QString old_name, QString current_name, bool were_global, bool is_global)
{
    std::map<QString, std::shared_ptr<LogicVariable>>::iterator it;
    std::shared_ptr<LogicVariable> var;
    if (were_global)
    {
        it = this->global_logic_variables_list.find(old_name);
        var = it->second;
        this->global_logic_variables_list.erase(it);

    }
    else
    {
        it = this->logic_variables_list.find(old_name);
        var = it->second;
        this->logic_variables_list.erase(it);
    }
    if (is_global)
    {
        this->global_logic_variables_list.insert(std::pair<QString, std::shared_ptr<LogicVariable>>(current_name, var));
    }
    else
    {
        this->logic_variables_list.insert(std::pair<QString, std::shared_ptr<LogicVariable>>(current_name, var));
    }
}
void Algorithm::changeValueVariable(QString old_name, QString current_name, bool were_global, bool is_global)
{
    std::map<QString, std::shared_ptr<ValueVariable>>::iterator it;
    std::shared_ptr<ValueVariable> var;
    if (were_global)
    {
        it = this->global_variables_list.find(old_name);
        var = it->second;
        this->global_variables_list.erase(it);

    }
    else
    {
        it = this->value_variables_list.find(old_name);
        var = it->second;
        this->value_variables_list.erase(it);
    }
    if (is_global)
    {
        this->global_variables_list.insert(std::pair<QString, std::shared_ptr<ValueVariable>>(current_name, var));
    }
    else
    {
        this->value_variables_list.insert(std::pair<QString, std::shared_ptr<ValueVariable>>(current_name, var));
    }
}

void Algorithm::reBuildAllStringFormulas()
{
    for (auto &it : this->logic_variables_list)
    {
        it.second->buildStringFormula();
    }
    for (auto &it : this->value_variables_list)
    {
        it.second->buildStringFormula();
    }
    for (auto &it : this->global_logic_variables_list)
    {
        it.second->buildStringFormula();
    }
    for (auto &it : this->global_variables_list)
    {
        it.second->buildStringFormula();
    }
    for (auto &it : this->rules_list)
    {
        it.second->buildStringFormula();
    }
}

void Algorithm::reCompileAllFormulas(FieldDistributor * field)
{
    for (auto &it : this->logic_variables_list)
    {
        it.second->reCompileFormula(this, field);
    }
    for (auto &it : this->value_variables_list)
    {
        it.second->reCompileFormula(this, field);
    }
    for (auto &it : this->global_logic_variables_list)
    {
        it.second->reCompileFormula(this, field);
    }
    for (auto &it : this->global_variables_list)
    {
        it.second->reCompileFormula(this, field);
    }
    for (auto &it : this->rules_list)
    {
        it.second->reCompileFormula(this, field);
    }
}
void Algorithm::deleteVariable(QString name)
{
    auto l_it = this->logic_variables_list.find(name);
    if (l_it != this->logic_variables_list.end())
    {
        this->logic_variables_list.erase(l_it);
        return;
    }
    l_it = this->global_logic_variables_list.find(name);
    if (l_it != this->global_logic_variables_list.end())
    {
        this->global_logic_variables_list.erase(l_it);
        return;
    }

    auto v_it = this->value_variables_list.find(name);
    if (v_it != this->value_variables_list.end())
    {
        this->value_variables_list.erase(v_it);
        return;
    }
    v_it = this->global_variables_list.find(name);
    if (v_it != this->global_variables_list.end())
    {
        this->global_variables_list.erase(v_it);
        return;
    }
}
bool Algorithm::hasStatement(int number)
{
    return this->statements_number_list.find(number) != this->statements_number_list.end();
}
bool Algorithm::hasStatement(QString name)
{
    return this->statements_list.find(name) != this->statements_list.end();
}
const std::map<int, Statement*> & Algorithm::getStatementsList()
{
    return this->statements_number_list;
}
Statement * Algorithm::getStatement(int number)
{
    auto it = this->statements_number_list.find(number);
    if (it == this->statements_number_list.end())
        return nullptr;
    else
        return it->second;
}
Statement * Algorithm::getStatement(QString name)
{
    return this->statements_list.find(name)->second.get();
}
void Algorithm::changeStatement(QString old_name, QString current_name, int old_number, int current_number)
{
    if (old_name != current_name)
    {
        auto it = this->statements_list.find(old_name);
        std::shared_ptr<Statement> statement = it->second;
        this->statements_list.erase(it);
        this->statements_list.insert(std::pair<QString, std::shared_ptr<Statement>>(current_name, statement));
    }
    if (old_number != current_number)
    {
        auto it = this->statements_number_list.find(old_number);
        Statement * statement = it->second;
        this->statements_number_list.erase(it);
        this->statements_number_list.insert(std::pair<int, Statement*>(current_number, statement));
    }
}
void Algorithm::changeEnvironsFunction(QString old_name, QString current_name)
{
    if (old_name != current_name)
    {
        auto it = this->environs_functions_list.find(old_name);
        std::shared_ptr<FunctionCell> function = it->second;
        this->environs_functions_list.erase(it);
        this->environs_functions_list.insert(std::pair<QString, std::shared_ptr<FunctionCell>>(current_name, function));

        auto it2 = this->allowed_environs_functions_list.find(old_name);
        if (it2 != this->allowed_environs_functions_list.end())
        {
            this->allowed_environs_functions_list.erase(it2);
            this->allowed_environs_functions_list.insert(std::pair<QString, std::shared_ptr<FunctionCell>>(current_name, function));
        }
    }
}
void Algorithm::deleteStatement(QString name)
{
    auto it = this->statements_list.find(name);
    this->statements_number_list.erase(this->statements_number_list.find(it->second->getNumber()));
    this->statements_list.erase(it);
}
void Algorithm::deleteStatement(int number)
{
    auto it = this->statements_number_list.find(number);
    this->statements_list.erase(this->statements_list.find(it->second->getName()));
    this->statements_number_list.erase(it);
}
void Algorithm::deleteEnvironsFunction(QString name)
{
    this->environs_functions_list.erase(this->environs_functions_list.find(name));
    auto it = this->allowed_environs_functions_list.find(name);
    if (it != this->allowed_environs_functions_list.end())
    {
        this->allowed_environs_functions_list.erase(it);
    }
}
void Algorithm::banEnvironsFunction(QString name)
{
    auto it = this->allowed_environs_functions_list.find(name);
    if (it == this->allowed_environs_functions_list.end())
        return;
    this->allowed_environs_functions_list.erase(it);
    this->has_environs_changed = true;
}
void Algorithm::allowEnvironsFunction(QString name)
{
    auto it = this->environs_functions_list.find(name);

    this->allowed_environs_functions_list.insert(std::pair<QString, std::shared_ptr<FunctionCell>>(it->first, it->second));
    this->has_environs_changed = true;
}
void Algorithm::addRule(Rule & rule)
{
    std::shared_ptr<Rule> newrule(new Rule(rule));
    this->rules_list.insert(std::pair<int, std::shared_ptr<Rule>>(this->rules_number, newrule));
    ++this->rules_number;
}
void Algorithm::deleteRule(int number)
{
    auto it = this->rules_list.find(number);
    this->rules_list.erase(it);
}
const std::map<int, std::shared_ptr<Rule>> & Algorithm::getRulesList()
{
    return this->rules_list;
}
std::shared_ptr<Rule> Algorithm::getRule(int number)
{
    return this->rules_list.find(number)->second;
}

void Algorithm::getReadyBeforeSimulating()
{

    this->logic_variables_vector.clear();
    for (auto &it : this->logic_variables_list)
    {
        this->logic_variables_vector.push_back(it.second);
    }
    this->value_variables_vector.clear();
    for (auto &it : this->value_variables_list)
    {
        this->value_variables_vector.push_back(it.second);
    }
    this->global_logic_variables_vector.clear();
    for (auto &it : this->global_logic_variables_list)
    {
        this->global_logic_variables_vector.push_back(it.second);
    }
    this->global_value_variables_vector.clear();
    for (auto &it : this->global_variables_list)
    {
        this->global_value_variables_vector.push_back(it.second);
    }
    this->wave_functions_vector.clear();
    for (auto &it : this->wave_functions_list)
    {
        this->wave_functions_vector.push_back(it.second);
    }
    this->global_rules_vector.clear();
    for (auto &it : this->rules_list)
    {

        if (it.second->isGlobal())
            this->global_rules_vector.push_back(it.second);
        else
            this->local_rules_vector.push_back(it.second);
    }
    for (auto &it : this->environs_functions_list)
    {
        if (it.second->isAllowed() && this->allowed_environs_functions_list.find(it.first) ==
                this->allowed_environs_functions_list.end())
            this->allowEnvironsFunction(it.first);
        else if (!it.second->isAllowed() && this->allowed_environs_functions_list.find(it.first) !=
                this->allowed_environs_functions_list.end())
            this->banEnvironsFunction(it.first);
    }

}
void Algorithm::doGlobalPartOfIteration()
{
    for (auto &it : this->global_logic_variables_vector)
    {
        it->count();
    }
    for (auto &it : this->global_value_variables_vector)
    {
        it->count();
    }
    for (auto &it : this->global_rules_vector)
    {
        it->complite();
    }
    if (this->has_environs_changed)
    {
        this->allowed_environs_functions_vector.clear();
        for (auto &it : this->allowed_environs_functions_list)
        {
            this->allowed_environs_functions_vector.push_back(it.second);
        }
    }
    for (auto &it : this->wave_functions_vector)
    {
        if (this->has_environs_changed)
            it->environChanged();
        it->calculateRadius();
    }
    this->has_environs_changed = false;
}
void Algorithm::doLocalPartOfIteration()
{
    for (auto &it : this->logic_variables_vector)
    {
        it->count();
    }
    for (auto &it : this->value_variables_vector)
    {
        it->count();
    }
    for (auto &it : this->local_rules_vector)
    {
        it->complite();
    }
}
std::vector<std::shared_ptr<FunctionCell>> & Algorithm::getAllowedEnvironsFunctions()
{
    return this->allowed_environs_functions_vector;
}
int Algorithm::getAmountOfAllowedEnvironsFunctions()
{
    return this->allowed_environs_functions_vector.size();
}
int Algorithm::getAmountOfBannedEnvironsFunctions()
{
    return this->environs_functions_list.size() - this->allowed_environs_functions_vector.size();
}
bool Algorithm::isValid()
{
    for (auto &it : this->logic_variables_list)
    {
        if (!it.second->isFormulaValid())
            return false;
    }
    for (auto &it : this->value_variables_list)
    {
        if (!it.second->isFormulaValid())
            return false;
    }
    for (auto &it : this->global_logic_variables_list)
    {
        if (!it.second->isFormulaValid())
            return false;
    }
    for (auto &it : this->global_variables_list)
    {
        if (!it.second->isFormulaValid())
            return false;
    }
    for (auto &it : this->rules_list)
    {
        if (!it.second->isFormulaValid())
            return false;
    }
    return true;
}
void Algorithm::generateStandartStatementsKit()
{
    QColor transparent;
    transparent.setAlpha(0);
    transparent.setRed(0);
    transparent.setBlue(0);
    transparent.setGreen(0);
    this->addStatement("empty", 0, true, transparent, QPixmap());
}
void Algorithm::prepareAllStatementsToDraw(int width, int height)
{
    for (auto &it : this->statements_number_list)
    {
        it.second->getReadyToDrawing(width, height);
    }
}
void Algorithm::addWaveFunction(WaveFunction * function)
{

    this->wave_functions_list.insert(std::pair<int, WaveFunction*>(this->wave_functions_number, function));
    function->setItsNumber(this->wave_functions_number);
    ++this->wave_functions_number;
}
void Algorithm::eraseWaveFunction(int number)
{
    this->wave_functions_list.erase(this->wave_functions_list.find(number));
}
void Algorithm::amountOfThreadsChanged(int new_amount)
{
    for (auto &it : this->logic_variables_list)
    {
        it.second->amountOfThreadsChanged(new_amount);
    }
    for (auto &it : this->value_variables_list)
    {
        it.second->amountOfThreadsChanged(new_amount);
    }
}
void Algorithm::setStep(int s)
{
    this->step = s;
}
int Algorithm::getStep()
{
    return this->step;
}
