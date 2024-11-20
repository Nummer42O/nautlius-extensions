#ifndef OPEN_IN_VSCODE_UTILITIES_H
#define OPEN_IN_VSCODE_UTILITIES_H

#include <glib.h>


/**
 * @brief Allocate basic command to open files in new VS Code window.
 *
 * @note Failed allocations trigger assertions.
 *
 * @return Heap allocated string representing the bash command. Caller takes ownership.
 */
char *oivsc_makeBaseCommand();

/**
 * @brief Add a file to the vscode command.
 *
 * @param command Current command pointer. Will be invalid after a successful run.
 * @param path Path to the file to be opened.
 * 
 * @return Returns a pointer to the reallocated, modified command.
 */
char *oivsc_addToCommand(
  char *command,
  const char *path
);

/**
 * @brief Select files from the GList by the given mime type.
 * 
 * @param files List of NautilusFileInfo objects representing the selected items.
 * @param mimeType The mime type (pattern) to be selected. Symlinks will be dereferenced before the check.
 * @param command Current command pointer. Will be invalid if o_nrSelectedElements has incremented.
 * @param o_nrSelectedElements Number of items which got selected for matching mime type. Must be initialized.
 * 
 * @return Possibly modified command. To be safe, always assume the command parameter is invalid and use this value instead.
 */
char *oivsc_selectByMimeType(
  GList *files,
  const char *mimeType,
  char *command,
  size_t *o_nrSelectedElements
);

/**
 * @brief Construct the label for the context menu button.
 * @param nrOfDirs The number of selected directories.
 * @param nrOfFiles The number of selected files.
 * @param o_buttonLabel A preallocated character array to write to.
 */
void oivsc_makeButtonLabel(
  size_t nrOfDirs,
  size_t nrOfFiles,
  char *o_buttonLabel
);

#endif // !defined(OPEN_IN_VSCODE_UTILITIES_H)
