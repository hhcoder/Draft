import numpy as np
import sys, getopt
import matplotlib.pyplot as plt

def ReadBayerRaw(src_fname, in_width, in_height):
    in_length = in_width * in_height
    raw_buffer = np.fromfile(src_fname, dtype=np.uint16, count=in_length)
    return np.reshape(raw_buffer, (in_height, in_width))

def ImShow(img, t):
        plt.figure()
        plt.imshow(img, cmap='gray')
        plt.title(t)
        plt.show(block=True)

def main(argv):
    inputfile = ''
    outputfile = ''
    width = 0
    height = 0
    try:
        opts, args = getopt.getopt(argv,'i:o:w:h:v',["ifile=","ofile=","width=","height="])
    except getopt.GetoptError:
        print('show_image.py -i <inputfile> -o <outputfile> -w <width> -h <height>')
        sys.exit(2)
    for opt, arg in opts:
        if opt == '-v':
            print('test.py -i <inputfile> -o <outputfile>')
            sys.exit()
        elif opt in ("-i", "--ifile"):
            inputfile = arg
        elif opt in ("-o", "--ofile"):
            outputfile = arg
        elif opt in ("-w", "--width"):
            width = int(arg)
        elif opt in ("-h", "--height"):
            height = int(arg)
    print('Input file is "', inputfile)
    print('Output file is "', outputfile)
    print('Width is "', width)
    print('Height is "', height)

    # inputfile = "./r.raw"
    # width = 4032
    # height = 3024
    uint16_image = ReadBayerRaw(inputfile, width, height)

    ImShow(uint16_image, "Image")

if __name__ == "__main__":
    main(sys.argv[1:])
