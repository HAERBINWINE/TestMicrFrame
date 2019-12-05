#ifndef REGISTERCLASS_H
#define REGISTERCLASS_H
#include "factory.h"

//该宏定义实现了一个动态类的创建，
//   ## 合并操作符 将操作两边的字符合并成一个新的标识符，合并后新的标识符不是字符串
//   #  构串操作符 它将实参的字符序列（而不是实参代表的值）转换成字符串常量, 转换后是一个字符串
//   class className##Helper : 如className是FileItem，程序将会生成一个FileItemHelper类。
//   构造函数 : 调用工厂类的注册函数，实现了类名和生成类实例函数的绑定
//   CreatObjFunc函数 : 生成一个类实例   比如className是FileItem,则new FileItem.  返回void *减少了代码的耦合

#define REGISTERCLASS(className,classparameters) \
class className##Helper { \
public: \
    className##Helper() \
    { \
        ClassFactory::instance()->RegisterItem(#className, className##Helper::CreatObjFunc,(classparameters)); \
    } \
    static void* CreatObjFunc() \
    { \
        return new className; \
    } \
}; \
className##Helper className##helper;
//定义了一个成员变量，如FileItemHelper类的成员变量 FileItemhelper
#endif // REGISTERCLASS_H
