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

## PARAMETERS

-i: Input Image Path
-o: Output Image Path
-g: Gray Scale
