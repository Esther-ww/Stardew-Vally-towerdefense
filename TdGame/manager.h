#ifndef _MANAGER_H
#define _MANSGER_H

template <typename T>
//单例模式
class Manager {
public:
	static Manager<T>* instance() {
		if (!manager)
			manager = new T();
		return manager;
	}
	
private:
	static Manager* manager;//静态指针 manager：用来保存 Manager 的唯一实例。

	
protected:
	Manager() = default;//防止外部代码通过 new Manager() 创建多个 Manager 实例。
	Manager(const Manager&) = delete;
	Manager& operator=(const Manager&) = delete;
	~Manager() = default;
 };

template <typename T>
Manager<T>* Manager<T>::manager = nullptr;

#endif 