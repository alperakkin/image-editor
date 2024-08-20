import os
import ctypes

package_dir = os.path.dirname(__file__)
lib_path = os.path.join(package_dir, 'libs', 'image-edit.so')

img_lib = ctypes.CDLL(lib_path)


class Image(ctypes.Structure):
    _fields_ = [
        ("name", ctypes.c_char_p),
        ("width", ctypes.c_int),
        ("height", ctypes.c_int),
        ("color_type", ctypes.c_ubyte),
        ("bit_depth", ctypes.c_ubyte),
        ("pixels", ctypes.POINTER(ctypes.POINTER(ctypes.c_ubyte * 4)))
    ]


img_lib.help.argtypes = None
img_lib.help.restype = None

img_lib.open_image.argtypes = [ctypes.c_char_p]
img_lib.open_image.restype = Image

img_lib.save_image.argtypes = [ctypes.c_char_p, Image]

img_lib.grayscale.argtypes = [Image]
img_lib.grayscale.restype = Image


img_lib.contrast.argtypes = [Image, ctypes.c_float]
img_lib.contrast.restype = Image


img_lib.brightness.argtypes = [Image, ctypes.c_float]
img_lib.brightness.restype = Image


img_lib.gaussian.argtypes = [Image, ctypes.c_int, ctypes.c_float]
img_lib.gaussian.restype = Image

img_lib.resize.argtypes = [Image, ctypes.c_int, ctypes.c_int]
img_lib.resize.restype = Image

img_lib.histogram.argtypes = [Image]
img_lib.histogram.restype = None

img_lib.filter.argtypes = [Image, ctypes.c_char_p, ctypes.c_float]
img_lib.filter.restype = Image

img_lib.opacity.argtypes = [Image, ctypes.c_float]
img_lib.opacity.restype = Image

img_lib.add_layer.argtypes = [
    Image, Image, ctypes.c_int, ctypes.c_int, ctypes.c_int
]
img_lib.add_layer.restype = Image


img_lib.crop.argtypes = [
    Image, ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.c_int
]

img_lib.crop.restype = Image


img_lib.rotate_image.argtypes = [Image, ctypes.c_double]
img_lib.rotate_image.restype = Image

img_lib.invert.argtypes = [Image]
img_lib.invert.restype = Image

img_lib.add_border.argtypes = [Image, ctypes.c_char_p, ctypes.c_int]
img_lib.add_border.restype = Image

img_lib.mask.argtypes = [Image, ctypes.c_char_p, ctypes.c_float]
img_lib.mask.restype = Image

img_lib.edge.argtypes = [Image, ctypes.c_int, ctypes.c_int]
img_lib.edge.restype = Image

img_lib.match_template.argtypes = [Image, Image, ctypes.c_float]
img_lib.match_template.restype = None

img_lib.check_color.argtypes = [Image, ctypes.c_char_p, ctypes.c_float]
img_lib.check_color.restype = None

img_lib.vignette.argtypes = [Image, ctypes.c_float]
img_lib.vignette.restype = Image
