
#include "Input.h"
#include "ApplicationCentral.h"


// ----------------------------------------------------------------------------
// The buffer size for the direct input device
// ----------------------------------------------------------------------------
#define DI_BUFFER_SIZE 256


// ----------------------------------------------------------------------------
// Name: BaseInput::BaseInput
// Desc: Constructor
// ----------------------------------------------------------------------------
BaseInput::BaseInput()
{
  REF_COUNT_CTOR(BaseInput);
} // BaseInput


// ----------------------------------------------------------------------------
// Name: BaseInput::~BaseInput
// Desc: Destructor
// ----------------------------------------------------------------------------
BaseInput::~BaseInput()
{
  REF_COUNT_DTOR(BaseInput);
} // ~BaseInput


// -- EOF

