#ifndef COUNTERSAMOUNT_H
#define COUNTERSAMOUNT_H
#include <map>
#include <set>
#include <memory>
#include <QString>
#include <atomic>
class Statement;
class CountersAmount
{
private:
    typedef std::unique_ptr<std::atomic_int> amount;
public:
    CountersAmount(std::set<QString> configs_names);
    void addElement(QString name);
    void renameElement(QString old_name, QString new_name);
    void eraseElement(QString name);
    void setCurrent(QString name);
    std::atomic_int* getCurrent();
private:
    //многопоточный доступ к карте не планируется
    std::map<QString, amount> amounts;
    std::atomic_int* current;
};

#endif // COUNTERSAMOUNT_H
