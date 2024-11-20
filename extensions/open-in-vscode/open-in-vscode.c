#include "open-in-vscode.h"
#include "logging.h"
#include "utilities.h"

#include <nautilus-extension.h>
#include <gtk/gtk.h>

#include <assert.h>
#include <string.h>
#include <stdio.h>


#define COMMAND_DATA_FIELD    "OpenInVSCodeCommand"
#define DEFAULT_BUTTON_LABEL  "Open in VSCode"


void oivsc_launchVSCode(NautilusMenuItem *menuItem, gpointer window)
{
  log_trace("[ENTER] menuItem: %p window: %p\n", menuItem, window);

  if (!menuItem)
  {
    return;
  }

  const char *command = g_object_get_data(
    G_OBJECT(menuItem), COMMAND_DATA_FIELD
  );

  int exitCode = system(command);
  if (exitCode != 0)
  {
    GtkWidget *dialog = gtk_message_dialog_new(
      (GtkWindow*)(window),
      GTK_DIALOG_DESTROY_WITH_PARENT,
      GTK_MESSAGE_ERROR, GTK_BUTTONS_OK,
      "VSCode failed to open selected items.\nExit code: %d", exitCode
    );
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
  }
}

GList *oivsc_menuProviderAddItem(GtkWidget *window, char *command, const char *buttonLabel)
{
  log_trace("[ENTER] window: %p command: \"%s\" buttonLabel: \"%s\"\n", window, command, buttonLabel);

  if (!command) return NULL;

  NautilusMenuItem *menuItem = nautilus_menu_item_new(
    "OpenInVSCode::openFiles",
    buttonLabel,
    "Hello everynyan. OH MAH GAAAHD",
    NULL
  );
  g_object_set_data_full(
    (GObject*)(menuItem), COMMAND_DATA_FIELD,
    command, free
  );

	g_signal_connect(
    menuItem, "activate",
    G_CALLBACK(oivsc_launchVSCode),
    gtk_widget_get_toplevel(window)
  );

	return g_list_append(NULL, menuItem);
}

GList *oivsc_menuProviderGetSelectedItems(NautilusMenuProvider *provider, GtkWidget *window, GList *files)
{
  log_trace(
    "[ENTER] provider: %p window: %p files: %p\n",
    provider, window, files
  );

  if (files == NULL) return NULL;

  char *command = oivsc_makeBaseCommand();

  size_t nrOfDirs = 0ul;
  command = oivsc_selectByMimeType(files, "inode/directory", command, &nrOfDirs);
  size_t nrOfFiles = 0ul;
  command = oivsc_selectByMimeType(files, "text/*", command, &nrOfFiles);

  if (nrOfDirs == 0 && nrOfFiles == 0)
  {
    return NULL;
  }

  char buttonLabel[64];
  oivsc_makeButtonLabel(nrOfDirs, nrOfFiles, buttonLabel);

  return oivsc_menuProviderAddItem(window, command, buttonLabel);
}

GList *oivsc_menuProviderGetCurrentFolder(NautilusMenuProvider *provider, GtkWidget *window, NautilusFileInfo *currentFolder)
{
  log_trace(
    "[ENTER] provider: %p window: %p currentFolder: %p\n",
    provider, window, currentFolder
  );

  assert(currentFolder);

  char *command = oivsc_makeBaseCommand();

  char *absoluteDirPath = g_file_get_path(nautilus_file_info_get_location(currentFolder));
  if (!absoluteDirPath) return NULL;

  command = oivsc_addToCommand(command, absoluteDirPath);
  g_free(absoluteDirPath);

  return oivsc_menuProviderAddItem(window, command, DEFAULT_BUTTON_LABEL);
}

void oivsc_menuProviderInterfaceInit(gpointer interfacePointer, gpointer)
{
  log_trace("[ENTER] interfacePointer: %p\n", interfacePointer);

  NautilusMenuProviderInterface* interface = interfacePointer;
  interface->get_file_items = oivsc_menuProviderGetSelectedItems;
  interface->get_background_items = oivsc_menuProviderGetCurrentFolder;
}
