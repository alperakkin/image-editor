import ctypes
from .image_edit import img_lib as img


class Editor:
    def __init__(self):
        pass

    def help(self):
        img.help()

    def open_image(self, filename):
        byte_path = filename.encode('utf-8')
        return img.open_image(ctypes.c_char_p(byte_path))

    def save_image(self, path, image):
        path = ctypes.c_char_p(path.encode("utf-8"))
        img.save_image(path, image)

    def gray_scale(self, image):
        return img.grayscale(image)

    def contrast(self, image, factor):
        factor = ctypes.c_float(factor)
        return img.contrast(image, factor)

    def brightness(self, image, ratio):
        ratio = ctypes.c_float(ratio)
        return img.brightness(image, ratio)

    def gaussian(self, image, kernel_size, sigma):
        kernel_size = ctypes.c_int(kernel_size)
        sigma = ctypes.c_float(sigma)
        return img.gaussian(image, kernel_size, sigma)

    def resize(self, image, width, height):
        width = ctypes.c_int(width)
        height = ctypes.c_int(height)
        return img.resize(image, width, height)

    def histogram(self, image):
        img.histogram(image)

    def filter(self, image, color, strength):
        color = ctypes.c_char_p(color.encode("utf-8"))
        strength = ctypes.c_float(strength)
        return img.filter(image, color, strength)

    def opacity(self, image, factor):
        factor = ctypes.c_float(factor)
        return img.opacity(image, factor)

    def add_layer(self, image, patch, pos_x, pos_y, alpha):
        pos_x = ctypes.c_int(pos_x)
        pos_y = ctypes.c_int(pos_y)
        alpha = ctypes.c_int(alpha)
        return img.add_layer(image, alpha, patch, pos_x, pos_y, alpha)

    def crop(self, image, left, right, top, bottom):
        left = ctypes.c_int(left)
        right = ctypes.c_int(right)
        top = ctypes.c_int(top)
        bottom = ctypes.c_int(bottom)
        return img.crop(image, left, right, top, bottom)

    def rotate_image(self, image, angle):
        angle = ctypes.c_double(angle)
        return img.rotate_image(image, angle)

    def invert(self, image):
        return img.invert(image)

    def add_border(self, image, color, size):
        color = ctypes.c_char_p(color.encode("utf-8"))
        size = ctypes.c_int(size)
        return img.add_border(image, color, size)

    def mask(self, image, color, threshold):
        color = ctypes.c_char_p(color.encode("utf-8"))
        threshold = ctypes.c_float(threshold)
        img.mask(image, color, threshold)

    def edge(self, image, high_threshold, low_threshold):
        high_threshold = ctypes.c_int(high_threshold)
        low_threshold = ctypes.c_int(low_threshold)
        return img.edge(image, high_threshold, low_threshold)

    def match_template(self, image, template, threshold):
        threshold = ctypes.c_float(threshold)
        img.match_template(image, template, threshold)

    def check_color(self, image, color, threshold):
        color = ctypes.c_char_p(color.encode("utf-8"))
        threshold = ctypes.c_float(threshold)
        img.check_color(image, color, threshold)

    def vignette(self, image, factor):
        factor = ctypes.c_float(factor)
        img.vignette(image, factor)
