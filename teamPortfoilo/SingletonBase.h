#pragma once
template<class T>
class SingletonBase
{
	/*
	������ ����(�̱���)
	- ������Ʈ ��ü���� �Ѱ��� �����ؾ��ϴ� ��ü�� Ŭ����, 
	�Ǵ� ������Ʈ ��ü���� �����ϴ� Ŭ������ ������ �� �ִ� ����
	*/

protected:
	//�̱��� �ν��Ͻ� ����
	static T* singleton;

	SingletonBase() {}
	~SingletonBase() {}

public:
	//�̱��� ��������
	static T* getSingleton(void);
	//�̱��� �޸𸮿��� ����
	void releaseSingleton(void);
};

 template<typename T>
 T* SingletonBase<T>::singleton = 0;

 //�̱��� ��������
 template<typename T>
 T* SingletonBase<T>::getSingleton(void)
 {
	 //�̱����� ������ ���� ����
	 if (!singleton) singleton = new T; //�����Ҵ� ����

	 return singleton;
 }

 //�̱��� �޸� ����
 template<typename T>
 void SingletonBase<T>::releaseSingleton(void)
 {
	 //�̱����� �ִٸ� �޸𸮿��� ����
	 if (singleton)  // �ٷ� ���������� ������ ���ǽ� �Ἥ �ѹ� �� ����� ����� !
	 {
		 delete singleton;
		 singleton = 0;
	 }
 }