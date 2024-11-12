#include "open-in-vscode.h"

#include <nautilus-extension.h>
#include <stdio.h>


static GType openInVSCodeExtensionType;


void nautilus_module_initialize(
  GTypeModule *module
)
{
  printf("Initializing OpenInVSCode\n");

  static const GTypeInfo typeInfo = {
    sizeof(OpenInVSCodeExtensionClass),
    (GBaseInitFunc)(NULL),
    (GBaseFinalizeFunc)(NULL),

    (GClassInitFunc)(NULL),
    (GClassFinalizeFunc)(NULL),
    (gconstpointer)(NULL),

    sizeof(OpenInVSCodeExtension),
    0,
    (GInstanceInitFunc)(NULL),

    (GTypeValueTable*)(NULL)
  };

  openInVSCodeExtensionType = g_type_module_register_type(
    module, G_TYPE_OBJECT,
    "OpenInVSCode", &typeInfo,
    (GTypeFlags)(0)
  );


  static const GInterfaceInfo menuProviderInterfaceInfo = {
    OpenInVSCodeMenuProviderInterfaceInit,
    (GInterfaceFinalizeFunc)(NULL),
    (gpointer)(NULL)
  };

  g_type_module_add_interface(
    module, openInVSCodeExtensionType, NAUTILUS_TYPE_MENU_PROVIDER,
    &menuProviderInterfaceInfo
  );
}

void nautilus_module_shutdown()
{
  printf("Shutting down OpenInVSCode\n");
}

void nautilus_module_list_types(
  const GType **types,
  int *num_types
)
{
  *types = &openInVSCodeExtensionType;
  *num_types = 1;
}
