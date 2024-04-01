import sys

def generate(filepath):
    out = ''  

    with open(filepath, 'r') as file:
        for line in file:  
            for char in line:  
                if char in "><+-.,[]":  
                    out += char * 6  

    with open(filepath.rsplit('.', 1)[0] + '.rf', 'w') as file:
        file.write(out)

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python script.py <file_path>")
        sys.exit(1)
    generate(sys.argv[1])
