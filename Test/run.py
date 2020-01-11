import show_image.ImShow as ImShow
import show_image.ReadBayerRaw as ReadBayerRaw

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
