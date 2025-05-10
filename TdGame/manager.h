#ifndef _MANAGER_H
#define _MANSGER_H

template <typename T>
//����ģʽ
class Manager {
public:
	static Manager<T>* instance() {
		if (!manager)
			manager = new T();
		return manager;
	}
	
private:
	static Manager* manager;//��ָ̬�� manager���������� Manager ��Ψһʵ����

	
protected:
	Manager() = default;//��ֹ�ⲿ����ͨ�� new Manager() ������� Manager ʵ����
	Manager(const Manager&) = delete;
	Manager& operator=(const Manager&) = delete;
	~Manager() = default;
 };

template <typename T>
Manager<T>* Manager<T>::manager = nullptr;

#endif 