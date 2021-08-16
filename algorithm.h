#ifndef ALGORITHM_H
#define ALGORITHM_H
#include<map>
#include<valuevariable.h>
#include<logicvariable.h>
#include<statement.h>
#include <memory>
#include "functioncell.h"
#include <vector>
#include "rule.h"
#include "vector"
#include "wavefunction.h"
class FieldDistributor;
//Переменные могут быть как Global & value, так и global & logic. GlobalVariable значит global & value, а GlobalLogicVariable -
//global & logic.
class Algorithm
{
public:
    Algorithm(FieldDistributor * field, bool create_empty);
    ~Algorithm();
    //не выполняет проверку на наличие переменной
    void addLogicVariable(QString name, bool is_global, QString sformula, std::shared_ptr<LogicElement> formula);
    //не выполняет проверку на наличие переменной
    void addValueVariable(QString name, bool is_global, QString sformula, std::shared_ptr<ValueElement> formula);
    //бросает исключение, если состояние с данным именем или номером существует
    void addStatement(QString name, int number, bool is_given_by_color, QColor color, QPixmap sprite);
    void addRule(Rule & rule);
    void addEnvironsFunction(QString name, int X, int Y, bool is_allowed);

    void deleteVariable(QString name);
    void deleteStatement(QString name);
    void deleteStatement(int number);
    void deleteRule(int number);
    void deleteEnvironsFunction(QString name);

    bool hasIterativeVariable(QString name);
    bool hasGlobalVariable(QString name);
    bool hasLogicVariable(QString name);
    bool hasValueVariable(QString name);
    bool hasEnvironsFunction(QString name);
    bool hasGlobalLogicVariable(QString name);
    bool hasStatement(QString name);
    bool hasStatement(int number);
    //создавать функцию hasRule(int number) не требуется, т. к. пользователь и сторонние классы никак не взаимодействуют с
    //номером правила, а данный класс гарантирует его уникальность

    const std::map<QString, std::shared_ptr<LogicVariable>> & getLogicVariablesList();
    const std::map<QString, std::shared_ptr<ValueVariable>> & getValueVariablesList();
    const std::map<QString, std::shared_ptr<ValueVariable>> & getGlobalVariablesList();
    const std::map<QString, std::shared_ptr<LogicVariable>> & getGlobalLogicVariablesList();
    const std::map<QString, std::shared_ptr<FunctionCell>> & getEnvironsFunctionsList();
    const std::map<int, Statement*> & getStatementsList();
    const std::map<int, std::shared_ptr<Rule>> & getRulesList();

    std::shared_ptr<LogicVariable> getLogicVariable(QString name);
    std::shared_ptr<ValueVariable> getValueVariable(QString name);
    std::shared_ptr<FunctionCell> getEnvironsFunction(QString name);
    //гарантировано, что такое состояние существует, иначе - возврат .end() контейнера
    Statement * getStatement(int number);
    Statement * getStatement(QString name);
    //опять же, должно быть гарантировано, что такой номер существует, иначе - вернет .end()
    std::shared_ptr<Rule> getRule(int number);
    //следующие функции изменяют лишь ключ элемента в хэш-таблице или перемещают его между таблицами
    //не проверяет наличие переменной. не затрагивает параметры самой переменной
    void changeLogicVariable(QString old_name, QString current_name, bool were_global, bool is_global);
    //не проверяет наличие переменной. не затрагивает параметры самой переменной
    void changeValueVariable(QString old_name, QString current_name, bool were_global, bool is_global);
    //не проверяет наличие состояния. не затрагивает параметры самого состояния
    void changeStatement(QString old_name, QString current_name, int old_number, int current_number);
    void changeEnvironsFunction(QString old_name, QString current_name);
    //функция changeRule не нужна, т. к. для rule используется один контейнер, и его идентификатор невозможно изменить
    void reBuildAllStringFormulas();
    void reCompileAllFormulas(FieldDistributor * field);
    //не меняют поле is_allowed самой функции
    void banEnvironsFunction(QString name);
    void allowEnvironsFunction(QString name);
    //переносит все данные в std::vector ради увеличения быстроты многократных проходов по ним
    void getReadyBeforeSimulating();
    //выполняет глобальные правила, считает глобальные переменные и т. д.
    void doGlobalPartOfIteration();
    //field, проходя по полю, вызывает этот метод для каждой клетки. данный метод считает локальные правила и переменные,
    //но не предоставляет никакой информации переменным и правилам
    void doLocalPartOfIteration();
    std::vector<std::shared_ptr<FunctionCell>> & getAllowedEnvironsFunctions();
    int getAmountOfAllowedEnvironsFunctions();
    int getAmountOfBannedEnvironsFunctions();
    bool isValid();
    void prepareAllStatementsToDraw(int width, int height);
    void addWaveFunction(WaveFunction * function);
    void eraseWaveFunction(int number);
    //работает непосредственно с переменными в векторе
    void amountOfThreadsChanged(int new_amount);
    void setStep(int step);
    int getStep();
private:
    //пока что они хранятся в мапах для того, чтобы было удобней работать в режиме создания автомата. При переключении
    //в режим симуляции, переменные, функции и правила перенесутся в std::vector ради увеличения быстродействия. Они хранятся в виде
    //указателей из-за ограничения мапа, позволяющего вызывать только const методы объектов, хранящихся в них, тогда как эти
    //данные необходимо изменять
    std::map<QString, std::shared_ptr<LogicVariable>> logic_variable_list;
    std::map<QString, std::shared_ptr<ValueVariable>> value_variables_list;
    std::map<QString, std::shared_ptr<ValueVariable>> global_variables_list;
    std::map<QString, std::shared_ptr<LogicVariable>> global_logic_variables_list;
    std::map<QString, std::shared_ptr<Statement>> statements_list;
    std::map<int, Statement*> statements_number_list;
    //умные указатели не нужны, и здесь, даже вредны, т. к. когда волновая функция перестает быть аргументом, она должна быть
    //моментально уничтожена.
    std::map<int, WaveFunction*> wave_functions_list;
    //в отличии
    std::map<QString, std::shared_ptr<FunctionCell>> environs_functions_list;
    std::map<QString, std::shared_ptr<FunctionCell>> allowed_environs_functions_list;

    //первый элемент в таблице указывает номер правила. у него нет физического значения в программе (пользователь с ним
    //никак не взаимодействует и не знает про него).
    std::map<int, std::shared_ptr<Rule>> rules_list;
    //номер, который получит следующее правило. если их не удалять, будет равен rules_list.size(), однако, при удалении
    //не уменьшается, тем самым убирая коллизии не делая никаких проверок.
    int rules_number = 0;
    int wave_functions_number = 0;

    int amount_of_local_rules = 0;
    int amount_of_global_rules = 0;

    std::vector<std::shared_ptr<LogicVariable>> logic_variables_vector;
    std::vector<std::shared_ptr<ValueVariable>> value_variables_vector;
    std::vector<std::shared_ptr<LogicVariable>> global_logic_variables_vector;
    std::vector<std::shared_ptr<ValueVariable>> global_value_variables_vector;
    std::vector<std::shared_ptr<Rule>> global_rules_vector;
    std::vector<std::shared_ptr<Rule>> local_rules_vector;
    //в отличии от остальных, данный вектор заполняется не единожды в начале симуляции, а перед каждой итерацией, потому что
    //список разрешенных функций может изменяться во время симуляции командами ALLOW и BAN. При этом, недопустимо хранить
    //их только в хеш-таблицах, так как изменения во время итерации должны сказываться только во время следующей итерации,
    //иначе нарушится одно из главных свойств клеточного автомата - порядок выполнения не влияет на результат. также,
    //вектор намного быстрее map-а, а волновой алгоритм требует частого прохода по контейнеру. Заполнение вектора находится
    //в функции doGlobalPartOfIteration()
    std::vector<std::shared_ptr<FunctionCell>> allowed_environs_functions_vector;
    //каждый раз в global-time итерации, элементы данного вектора должны получать сигнал о пересчитывании радиуса и функций
    //окружения. Поскольку, algorithm не управлят временью жизни данных функций, умные указатели не используются.
    std::vector<WaveFunction*> wave_functions_vector;
    void generateStandartEnvironsFunctionsKit();
    void generateStandartStatementsKit();
    FieldDistributor * field;
    bool has_environs_changed = true;
    int step;
};

#endif // ALGORITHM_H
