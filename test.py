
from pyimage import Editor

editor = Editor()
file_path = "examples/castle.png"


img = editor.open_image(file_path)

editor.save_image("test.png", img)
