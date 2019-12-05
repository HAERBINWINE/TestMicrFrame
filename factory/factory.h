#ifndef FACTORY_H
#define FACTORY_H

#include "singleton.h"
#include <map>


class Item;

//定义一个返回值为void* 参数为null的函数指针
typedef void* (*ItemObject)();

struct ItemObjectClass
{
    explicit ItemObjectClass(ItemObject item) : itemObject(item) {}
    ItemObject itemObject;
};


//作为所有类的工厂，如有需要某一类型的类的工厂可以继承此类
class ClassFactory : public Singleton<ClassFactory>
{
public:
    ClassFactory();
    ~ClassFactory();


    //************************************
    // Method:    CreateItem 创建类，
    // FullName:  ClassFactory::CreateItem
    // Access:    public
    // Returns:   void *
    // Qualifier:
    // Parameter: string className
    //************************************
    void * CreateItem(QString className);    // 返回void *减少了代码的耦合

    //
    //************************************
    // Method:    RegisterItem
    // FullName:  ClassFactory::RegisterItem
    // Access:    public
    // Returns:   void
    // Qualifier:
    // Parameter: const string & className 要创建类的类名
    // Parameter: ItemObject item 函数指针，该指针在宏REGISTER_CLASS中被绑定
    //************************************
    void RegisterItem(const QString& className, ItemObject item,QStringList);
    std::map<QString,QStringList> ReturnClassNames() const;

private:
    //缓存类名和生成类实例函数指针的map，ItemObject实际上是一个函数指针
    std::map<QString, ItemObjectClass *> objectItems;
    std::map<QString,QStringList> classNameSets;
};
#endif // FACTORY_H


