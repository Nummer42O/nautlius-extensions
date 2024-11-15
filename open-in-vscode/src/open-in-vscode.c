#include "open-in-vscode.h"

#include <nautilus-extension.h>
#include <gtk/gtk.h>


#include <assert.h>
#include <string.h>
#include <stdio.h>


#define COMMAND_DATA_FIELD    "OpenInVSCodeCommand"
#define DEFAULT_BUTTON_LABEL  "Open in VSCode"


void openInVSCodeOpenFiles(NautilusMenuItem *menuItem, gpointer window)
{
  if (!menuItem)
  {
    return;
  }

  const char *command = g_object_get_data(
    G_OBJECT(menuItem), COMMAND_DATA_FIELD
  );
  printf("command: %s\n", command);

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

GList *menuProviderAddItem(GtkWidget *window, char *command, const char *buttonLabel)
{
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
    G_CALLBACK(openInVSCodeOpenFiles),
    gtk_widget_get_toplevel(window)
  );

	return g_list_append(NULL, menuItem);
}

char *makeBaseCommand()
{
  char *command = malloc(11ul);
  assert(command && "Failed to allocate memory for base command.");

  strcpy(command, "code -n --");

  return command;
}

char *addToCommand(char *command, const char *path)
{
  size_t \
    originalSize = strlen(command),
    pathSize = strlen(path);
  size_t totalSize = originalSize + pathSize + 4;

  char *newCommand = realloc(command, totalSize);
  assert(newCommand && "Failed to reallocate memory for command.");

  strcpy(newCommand + originalSize,                " '");
  strcpy(newCommand + originalSize + 2,            path);
  strcpy(newCommand + originalSize + 2 + pathSize, "'");

  return newCommand;
}

GList *menuProviderGetSelectedItems(NautilusMenuProvider *provider, GtkWidget *window, GList *files)
{
  if (files == NULL)
  {
    return NULL;
  }

  char *command = makeBaseCommand();

  size_t nrOfElements = g_list_length(files);
  NautilusFileInfo *firstFile = files->data;
  if (nrOfElements == 1 && nautilus_file_info_is_directory(firstFile))
  {
    char *absoluteFilePath = g_file_get_path(nautilus_file_info_get_location(firstFile));
    command = addToCommand(command, absoluteFilePath);
    g_free(absoluteFilePath);

    return menuProviderAddItem(window, command, DEFAULT_BUTTON_LABEL);
  }

  char buttonLabel[32];
  size_t nrOfFiles = 0ul;

  for (GList *element = files; element != NULL; element = element->next) {
    NautilusFileInfo *file = element->data;

    if (nautilus_file_info_is_mime_type(file, "text/*"))
    {
      char *absoluteFilePath = g_file_get_path(nautilus_file_info_get_location(file));

      command = addToCommand(command, absoluteFilePath);
      assert(command);
      ++nrOfFiles;

      g_free(absoluteFilePath);
    }
  }

  if (nrOfFiles == 0)
  {
    return NULL;
  }

  if (nrOfFiles == 1)
  {
    strcpy(buttonLabel, "Open file in VSCode");
  }
  else
  {
    sprintf(buttonLabel, "Open %ld files in VSCode", nrOfFiles);
  }

  return menuProviderAddItem(window, command, buttonLabel);
}

GList *menuProviderGetCurrentFolder(
  NautilusMenuProvider *provider,
  GtkWidget *window,
  NautilusFileInfo *currentFolder
)
{
  assert(currentFolder);

  char *command = makeBaseCommand();

  char *absoluteDirPath = g_file_get_path(nautilus_file_info_get_location(currentFolder));
  if (!absoluteDirPath) return NULL;

  command = addToCommand(command, absoluteDirPath);
  g_free(absoluteDirPath);

  return menuProviderAddItem(window, command, DEFAULT_BUTTON_LABEL);
}

void OpenInVSCodeMenuProviderInterfaceInit(gpointer interfacePointer, gpointer)
{
  NautilusMenuProviderInterface* interface = interfacePointer;
  interface->get_file_items = menuProviderGetSelectedItems;
  interface->get_background_items = menuProviderGetCurrentFolder;
}
