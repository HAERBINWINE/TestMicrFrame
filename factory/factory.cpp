#include "factory.h"



ClassFactory::ClassFactory()
{
}


ClassFactory::~ClassFactory()
{
    for (auto it : objectItems)
    {
        if (it.second != nullptr)
        {
            delete it.second;
            it.second = nullptr;
        }
    }
    objectItems.clear();
    classNameSets.clear();
}


//返回void *减少了代码的耦合
void * ClassFactory::CreateItem(QString className)
{
    ItemObject constructor = nullptr;

    if (objectItems.find(className) != objectItems.end())
        constructor = objectItems.find(className)->second->itemObject;

    if (constructor == nullptr)
        return nullptr;

    // 调用函数指针指向的函数 调用REGISTER_CLASS中宏的绑定函数，也就是运行new className代码
    return (*constructor)();
}

//ItemObject相当于一个回掉函数
void ClassFactory::RegisterItem(const QString& className, ItemObject item,QStringList classparameters)
{
    std::map<QString, ItemObjectClass *>::iterator it = objectItems.find(className);
    if (it != objectItems.end())
        objectItems[className]->itemObject = item;
    else
        classNameSets.insert(std::make_pair(className,classparameters));
        objectItems.insert(std::make_pair(className, new ItemObjectClass(item)));
}

std::map<QString,QStringList>  ClassFactory::ReturnClassNames() const
{
    return classNameSets;
}
