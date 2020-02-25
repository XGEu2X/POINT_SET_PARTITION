from os import listdir

def leer_archivo(nombre_de_archivo):
    Data = []
    file = open(nombre_de_archivo,'r')
    for dato in file:
        Data.append(dato.strip('\n'))
    return Data

#dir = 'outs/'
dir = 'C:/Users/ge_u2/Dropbox/PHD/Experimentos/'

result = []

Files = listdir(dir)
for fileName in Files:
    File = leer_archivo(dir+fileName)
    size = len(File)
    value = float(File[size-3])

    splited = fileName.split('_')
    
    n = int(splited[1])
    t = int(splited[2])
    method = int(splited[9][0])

    if not ([n,t, method] in result):
        result.append([n,t,method])
        result.append(100)
    
    i = result.index([n,t, method])
    if value < result[i+1]:
        result[i+1] = value

for i in range(int(len(result)/2)):
    print(str(result[2*i])+' '+str(result[2*i+1]))