#include "utilities.h"
#include "logging.h"

#include <assert.h>
#include <nautilus-extension.h>


char *oivsc_makeBaseCommand()
{
  nelog_trace("[ENTER]\n");

  char *command = malloc(11ul);
  assert(command && "Failed to allocate memory for base command.");

  strcpy(command, "code -n --");

  return command;
}

char *oivsc_addToCommand(char *command, const char *path)
{
  nelog_trace("[ENTER] command: \"%s\" path: \"%s\"\n", command, path);

  size_t originalSize = strlen(command);
  size_t totalSize = originalSize + strlen(path) + 4;

  char *newCommand = realloc(command, totalSize);
  assert(newCommand && "Failed to reallocate memory for command.");

  sprintf(newCommand + originalSize, " '%s'", path);

  return newCommand;
}

char *oivsc_selectByMimeType(GList *files, const char *mimeType, char *command, size_t *o_nrSelectedElements)
{
  nelog_trace(
    "[ENTER] files: %p mimeType: \"%s\" command: \"%p\", o_nrSelectedElements: %p\n",
    files, mimeType, command, o_nrSelectedElements
  );

  char *outputCommand = command;
  for (GList *element = files; element != NULL; element = element->next) {
    NautilusFileInfo *file = element->data;

    //! NOTE: automatically dereferences symlinks, so this is fine to check directly
    if (nautilus_file_info_is_mime_type(file, mimeType))
    {
      char *absoluteFilePath = g_file_get_path(nautilus_file_info_get_location(file));
      if (!absoluteFilePath) continue;

      outputCommand = oivsc_addToCommand(outputCommand, absoluteFilePath);
      ++(*o_nrSelectedElements);

      g_free(absoluteFilePath);
    }
  }

  return outputCommand;
}

void oivsc_makeButtonLabel(size_t nrOfDirs, size_t nrOfFiles, char *o_buttonLabel)
{
  nelog_trace(
    "[ENTER] nrOfDirs: %lu nrOfFiles: %lu o_buttonLabel: %p\n",
    nrOfDirs, nrOfFiles, o_buttonLabel
  );

  strcpy(o_buttonLabel, "Open");

  if (nrOfDirs != 0) {
    if (nrOfDirs == 1) {
      sprintf(o_buttonLabel, "%s dir", o_buttonLabel);
    } else {
      sprintf(o_buttonLabel, "%s %ld dirs", o_buttonLabel, nrOfDirs);
    }
    if (nrOfFiles != 0) {
      sprintf(o_buttonLabel, "%s and", o_buttonLabel);
    }
  }

  if (nrOfFiles != 0) {
    if (nrOfFiles == 1) {
      sprintf(o_buttonLabel, "%s file", o_buttonLabel);
    } else {
      sprintf(o_buttonLabel, "%s %ld files", o_buttonLabel, nrOfFiles);
    }
  }

  sprintf(o_buttonLabel, "%s in VSCode", o_buttonLabel);
}
