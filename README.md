# image-editor

## DEFINITION
Simple image editor written in C.
Editor supports only png files.


## BUILD

Build the executable by running the Makefile.

```bash
$ make
```

## QUICK START

### Save As

To save the image file with a different name add following parameters

```bash
$ ./image-edit -i input.png -o output.png
```

### Gray Scale
To gray scale the desired image file, add following parameters

```bash
$ ./image-edit -i input.png -o output.png -g
```
#### Input
![](https://github.com/alperakkin/image-editor/blob/main/examples/castle.png)

#### Output

![](https://github.com/alperakkin/image-editor/blob/main/examples/castle-gs.png)

### Contrast
To apply contrast to the desired image file, add following parameters

```bash
$ ./image-edit -i input.png -o output.png -c 1.2
```
#### Input
![](https://github.com/alperakkin/image-editor/blob/main/examples/castle.png)

#### Output

![](https://github.com/alperakkin/image-editor/blob/main/examples/castle-contr.png)

### Brightness
To apply brightness to the desired image file, add following parameters

```bash
$ ./image-edit -i input.png -o output.png -b 1.2
```
#### Input
![](https://github.com/alperakkin/image-editor/blob/main/examples/castle.png)

#### Output

![](https://github.com/alperakkin/image-editor/blob/main/examples/castle-bright.png)


### Gaussian Blur
To apply Gaussian Blur to the desired image file, add following parameters


```bash
$ ./image-edit -i examples/castle.png  --gaussian 50x1.4  -o examples/castle-gaussian.png
```

The --gaussian 50x1.4 parameter applies a Gaussian blur effect, where 50 specifies the size of the Gaussian kernel matrix (e.g., 50x50), and 1.4 indicates the standard deviation (sigma) of the Gaussian distribution.


#### Input
![](https://github.com/alperakkin/image-editor/blob/main/examples/castle.png)

#### Output

![](https://github.com/alperakkin/image-editor/blob/main/examples/castle-gaussian.png)

### Resize
To rezise the desired image file, add following parameters


```bash
$ ./image-edit -i examples/castle.png  -r 128x128  -o examples/castle-resize.png
```



#### Input
![](https://github.com/alperakkin/image-editor/blob/main/examples/castle.png)

#### Output

![](https://github.com/alperakkin/image-editor/blob/main/examples/castle-resize.png)

### Histogram
To obtain the histogram distribution of the color channels of the desired image file, add the following parameters.


```bash
$ ./image-edit -i examples/castle.png  --histogram
```



#### Input
![](https://github.com/alperakkin/image-editor/blob/main/examples/castle.png)

#### Output

![](https://github.com/alperakkin/image-editor/blob/main/examples/terminal-histogram.png)


### Color Filter
To apply color filter to the desired image file, add the following parameters.


```bash
$ ./image-edit -i examples/castle.png  -f f5da42x0.2  -o examples/castle-filter.png
```

This filter applies yellow filter (f5da42) with 0.2 opacity.


#### Input
![](https://github.com/alperakkin/image-editor/blob/main/examples/castle.png)

#### Output

![](https://github.com/alperakkin/image-editor/blob/main/examples/castle-filter.png)

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
