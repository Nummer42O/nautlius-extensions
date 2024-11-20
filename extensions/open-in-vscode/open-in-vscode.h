#ifndef OPEN_IN_VSCODE_H
#define OPEN_IN_VSCODE_H

#include <nautilus-extension.h>


typedef struct {
  GObject parent_slot;
} OpenInVSCodeExtension;

typedef struct {
  GObjectClass parent_slot;
} OpenInVSCodeExtensionClass;

void oivsc_menuProviderInterfaceInit(
  gpointer interfacePointer,
  gpointer // interfaceData
);

#endif // !defined(OPEN_IN_VSCODE_H)
