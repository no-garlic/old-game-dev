

#include "Object.h"


IMPLEMENT_TYPE_INFO(Object);


ObjectGlobal *ObjectGlobal::s_pInstance = NULL;


Object::Object()
{
  m_Id = ObjectManager.Register(this);
}


Object::~Object()
{
  ObjectManager.UnRegister(m_Id);
}


// -- EOF

