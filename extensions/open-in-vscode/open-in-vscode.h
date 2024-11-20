#include <nautilus-extension.h>


typedef struct {
  GObject parent_slot;
} OpenInVSCodeExtension;

typedef struct {
  GObjectClass parent_slot;
} OpenInVSCodeExtensionClass;

void OpenInVSCodeMenuProviderInterfaceInit(
  gpointer interfacePointer,
  gpointer // interfaceData
);
