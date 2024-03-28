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

## PARAMETERS

-i: Input Image Path
-o: Output Image Path
-g: Gray Scale
-c: Contrast


It is also possible to apply multi filters at once

```bash
$ ./image-edit -i input.png -o output.png  -g -c 1.2
```

#### Input
![](https://github.com/alperakkin/image-editor/blob/main/examples/castle.png)

#### Output

![](https://github.com/alperakkin/image-editor/blob/main/examples/castle-gs-contr.png)