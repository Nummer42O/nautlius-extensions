"""
Add an action to the Nautilus context-menu to convert png and jpeg images
to the wepb format.

Author: Egidio Docile
"""

from urllib.parse import urlparse, unquote
from logging import Logger, FileHandler, getLogger

from gi.repository import GObject, Nautilus
from PIL import Image


class OpenInCodeProvider(GObject.GObject, Nautilus.MenuProvider):
    log: Logger

    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)

        self.log = getLogger(self.__class__.__qualname__)
        self.log.addHandler(
            FileHandler("/home/johannes/.logs/nautilus-extensions.log")
        )
        self.log.debug(f"__init__ with {args=}, {kwargs=}")

    def convert(self, menu, files):
        self.log.debug(f"convert with {menu=}, {files=}")

    def get_file_items(self, window, files):
        self.log.debug(f"get_file_items with {window=}, {files=}")

        menu_item = Nautilus.MenuItem(
            name="test",
            label="Test"
        )
        menu_item.connect('activate', self.convert, files)

        return menu_item,