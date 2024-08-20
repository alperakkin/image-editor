# image-editor

## DEFINITION
A lightweight image editor written in C, designed to be integrated into Python packages.


## BUILD

Build the executable by running the Makefile.

```bash
$ make
```
Executable file "image-edit" will be created in bin folder.

### AS PYTHON PACKAGE

To build python package from image editor .c files run following script

```bash
$ make shared
```

After build completes, you can use pyimage folder as python package.

Note: This package can only be used for Unix based systems. (Linux, Darwin etc.)

## QUICK START

### Save As

To save the image file with a different name add following parameters

```bash
$ ./bin/image-edit -i input.png -o output.png
```

### Gray Scale
To apply gray scale to the desired image file, add following parameters

```bash
$ ./bin/image-edit -i input.png -o output.png -g
```
#### Input
![](https://github.com/alperakkin/image-editor/blob/main/examples/castle.png)

#### Output

![](https://github.com/alperakkin/image-editor/blob/main/examples/castle-gs.png)


### Opacity

To apply opacity to the desired image, add following parameters

```bash
$ ./bin/image-edit -i examples/castle.png  --opacity 0.3  -o examples/castle-opacity.png
```
#### Input
![](https://github.com/alperakkin/image-editor/blob/main/examples/castle.png)

#### Output

![](https://github.com/alperakkin/image-editor/blob/main/examples/castle-opacity.png)



### Contrast
To apply contrast to the desired image file, add following parameters

```bash
$ ./bin/image-edit -i input.png -o output.png -c 1.2
```
#### Input
![](https://github.com/alperakkin/image-editor/blob/main/examples/castle.png)

#### Output

![](https://github.com/alperakkin/image-editor/blob/main/examples/castle-contr.png)

### Brightness
To apply brightness to the desired image file, add following parameters

```bash
$ ./bin/image-edit -i input.png -o output.png -b 1.2
```
#### Input
![](https://github.com/alperakkin/image-editor/blob/main/examples/castle.png)

#### Output

![](https://github.com/alperakkin/image-editor/blob/main/examples/castle-bright.png)


### Gaussian Blur
To apply Gaussian Blur to the desired image file, add following parameters


```bash
$ ./bin/image-edit -i examples/castle.png  --gaussian --kernel-size 50 --sigma 1.4  -o examples/castle-gaussian.png
```

The --gaussian 50x1.4 parameter applies a Gaussian blur effect, where 50 specifies the size of the Gaussian kernel matrix (e.g., 50x50), and 1.4 indicates the standard deviation (sigma) of the Gaussian distribution.


#### Input
![](https://github.com/alperakkin/image-editor/blob/main/examples/castle.png)

#### Output

![](https://github.com/alperakkin/image-editor/blob/main/examples/castle-gaussian.png)

### Resize
To rezise the desired image file, add following parameters


```bash
$ ./bin/image-edit -i examples/castle.png  -r 128x128  -o examples/castle-resize.png
```



#### Input
![](https://github.com/alperakkin/image-editor/blob/main/examples/castle.png)

#### Output

![](https://github.com/alperakkin/image-editor/blob/main/examples/castle-resize.png)

### Histogram
To obtain the histogram distribution of the color channels of the desired image file, add the following parameters.


```bash
$ ./bin/image-edit -i examples/castle.png  --histogram
```



#### Input
![](https://github.com/alperakkin/image-editor/blob/main/examples/castle.png)

#### Output

![](https://github.com/alperakkin/image-editor/blob/main/examples/terminal-histogram.png)


### Color Filter
To apply color filter to the desired image file, add the following parameters.


```bash
$ ./bin/image-edit -i examples/castle.png  -f --color "#f5da42" --opacity 0.2  -o examples/castle-filter.png
```

This filter applies yellow filter (#f5da42) with 0.2 opacity.


#### Input
![](https://github.com/alperakkin/image-editor/blob/main/examples/castle.png)

#### Output

![](https://github.com/alperakkin/image-editor/blob/main/examples/castle-filter.png)


### Add Image Layer
To add new image to existing image, add the following parameters.


```bash
$   ./bin/image-edit -i examples/castle.png -l --path examples/sun.png --pos 170x30  --alpha-mask 200 -o examples/castle-layer.png
```

This command overlays sun.png onto castle.png at coordinates x:170 and y:30. A higher value of the alpha mask results in a loss of detail in the sun flares, while a lower value creates noise in the image.



#### Inputs
![](https://github.com/alperakkin/image-editor/blob/main/examples/castle.png)
![](https://github.com/alperakkin/image-editor/blob/main/examples/sun.png)

#### Output

![](https://github.com/alperakkin/image-editor/blob/main/examples/castle-layer.png)

### Crop Image
To crop the image from sides, add the following parameters.


```bash
$ ./bin/image-edit -i examples/castle.png --crop --left 100  --right 10 --top 30 --bottom 20 -o examples/castle-cropped.png
```

Side parameters are optional. It is possible to provide just desired sides.



#### Input
![](https://github.com/alperakkin/image-editor/blob/main/examples/castle.png)

#### Output

![](https://github.com/alperakkin/image-editor/blob/main/examples/castle-cropped.png)


### Rotate Image
To rotate the image with given angle in degrees, add the following parameters.


```bash
$ ./bin/image-edit -i examples/castle.png --rotate 30 -o examples/castle-rotated.png
```


#### Input
![](https://github.com/alperakkin/image-editor/blob/main/examples/castle.png)

#### Output

![](https://github.com/alperakkin/image-editor/blob/main/examples/castle-rotated.png)


### Invert Image
To invert the colors of the image, add the following parameters.


```bash
$ ./bin/image-edit -i examples/castle.png --invert -o examples/castle-rotated.png
```


#### Input
![](https://github.com/alperakkin/image-editor/blob/main/examples/castle.png)

#### Output

![](https://github.com/alperakkin/image-editor/blob/main/examples/castle-inverted.png)


### Add Border
To add borders on the image, add the following parameters.


```bash
$ ./bin/image-edit -i examples/castle.png --border 5 --color "#f51a00" -o examples/castle-border.png
```


#### Input
![](https://github.com/alperakkin/image-editor/blob/main/examples/castle.png)

#### Output

![](https://github.com/alperakkin/image-editor/blob/main/examples/castle-border.png)


### Mask Color
To apply a color mask , add the following parameters.


```bash
$ ./bin/image-edit -i examples/castle.png  --mask --color "#6a7175"  --threshold 0.65 --mask --color "#255bbb" --threshold 0.35 -o examples/castle-mask.png
```

The above command applies two masks to the image. The first mask removes the color #6a7175 from the image with a 65% threshold. The second mask removes the color #255bbb with a 35% threshold.


#### Input
![](https://github.com/alperakkin/image-editor/blob/main/examples/castle.png)

#### Output

![](https://github.com/alperakkin/image-editor/blob/main/examples/castle-mask.png)


### Edge Detection
To detect the edges in the image , add the following parameters.


```bash
$  ./bin/image-edit -i examples/castle.png --edge --threshold --low 200 --high 250 -o examples/castle-edge.png
```

Fine tune your image with low & high thresholds to get a better result.


#### Input
![](https://github.com/alperakkin/image-editor/blob/main/examples/castle.png)

#### Output

![](https://github.com/alperakkin/image-editor/blob/main/examples/castle-edge.png)


### Template Matching
To detect any given template image (part of the original image) matches the original image, add the following parameters.


```bash
$  ./bin/image-edit -i examples/castle.png --template examples/castle-template.png --threshold 1
```


#### Inputs
![](https://github.com/alperakkin/image-editor/blob/main/examples/castle.png)
![](https://github.com/alperakkin/image-editor/blob/main/examples/castle-template.png)

#### Output

![](https://github.com/alperakkin/image-editor/blob/main/examples/template-output.png)


### Color Check
To detect any given color matches in the original image, add the following parameters.


```bash
$   ./bin/image-edit -i examples/image.png --check-color "#FFFFFF" --threshold 0.9
```


#### Input
![](https://github.com/alperakkin/image-editor/blob/main/examples/signature.png)


#### Output

```bash
$   ./bin/image-edit -i examples/image.png --check-color "#FFFFFF" --threshold 0.9
[Color: #FFFFFF Fill Ratio: 9.302073 %]
```

```bash
$   ./bin/image-edit -i examples/image.png --check-color "#FFFFFF" --threshold 0.05
[Color: #FFFFFF Fill Ratio: 9.648534 %]
```

In the example above, it is determined whether a signature is present in the image. Observe how the threshold value affects the reduction of noise in the image.

### Vignette
To apply vignette to the image, add the following parameters.


```bash
$   ./bin/image-edit -i examples/castle.png --vignette 1.1 -o examples/castle-vignette.png
```


#### Input
![](https://github.com/alperakkin/image-editor/blob/main/examples/castle.png)


#### Output
![](https://github.com/alperakkin/image-editor/blob/main/examples/castle-vignette.png)


In the example above, it is determined whether a signature is present in the image. Observe how the threshold value affects the reduction of noise in the image.

## PARAMETERS

-i: Input Image Path
-o: Output Image Path
-g: Gray Scale
-c: Contrast
-b: Brightness
--gaussian: Gaussian Blur
-r: Resize
--histogram: Histogram
-f: Color Filter
--color: Color Hex Value
--opacity: Opacity
--kernel-size: Kernel Size
--sigma: Sigma Value
-l: Add Image Layer
--path: Layer Path
--pos: Locate Image
--crop: Crop Image
--left: Left Side in Pixels
--right: Right Side in Pixels
--top: Top Side in Pixels
--bottom: Bottom Side in Pixels
--rotate: Rotate Image to given angle
--invert: Invert Colors
--border: Add Border
--mask: Add Mask
--threshold: Threshold
--edge: Edge Detection
--low: Low Key
--high: High Key
--template: Match Template
--color-check: Color Check
--vignette: Apply Vignette



## MULTIPLE ARGUMENTS

Multiple arguments can be assigned to the input image as shown below

```bash
$ ./bin/image-edit -i examples/castle.png  -r 128x128 --gaussian --kernel-size 50 --sigma 1.4 -o examples/castle-multiple.png
```


#### Input
![](https://github.com/alperakkin/image-editor/blob/main/examples/castle.png)

#### Output

![](https://github.com/alperakkin/image-editor/blob/main/examples/castle-multiple.png)



### Python Usage

```python
from pyimage import Editor

editor = Editor()
file_path = "examples/castle.png"

img = editor.open_image(file_path)
img = editor.gray_scale(img)
img = editor.gaussian(img, 5, 1.2)

editor.save_image("examples/castle-python.png", img)

```

#### Input
![](https://github.com/alperakkin/image-editor/blob/main/examples/castle.png)

#### Output

![](https://github.com/alperakkin/image-editor/blob/main/examples/castle-python.png)

