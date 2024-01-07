

#include <CEGUIRefPtr.h>
#include <assert.h>

CEGUI::Referenced::~Referenced()
{
  assert(d_refCount == 0);
}
