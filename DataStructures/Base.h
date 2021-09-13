#ifndef BASE_DATA
#define BASE_DATA

template<typename T>
class Base
{
private:
  T data;

public:
  T GetData() { return this->data; }
  void SetData(T data) { this->data = data; }
};

#endif
